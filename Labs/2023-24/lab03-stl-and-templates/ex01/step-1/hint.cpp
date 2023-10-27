#include <iostream>
#include <vector> // *include vector utility
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

// *The folloiwing class is an ABSTRACT CLASS that represents a sparse matrix
// *and you want it as a template class, meaning that you want to be able to
// *use it with different types (e.g. int, double, float, etc.)


// *use templates to make your matrix usable with different types
// *just like an std::vector can contain different elements, depending on
// *what you specified

template<typename T> // *T is a template parameter, it can be anything; in other words, T is the type of the elements of the class
class SparseMatrix {

  public:
  // *define an alias for std::vector<T>; just for simplicity
  using Vector = std::vector<T>;
  // *constructor, takes no parameters but initializes: number of non-zero elements, number of rows and cols to zero
  SparseMatrix() : _nnz(0), _nrows(0), _ncols(0) {};
  // *getter for number of rows
  size_t getRows() const { return _nrows; };
  // *getter for number of cols
  size_t getCols() const { return _ncols; };
  // *getter for number of number of non-zero
  size_t getNNZ() const { return _nnz; };

  // *print function: prints the number of rows, cols and nnz; moreover calls 
  //                  _print, the virtual version of print that is specialized in the children class
  // RMK: print functions are adopted for debugging purposes
  // see: "Template Method Design Pattern"
  // see: output stream, std::ostream --> so you can print to file as well!
  //      you can do the above because strings in c++ are a polymorphic type!
  void print(std::ostream& os = std::cout) const { // argument is initialized to std::cout if no other printing device is specified
    os << "nrows: " << _nrows << " | ncols:" << _ncols << " | nnz: " << _nnz << std::endl; // common part
    _print(os); // specialized part
  }; 

  // *abstract virtual method vmult that implements vector multiplication
  virtual Vector vmult(const Vector& v) const = 0; 

  /*  The following two methods are the so called "operator overloading", basically they are functions that 
      are called when you use the operator (e.g. +, -, *, /, (), etc.) between two objects of the same class
      In this case, we are overloading the operator () that is used to access the elements of the matrix!!!
      In particular, we are overloading the operator () in two different ways:
      1) const version: this is the version that you want to use when you want to access the element of the matrix
                        but you don't want to modify it, indeed it returns a const reference
      2) non-const version: this is the version that you want to use when you want to modify the element of the matrix,
                            indeed it returns a non-const reference
  */
  // *abstract virtual method operator()(size_t i, size_t j) that implements element access in read only (const version)
  virtual const T& operator()(size_t i, size_t j) const = 0; // pure virtual function, still not implemented
  // *abstract virtual method operator()(size_t i, size_t j) that implements element access in write (returns non-const reference)
  // RMK: this is the version that you want to use when you want to modify the element of the matrix, indeed it returns a non-const reference
  virtual T& operator()(size_t i, size_t j) = 0; // pure virtual function, still not implemented

  // *virtual destructor
  virtual ~SparseMatrix() = default;

  protected: // protected because need to be accessible to children!
    // *abstract virtual method _print that prints the matrix
    virtual void _print(std::ostream& os) const = 0; // pure virtual function, specialized in the children class
    // *variable to store nnz
    size_t _nnz;
    // *variable to store number of rows
    size_t _nrows;
    // *variable to store number of cols
    size_t _ncols;
};

int main() { // main is defined just for compiling purpose

  // SparseMatrix<double> mtx_double; // *this is a sparse matrix of doubles

  return 0;
}