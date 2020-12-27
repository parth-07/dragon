#ifndef DRAGON_NUMBER_THEORY_EULER_TOTIENT_CPP
#define DRAGON_NUMBER_THEORY_EULER_TOTIENT_CPP
#include <iostream>
#include <vector>

namespace dragon {
template <typename ValueT> auto get_euler_totient(ValueT num) {
  ValueT res = num;
  for (ValueT i = 2; i * i <= num; ++i) {
    if (num % i == 0) {
      while (num % i == 0)
        num /= i;
      res -= res / i;
    }
  }
  res -= res / num;
  return res;
}

template <typename ValueT> class EulerTotient {
public:
  using ValueType = ValueT;
  using SizeType = size_t;

private:
  template <typename T> using Sequence = std::vector<T>;

public:
  EulerTotient() = default;
  EulerTotient(const EulerTotient&) = default;
  EulerTotient(EulerTotient&&) noexcept = default;
  EulerTotient& operator=(const EulerTotient&) = default;
  EulerTotient& operator=(EulerTotient&&) noexcept = default;
  ~EulerTotient() = default;

  EulerTotient(SizeType scan_limit) { build(scan_limit); }

  auto operator[](SizeType num) const noexcept { return m_totients[num]; }

  void build(SizeType scan_limit);
  auto get_totient(SizeType num) const noexcept { return m_totients[num]; }

private:
  Sequence<ValueT> m_totients;
  SizeType m_scan_limit = 0;
};

template <typename ValueT>
void EulerTotient<ValueT>::build(SizeType scan_limit) {
  m_scan_limit = scan_limit;
  m_totients.resize(m_scan_limit + 1);
  for (SizeType i = 0; i <= m_scan_limit; ++i) {
    m_totients[i] = static_cast<ValueT>(i);
  }
  for (SizeType i = 2; i <= m_scan_limit; i += 2) {
    m_totients[i] -= static_cast<ValueT>(m_totients[i] / 2);
  }
  for (SizeType i = 3; i <= m_scan_limit; i += 2) {
    if (m_totients[i] == static_cast<ValueT>(i)) {
      for (SizeType j = i; j <= m_scan_limit; j += i) {
        m_totients[j] -= static_cast<ValueT>(m_totients[j] / i);
      }
    }
  }
}
} // namespace dragon
#endif