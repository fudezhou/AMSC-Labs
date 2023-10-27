#include "newton.hpp"

NewtonSolver::NewtonSolver(const NewtonParams& params) // definition of the constructor
    : _fx(params.fx),
      _dfx(params.dfx),
      _max_iter(params.max_iter),
      _tol_res(params.tol_res),
      _tol_dx(params.tol_dx),
      _x_n(params.x_n), 
      _df_dx(params.df_dx),
      _dx(params.dx),
      _res(params.res),
      _iter(params.iter) {}

void NewtonSolver::solve(const double& x_0) {

    _x_n.resize(1); // THIS IS FUNDAMENTAL
    _x_n.reserve(_max_iter + 1);
    _x_n[0] = x_0;

    for (_iter = 0; _iter < _max_iter; ++_iter) {
        std::cout << std::endl;
        std::cout << "=== Newton Method ===" << std::endl;

        std::cout << "iter =    " << NewtonSolver::getIter() << std::endl;

        _res = _fx(_x_n[_iter]);
        std::cout << "res  =    " << NewtonSolver::getResidual() << std::endl;

        if (std::abs(_res) < _tol_res) {
            std::cout << "dx   =    " << NewtonSolver::getStep() << std::endl;
            std::cout << "x    =    " << NewtonSolver::getResult() << std::endl;
            break;
        }

        _df_dx = _dfx(_x_n[_iter]);
        _dx = _res / _df_dx;
        std::cout << "dx   =    " << NewtonSolver::getStep() << std::endl;

        _x_n.push_back(_x_n[_iter] - _dx);
        std::cout << "x    =    " << NewtonSolver::getResult() << std::endl;

        if (std::abs(_dx) < _tol_dx) break;
    }
}

double NewtonSolver::getResult() const {
    return _x_n.back();
}

double NewtonSolver::getStep() const {
    return _dx;
}

const std::vector<double>& NewtonSolver::getHistory() const {
    return _x_n;
}

double NewtonSolver::getResidual() const {
    return _res;
}

unsigned int NewtonSolver::getIter() const {
    return _iter;
}
