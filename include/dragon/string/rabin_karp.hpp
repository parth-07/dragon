#ifndef DRAGON_STRING_ROBIN_KARP_HPP
#define DRAGON_STRING_ROBIN_KARP_HPP
#include <string>
#include <vector>
#include "dragon/string/hash.hpp"
namespace dragon {
std::vector<unsigned> rabin_karp(const std::string& s,
                                 const std::string& pattern, long long p = 31,
                                 long long m = 1e9 + 7) {
  std::vector<unsigned> pos;
  PolynomialRollingHash hash(p, m);
  auto pattern_hash = hash(pattern);
  std::vector<PolynomialRollingHash::ValueType> s_hash_prefix(s.size() + 1);
  s_hash_prefix[0] = 0;
  for (auto i = 0U; i < s.size(); ++i) {
    s_hash_prefix[i + 1] = hash.extend(s_hash_prefix[i], i, s[i]);
  }
  for (auto i = 0U; i <= s.size() - pattern.size(); ++i) {
    auto current_hash = s_hash_prefix[i + pattern.size()] - s_hash_prefix[i];
    if (current_hash == (pattern_hash * hash.cal_p_power(i)) % m) {
      pos.push_back(i);
    }
  }
  return pos;
}
} // namespace dragon
#endif