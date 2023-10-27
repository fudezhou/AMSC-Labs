#include "newton.hpp"

// You can define you function like this or use a lambda function

  double fx(double x) { return x * x - 2.0;} 
  double dfx(double x) { return 2.0 * x; }

int main() {

  // Defining as lambda functions
  auto f = [](auto x) { return x * x - 2.0; };
  auto df = [](auto x) { return 2.0 * x; };

  NewtonSolver solver(f, df); // try also with fx and dfx

  solver.solve(1.0);

  std::cout << std::endl;

  return 0;
}