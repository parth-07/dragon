/**
 * Algorithm to solve given set of congruence equations
 * in one variable, that is, Solve:
 * x*a1 = 1 (mod m1)
 * x*a2 = 1 (mod m2)
 * .
 * .
 * x*aN = 1 (mod mN)
 */
#ifndef DRAGON_MATHS_CHINESE_REMAINDER_THEOREM_HPP
#define DRAGON_MATHS_CHINESE_REMAINDER_THEOREM_HPP
#include "mod-inverse.hpp"
#include <vector>

namespace dragon {
// Time complexity : O(a.size()*lg(*max(m.begin(),m.end())))
// Time complexity : O(len(a)*max(m))
// Numbers in m vector should be relatively prime to each other
template <typename RandomAccessContainer>
auto solve_typical_crt_problem(const RandomAccessContainer& a,
                               const RandomAccessContainer& m) {
  using ValueType = typename RandomAccessContainer::value_type;

  ValueType all_m_product = 1;
  for (auto item : m)
    all_m_product *= item;
  std::vector<ValueType> m_k;
  for (auto item : m)
    m_k.push_back(all_m_product / item);
  ValueType res = 0;
  for (unsigned i = 0; i < a.size(); ++i) {
    res = (res +
           (a[i] * m_k[i] * mod_inverse_using_extended_euclid(m_k[i], m[i]))) %
          all_m_product;
  }
  return res;
}
} // namespace dragon
#endif