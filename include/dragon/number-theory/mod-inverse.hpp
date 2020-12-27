#ifndef DRAGON_NUMBER_THEORY_MOD_INVERSE_HPP
#define DRAGON_NUMBER_THEORY_MOD_INVERSE_HPP
#include "dragon/number-theory/binary-exponentiation.hpp"
#include "dragon/number-theory/extended-euclid-gcd.hpp"
#include <iostream>

namespace dragon {
// Time complexity : same as euclid gcd algorithm
template <typename T>
constexpr T mod_inverse_using_extended_euclid(T a, T m) noexcept {
  T x, y;
  T g = gcd(a, m, x, y);
  if (g == 1)
    return (x % m + m) % m;
  else
    return 0;
}

// Time complexity : O(lg(m))
// can only be used if m is prime
template <typename T>
constexpr T mod_inverse_using_binary_exp(T a, T m) noexcept {
  return binary_exponentiation(a, m - 2, m);
}
} // namespace dragon
#endif
