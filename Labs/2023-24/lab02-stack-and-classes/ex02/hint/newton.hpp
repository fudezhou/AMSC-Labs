#ifndef NEWTON_H
#define NEWTON_H

#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>

class NewtonSolver {
  public:

    // Constructor
    NewtonSolver(
      // function f
      const std::function<double(double)>& fx, // passed as a reference because you don't need to copy it
      // derivative of f
      const std::function<double(double)>& dfx,
      // max iterations 
      const unsigned int max_iter = 100,
      // residual tolerance, by default 2 machine epsilon
      const double tol_res = std::numeric_limits<double>::epsilon(),
      // step tolerance, by default 2 machine epsilon
      const double tol_dx = std::numeric_limits<double>::epsilon()
    )
      : 
    // initialize members
      _fx(fx), 
      _dfx(dfx),
      _max_iter(max_iter),
      _tol_res(tol_res), 
      _tol_dx(tol_dx),
      _x_n(0),
      _df_dx(0),
      _dx(0),
      _res(0),
      _iter(0) {}

// ================================================
// implement here the public method "solve" that recives as input x_0
// has the following pseudocode
// * reset the history of solutions x_n
// * while not reached max number of iterations
// ** compute residual at current x_iter
// ** if residual too small break
// ** compute derivative at current x_iter
// ** apply newton step
// ** if step is smaller than tolerance break

    void solve(const double x_0); // you can pass x0 by value

// ================================================
// define here the public "getters" for

    // * the result
    double getResult() const {
      return _x_n.back(); // return the last element of the vector
    };

    // * the last step size
    double getStep() const { return _dx; };

    // * the history of x_n (return a const reference)
    const std::vector<double>& getHistory() const { // const reference because we don't want to modify the history and you only need to read it
      return _x_n;
    };

    // * the last residual
    double getResidual() const { return _res; };

    // * the number of iterations performed
    unsigned int getIter() const { return _iter; };

    ~NewtonSolver() = default; // default destructor, not virtual because it is not a polymorphic class and not needed


// ================================================
// define here the private members, you need
  private:

    // * the function f
    std::function<double(double)> _fx;
    // * the derivative of f
    std::function<double(double)> _dfx;

    // * max number of iterations
    const unsigned int  _max_iter;
    // * the tolerance on the residual
    const double        _tol_res;
    // * the tolerance of the step size
    const double        _tol_dx;

    // * the history of the iterations x_n
    std::vector<double> _x_n;
    // * the last evaluation of f
    double              _df_dx;
    // * the last evaluation of the derivative of f
    double              _dx;
    // * the current residual
    double              _res;
    // * the current number of iterations
    unsigned int        _iter;

};

#endif /* NEWTON_H */