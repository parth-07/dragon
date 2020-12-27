#ifndef DRAGON_NUMBER_THEORY_LINEAR_DIOPHANTINE_EQUATION_HPP
#define DRAGON_NUMBER_THEORY_LINEAR_DIOPHANTINE_EQUATION_HPP

#include "dragon/number-theory/extended-euclid-gcd.hpp"
#include <bits/stdc++.h>

namespace dragon {
using std::pair;

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