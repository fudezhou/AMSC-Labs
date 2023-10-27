#include "newton.hpp"

/*
    Definition of 'solve' method of NewtonSolver
*/

void NewtonSolver::solve(const double x_0) {

    _x_n.resize(1); // reset the history of solutions x_n; --> REUSABILITY
    _x_n.reserve(_max_iter + 1); // reserving memory
    _x_n[0] = x_0; // initializing the history of solutions x_n with  x_0

    for (_iter = 0; _iter < _max_iter; ++_iter) { 

        std::cout << std::endl;
        std::cout << "=== Newton Method ===" << std::endl;

        std::cout << "iter =    " << NewtonSolver::getIter() << std::endl; // get _iter

        _res = _fx(_x_n[_iter]); // f(x_iter)
        std::cout << "res  =    " << NewtonSolver::getResidual() << std::endl; // get _res at _iter 

        if (std::abs(_res) < _tol_res) {

            std::cout << "dx   =    " << NewtonSolver::getStep() << std::endl; // get _dx at _iter
            std::cout << "x    =    " << NewtonSolver::getResult() << std::endl; // get _x_n.back()
            
            break;
        }

        _df_dx = _dfx(_x_n[_iter]); // f'(x_iter)
        _dx = _res / _df_dx; // dx = f(x_iter) / f'(x_iter)
        std::cout << "dx   =    " << NewtonSolver::getStep() << std::endl; // get _dx at _iter

        _x_n.push_back(_x_n[_iter] - _dx); // x_n+1 = x_n - dx
        std::cout << "x    =    " << NewtonSolver::getResult() << std::endl; // get _x_n.back()

        if (std::abs(_dx) < _tol_dx) break;

    }  

}