/**
 * Good old Sieve of eratosthenes implementation 
 * Time complexity: O(Nlg(lg(N))
 */
#ifndef DRAGON_NUMBER_THEORY_SIEVE_HPP
#define DRAGON_NUMBER_THEORY_SIEVE_HPP
#include <bits/stdc++.h>

namespace dragon {

/**
 * Uses sieve of eratosthenes algorithm to compute prime numbers
 * in range [1,N] and information about whether number i 
 * in range [1,N] is prime or not.
 * 
 * @param T should be big enough to store largest prime number in range [1,N],
 */
template <typename T = long long int> class Sieve {

private:
  template <typename U> using Sequence = std::vector<U>;

public:
  using SizeType = typename Sequence<T>::size_type;
  using ValueType = T;

public:
//Special member functions declared as default
  Sieve() = default;
  Sieve(const Sieve&) = default;
  Sieve(Sieve&&) noexcept = default;
  Sieve& operator=(const Sieve&) = default;
  Sieve& operator=(Sieve&&) noexcept = default;
  ~Sieve() = default;

  Sieve(SizeType scan_limit);
  void build(SizeType scan_limit);

public:
  Sequence<bool> is_prime;
  // primes[i] returns the i'th prime number.
  Sequence<T> primes;

private:
  SizeType m_scan_limit;
};
/**
 * Compute primes and is_prime members to provide information about 
 * primes in range [1,scan_limit]
 */
template <typename T> Sieve<T>::Sieve(SizeType scan_limit) {
  build(scan_limit);
}

/**
 * Compute primes and is_prime members to provide information about 
 * primes in range [1, scan_limit].
 */
template <typename T> void Sieve<T>::build(SizeType scan_limit) {
  m_scan_limit = scan_limit;

  is_prime.clear();
  primes.clear();

  is_prime.resize(scan_limit + 1, 1);

  is_prime[0] = is_prime[1] = 0;

  for (SizeType i = 4; i <= scan_limit; i += 2)
    is_prime[i] = 0;

  for (SizeType i = 3; i * i <= scan_limit; i += 2) {
    if (is_prime[i]) {
      for (SizeType j = i * i; j <= scan_limit; j += i) {
        is_prime[j] = 0;
      }
    }
  }

  for (SizeType i = 0; i <= scan_limit; ++i) {
    if (is_prime[i])
      primes.push_back(static_cast<ValueType>(i));
  }
}
} // namespace dragon
#endif