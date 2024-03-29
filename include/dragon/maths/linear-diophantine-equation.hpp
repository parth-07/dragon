/**
 * Algorithm for efficiently computing solutions for linear equation in 2
 * variables, for example, given equations
 * a*x + b*y = c, then
 * find_linear_diophantine_equation_solution(a,b,c,x,y) will return true
 * if solutions exists ,an passed variables x and y will contain 1 such solution
 * If solution don't exist, function return false
 */
#ifndef DRAGON_MATHS_LINEAR_DIOPHANTINE_EQUATION_HPP
#define DRAGON_MATHS_LINEAR_DIOPHANTINE_EQUATION_HPP

#include <bits/stdc++.h>
#include "dragon/maths/extended-euclid-gcd.hpp"

namespace dragon {
using std::pair;

/**
 * Compute solution for linear equation in 2 variables and
 * assigns solution, if it exists, inplace to the x and y
 * function arguments
 *
 * ```
 * a*x + b*y = c
 * ```
 * @return true, if solution exist, otherwise false
 */
template <typename T, typename U>
constexpr bool find_linear_diophantine_equation_solution(T a, T b, T c, U& x,
                                                         U& y) noexcept {
  T g = gcd(abs(a), abs(b), x, y);
  if (c % g)
    return 0;
  x *= (c / g);
  y *= (c / g);
  if (a < 0)
    x = -x;
  if (b < 0)
    y = -y;
  return true;
}
} // namespace dragon
#endif