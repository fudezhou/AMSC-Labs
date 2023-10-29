#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <random>
#include <chrono>
#include <map>
#include <unordered_map>
#include <tuple>
#include <memory>
#include <cassert>
#include <utility>
#include <functional>
#include <array> 

/*
  In this exercise you will implement a sparse matrix class using a map of maps.
  The class should be able to store and retrieve elements in O(1) time.
  The class should also be able to perform a matrix-vector product in O(nnz) time.
  In particulare this is CSR format.
*/

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

// The following is a partial implementation of the SparseMatrix class template
template<typename T>
class MapMatrix : public SparseMatrix<T> {

  public:
    using Vector = typename SparseMatrix<T>::Vector; // this is inherited from the base class
    virtual Vector vmult(const Vector& x) const override {

      // assert x.size() == _ncols
      assert(x.size() == SparseMatrix<T>::_ncols); // you can't use _ncols because it is private in the base class
      // allocate memory for result and initialize to 0
      Vector res(SparseMatrix<T>::_nrows);

      // loop over each element of the matrix and add contribute to result
      for (size_t i = 0; i < _data.size(); ++i) {
        /*
          Alternatively you can do as followd:
          const auto& row = _data[i];
          for (const auto& [j, v] : row) {
            res[i] += x[j] * v;
          }
        */
        for (const auto& [j, v] : _data[i]) { // in the reference you can pack two variables, the first is the key and the second is the value
          res[i] += x[j] * v; // local contribution
        }
      }
      return res;
    };

    // this is the non-const version of the operator (), it writes to the matrix
    virtual T& operator()(size_t i, size_t j) override { // 
      // check if we have enough rows, if not add them
      // find column entry, if not present add it
      // return value reference

      if (_data.size() < i + 1) { // with this for you have enough memory space
        _data.resize(i + 1);
        SparseMatrix<T>::_nrows = i + 1;
      }

      const auto it = _data[i].find(j); // find the column entry
      if (it == _data[i].end()) { // if not present add it
        SparseMatrix<T>::_nnz++;
        SparseMatrix<T>::_ncols = std::max(SparseMatrix<T>::_ncols, j + 1); // actual number of columns againts the maximum number of columns

        return (*_data[i].emplace(j, 0).first).second; // return value reference; the second is the value
      } else {
        return (*it).second;
      }
    };

    virtual const T& operator()(size_t i, size_t j) const override {
      // Hp: everything is fine, we can return the value reference
      // return value reference with no check, we use the c++ convention of no bounds check 
      return _data.at(i).at(j); // same as _data[i][j] or _data[i].at(j); the one employing at() is safer because it checks if the index is out of bound and preserves constness
    };

    virtual ~MapMatrix() override = default;

  protected:

    virtual void _print(std::ostream& os) const override {
      // print the data
      for (size_t i = 0; i < _data.size(); ++i) {
        for (const auto& [j, v] : _data[i]) { // for each key-value pair in the map
          os << "["<< i << ", " << j << "]" << " = " << v << std::endl; // in this way you are sure that the order is the same as the one in the map
        }
      }
    };

    std::vector<std::map<size_t, T>> _data; // you have to specify the type of the key and the type of the value
};

int main() {

  MapMatrix<double> m;
  m(0, 0) = 1;
  m(1, 1) = 2;

  std::cout << "Matrix m:" << std::endl;
  m.print(std::cout);

  const auto x = m.vmult({{2, 3}}); // see this syntax

  //std::cout << x[0] << " " << x[1] << std::endl;
  std::cout << "m @ [2; 3]" << std::endl;

  // for (size_t i = 0; i < x.size(); ++i) { // this is the old way
  //   std::cout << x[i] << std::endl;
  // }

  for (const auto& p : x) { // this is fancier
    std::cout << p << std::endl;
  }
  
  return 0;
}
