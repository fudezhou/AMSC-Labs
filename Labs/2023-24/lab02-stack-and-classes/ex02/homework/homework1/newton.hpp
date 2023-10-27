#ifndef NEWTON_H
#define NEWTON_H

#include <cmath>
#include <functional>
#include <iostream>
// #include <limits>
#include <vector>

struct NewtonParams {
  std::function<double(double)> fx;
  std::function<double(double)> dfx;
  unsigned int max_iter;
  double tol_res;
  double tol_dx;
  std::vector<double> x_n;
  double df_dx;
  double dx;
  double res;
  unsigned int iter;
}; // struct NewtonParams, defining the parameters of the NewtonSolver class

class NewtonSolver {

  public:

    NewtonSolver(const NewtonParams& params); 
    void solve(const double& x_0); // this is not const because it modifies the object
    double getResult() const; 
    double getStep() const;
    const std::vector<double>& getHistory() const; 
    double getResidual() const;   
    unsigned int getIter() const;
    ~NewtonSolver() = default; 

  private:

    std::function<double(double)> _fx;
    std::function<double(double)> _dfx;
    const unsigned int            _max_iter;
    const double                  _tol_res;
    const double                  _tol_dx;

    std::vector<double> _x_n;
    double              _df_dx;
    double              _dx;
    double              _res;
    unsigned int        _iter;
};    

#endif
