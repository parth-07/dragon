/**
 * Algorithms to efficiently compute expressions a^b and (a^b)%m 
 * 
 */
#ifndef DRAGON_MATHS_BINARY_EXPONENTIATION_HPP
#define DRAGON_MATHS_BINARY_EXPONENTIATION_HPP

#include <bits/stdc++.h>
namespace dragon {

/**
 * Computes (a^b)%m in logarithmic time.
 *
 */
template <typename T>
inline constexpr T binary_exponentiation(T a, T b, T m) noexcept {
  T res = 1;
  while (b) {
    if (b & 1)
      res = (res * a) % m;
    a = (a * a) % m;
    b >>= 1;
  }
  return res;
}

/**
 * Computes a^b in logarithmic time.
 */
template <typename T>
inline constexpr T binary_exponentiation(T a, T b) noexcept {
  T res = 1;
  while (b) {
    if (b & 1)
      res = (res * a);
    a = (a * a);
    b >>= 1;
  }
  return res;
}
} // namespace dragon
#endif
