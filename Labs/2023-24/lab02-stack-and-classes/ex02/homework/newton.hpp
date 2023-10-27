#ifndef NEWTON_H
#define NEWTON_H

#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>

struct NewtonParams {
  std::function<double(double)> fx;
  std::function<double(double)> dfx;
  unsigned int max_iter = 100;
  double tol_res = std::numeric_limits<double>::epsilon();
  double tol_dx = std::numeric_limits<double>::epsilon();
}; // struct NewtonParams, defining the parameters of the NewtonSolver class

class NewtonSolver {c

public:
  NewtonSolver(const NewtonParams& params); 
  void solve(const double x_0);
  double getResult() const {
    return _x_n.back(); 
  }; 
  double getStep() const { return _dx; };
  const std::vector<double>& getHistory() const { 
    return _x_n;
  }; 
  double getResidual() const { return _res; };   
  unsigned int getIter() const { return _iter; };
  ~NewtonSolver() = default; 

private:
  std::function<double(double)> _fx;
  std::function<double(double)> _dfx;
  const unsigned int _max_iter;
  const double _tol_res;
  const double _tol_dx;
  std::vector<double> _x_n;
  double _df_dx;
  double _dx;
  double _res;
  unsigned int _iter;
};

#endif
