#ifndef DRAGON_MATHS_EXTENDED_EUCLID_GCD_HPP
#define DRAGON_MATHS_EXTENDED_EUCLID_GCD_HPP
#include <bits/stdc++.h>
namespace dragon {
/**
 * Computes solution to the equation and assigns solution
 * inplace to the x and y arguments
 *
 * ```
 * a*x + b*y = gcd(a, b)
 * ```
 *
 * @return gcd(a, b)
 *
 */
template <typename T, typename U>
constexpr T gcd(T a, T b, U& x, U& y) noexcept {
  if (!b) {
    x = 1;
    y = 0;
    return a;
  }
  if (a < b)
    return gcd(b, a, y, x);
  U x1, y1;
  T g = gcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - (a / b) * y1;
  return g;
}
} // namespace dragon
#endif
