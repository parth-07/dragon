#include "dragon/number-theory/linear-diophantine-equation.hpp"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() {
  int a, b, c;
  // cin >> a >> b >> c;
  a = 5;
  b = 7;
  c = 11;
  int x, y;
  bool is_solution_feasible =
      dragon::find_linear_diophantine_equation_solution(a, b, c, x, y);
  if (is_solution_feasible) {
    cout << a << "*" << x << " + " << b << "*" << y << " = " << c << endl;
  } else
    cout << "No solution feasible";
}