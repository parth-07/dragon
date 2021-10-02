#ifndef FACTORIZATION_HPP
#define FACTORIZATION_HPP
#include <cmath>
#include <vector>

namespace dragon {
/**
 * Computes prime factorization of a number in O(sqrt(N)).
 *
 * @returns sequence containing prime factorization
 * of the number in non-descending order.
 */
template <typename T> auto cal_prime_factorization(T n) {
  std::vector<T> pfs;
  for (T i = 2; i * i <= n; ++i) {
    while (n % i == 0) {
      pfs.push_back(i);
      n /= i;
    }
  }
  if (n > 1)
    pfs.push_back(n);
  return pfs;
}

/**
 * Computes factors of a number in O(sqrt(n)).
 *
 * @returns vector containing all the factors in
 * ascending order.
 */
template <typename T> auto cal_factors(T n) {
  std::vector<T> factors;
  std::vector<T> factors_after_sqrt;
  for (T i = 1; i * i <= n; ++i) {
    if (n % i == 0) {
      factors.push_back(i);
      factors_after_sqrt.push_back(n / i);
    }
  }
  if (factors_after_sqrt.back() == factors.back()) {
    factors_after_sqrt.pop_back();
  }
  while (!factors_after_sqrt.empty()) {
    factors.push_back(factors_after_sqrt.back());
    factors_after_sqrt.pop_back();
  }
  return factors;
}

} // namespace dragon
#endif