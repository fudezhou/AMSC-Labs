#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <random>
#include <chrono> // for timing
#include <map>
#include <unordered_map>
#include <tuple>
#include <memory>
#include <cassert>
#include <utility>
#include <functional>
#include <array> 
#include <numeric> // for std::iota

template<typename T> 
class SparseMatrix {

  public:

    using Vector = std::vector<T>;

    SparseMatrix() : _nnz(0), _nrows(0), _ncols(0) {};

    size_t getRows() const { return _nrows; };
    size_t getCols() const { return _ncols; };
    size_t getNNZ() const { return _nnz; };

    void print(std::ostream& os = std::cout) const { 
      os << "nrows: " << _nrows << " | ncols:" << _ncols << " | nnz: " << _nnz << std::endl;
      _print(os);
    }; 

    virtual Vector vmult(const Vector& x) const = 0; 
    virtual const T& operator()(size_t i, size_t j) const = 0; 
    virtual T& operator()(size_t i, size_t j) = 0; 
    virtual ~SparseMatrix() = default;

  protected:
  
    virtual void _print(std::ostream& os) const = 0; 
    size_t _nnz, _nrows, _ncols;
};

template<typename T>
class MapMatrix : public SparseMatrix<T> {
public:
    using Vector = typename SparseMatrix<T>::Vector;
    
    // ... Other members and functions ...

    virtual Vector vmult(const Vector& x) const override {
        assert(x.size() == SparseMatrix<T>::_ncols);
        Vector res(SparseMatrix<T>::_nrows);
        for (size_t i = 0; i < _data.size(); ++i) {
            for (const auto& [j, v] : _data[i]) {
                res[i] += x[j] * v;
            }
        }
        return res;
    };

    virtual T& operator()(size_t i, size_t j) override {
        if (_data.size() < i + 1) {
            _data.resize(i + 1);
            SparseMatrix<T>::_nrows = i + 1;
        }
        
        const auto it = _data[i].find(j);
        if (it == _data[i].end()) {
            SparseMatrix<T>::_nnz++;
            SparseMatrix<T>::_ncols = std::max(SparseMatrix<T>::_ncols, j + 1);
            return (*_data[i].emplace(j, 0).first).second;
        } else {
            return (*it).second;
        }
    };

    virtual const T& operator()(size_t i, size_t j) const override {
        return _data.at(i).at(j);
    };

    virtual ~MapMatrix() override = default;

protected:

    virtual void _print(std::ostream& os) const override {
        for (size_t i = 0; i < _data.size(); ++i) {
            for (const auto& [j, v] : _data[i]) {
                os << "[" << i << "; " << j << "]" << " = " << v << std::endl;
            }
        }
    };

    std::vector<std::unordered_map<size_t, T>> _data; // Replaced std::map with std::unordered_map
};

template<typename T>
void fill_matrix(SparseMatrix<T>& m, size_t N) { 
  m(0, 0) = -2;
  m(0, 1) = 1;  
  m(N - 1, N - 2) = 1;
  m(N - 1, N - 1) = -2;  

  for (size_t i = 1; i < N - 1; ++i) {
    m(i, i) = -2;
    m(i, i + 1) = 1;
    m(i, i - 1) = 1;
  }

}

template<typename T>
bool check_eq(const std::vector<T>& lhs, const std::vector<T>& rhs) {

  if (lhs.size() != rhs.size()) { 
    return false;
  }

  for (size_t i = 0; i < lhs.size(); ++i) {
    if (lhs[i] != rhs[i]) { 
      return false;
    }
  }

  return true;
}

void print_test_result(bool test, const std::string& test_name) {
  std::cout << test_name << " test: \t" << (test ? "PASSED" : "FAILED") << std::endl;
}

int main() {

  constexpr size_t N = 10000; // size of the matrix  
  using elem_t = double; // type of the matrix elements

  MapMatrix<elem_t> mtx;
  MapMatrix<elem_t>::Vector x(N), y_ex(N), y(N); 

  std::iota(x.begin(), x.end(), 0); // fill x with 0, 1, 2, ..., N - 1

  y_ex[0] = 1;
  // y_ex[N - 1] = -N; // this line could lead to problems as N is size_t and so -N is not defined
  y_ex[N - 1] = -static_cast<elem_t>(N); // this is the correct way to do it

  {
    using namespace std::chrono;
    const auto t0 = high_resolution_clock::now(); // start the timer
    fill_matrix(mtx, N); // fill the matrix
    const auto t1 = high_resolution_clock::now(); // stop the timer
    const auto elapsed_time = duration_cast<milliseconds>(t1 - t0).count(); // compute the elapsed time
    print_test_result((mtx.getRows() == N) && (mtx.getCols() == N) && (mtx.getNNZ() == 3 * N - 2), "mtx_fill");
    std::cout << "mtx_fill time: \t" << elapsed_time << " ms" << std::endl; // print the elapsed time
  }
    
  std::cout << std::endl;

  {
    using namespace std::chrono;
    const auto t0 = high_resolution_clock::now(); // start the timer
    y = mtx.vmult(x); // compute the matrix-vector product
    const auto t1 = high_resolution_clock::now(); // stop the timer
    const auto elapsed_time = duration_cast<milliseconds>(t1 - t0).count(); // compute the elapsed time
    print_test_result(check_eq(y, y_ex), "vmult"); // check the result
    std::cout << "vmult time: \t" << elapsed_time << " ms" << std::endl; // print the elapsed time
  }

  std::cout << "\n============================\n" << std::endl;
  std::cout << "Matrix:\n" << std::endl;

  if (N < 10) {
    mtx.print(); // default argument is std::cout
  } else {
    std::cout << "N is too large to print the matrix" << std::endl;
  }

  return 0;
}