#ifndef NEWTON_H
#define NEWTON_H

#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>

class NewtonSolver {
public:
  NewtonSolver(
    // function f
    // derivative of f
    // max iterations 
    // residual tolerance, by default 2 machine epsilon
    // step tolerance, by default 2 machine epsilon
    const std::function<double(double)>& fx,
    const std::function<double(double)>& dfx
  )
    : _fx(fx), _dfx(dfx) {}
  /*initialize members*/ {
  }


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
  void solve();

// ================================================
// define here the public "getters" for
// * the result
// * the last step size
// * the history of x_n (return a const reference)
// * the last residual
// * the number of iterations performed

// ================================================
// define here the private members, you need
// * the function f
// * the derivative of f
// * max number of iterations
// * the tolerance on the residual
// * the tolerance of the step size
// * the history of the iterations x_n
// * the last evaluation of f
// * the last evaluation of the derivative of f
// * the current residual
// * the current number of iterations
private:
  std::function<double(double)> _fx;
  std::function<double(double)> _dfx;

};

#endif /* NEWTON_H */