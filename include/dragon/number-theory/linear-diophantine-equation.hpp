/**
 * Algorithm for efficiently computing solutions for linear equation in 2 
 * variables, for example, given equations
 * a*x + b*y = c, then
 * find_linear_diophantine_equation_solution(a,b,c,x,y) will return true
 * if solutions exists ,an passed variables x and y will contain 1 such solution
 * If solution don't exist, function return false
 */
#ifndef DRAGON_NUMBER_THEORY_LINEAR_DIOPHANTINE_EQUATION_HPP
#define DRAGON_NUMBER_THEORY_LINEAR_DIOPHANTINE_EQUATION_HPP

#include "dragon/number-theory/extended-euclid-gcd.hpp"
#include <bits/stdc++.h>

namespace dragon {
using std::pair;

/**
 * time complexity: Same as of Euclid gcd algorithm
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