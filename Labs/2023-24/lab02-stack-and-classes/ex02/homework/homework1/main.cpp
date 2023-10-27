#include <limits>
#include "newton.hpp"

int main() {
    auto f = [](auto x) { return x * x - 2.0; };
    auto df = [](auto x) { return 2.0 * x; };

    NewtonParams params; // declare a NewtonParams object for the parameters
    params.fx = f;
    params.dfx = df;
    params.max_iter = 100;
    params.tol_res = std::numeric_limits<double>::epsilon();
    params.tol_dx = std::numeric_limits<double>::epsilon();
    // params.x_n = std::vector<double>(0); // defining an empty vector
    // params.df_dx = 0.0;
    // params.dx = 0.0;
    // params.res = 0.0;
    // params.iter = 0;

    std::cout << "[SETTINGS]" << std::endl;
    std::cout << "max_iter = " << params.max_iter << std::endl;
    std::cout << "tol_res  = " << params.tol_res << std::endl;
    std::cout << "tol_dx   = " << params.tol_dx << std::endl;

    NewtonSolver solver(params); // define a NewtonSolver object with the parameters

    solver.solve(1.0);

    std::cout << std::endl;

    return 0;
}
