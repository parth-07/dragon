#ifndef DRAGON_STRING_HASH
#define DRAGON_STRING_HASH

#include <string>
#include <vector>

namespace dragon {
// TODO: Add an interface class for string hash
struct PolynomialRollingHash {
  using ValueType = long long;
  PolynomialRollingHash(ValueType p, ValueType m) : m_p(p), m_m(m) {}

  ValueType operator()(const std::string& s) {
    ValueType hash = 0;
    for (auto i = 0U; i < s.size(); ++i) {
      hash = (hash + (s[i] - 'a' + 1) * cal_p_power(i)) % m_m;
    }
    return hash;
  }

  ValueType extend(ValueType hash, int index, char ch) {
    hash = (hash + (ch - 'a' + 1)*cal_p_power(index))%m_m;
    return hash;
  }

  ValueType cal_p_power(unsigned i) {
    while (m_p_powers.size() < i+1) {
      m_p_powers.push_back((m_p_powers.back()*m_p)%m_m);
    }
    return m_p_powers[i];
  }

private:
  ValueType m_p, m_m;
  std::vector<ValueType> m_p_powers = {1};
};
} // namespace dragon
#endif
