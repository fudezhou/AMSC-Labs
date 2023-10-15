#include "newton.hpp"

// You could define functions 
// 
// double f(double x) {
//     return x * x - 2.0;
// }

// double df(double x) {
//     return 2.0 * x;
// }

int main() { // you need to pass a function and its derivative
  NewtonSolver solver([](auto x) { return x * x - 2.0; }, [](auto x) { return 2.0 * x; }); // these are lambda functions
  solver.solve(1.0);

  std::cout << "x    =    " << solver.getResult() << std::endl;
  std::cout << "r    =    " << solver.getResidual() << std::endl;
  std::cout << "dx   =    " << solver.getStep() << std::endl;
  std::cout << "iter =    " << solver.getIter() << std::endl;

  return 0;
}