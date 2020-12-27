#ifndef DRAGON_DS_SPARSE_TABLE_HPP
#define DRAGON_DS_SPARSE_TABLE_HPP
#include <bits/stdc++.h>

namespace dragon {
template <typename T, typename BinaryFunctor> class SparseTable {

private:
  mutable BinaryFunctor m_query_function;

public:
  using QueryReturnType =
      decltype(m_query_function(std::declval<T>(), std::declval<T>()));
  using SourceValueType = T;

private:
  template <typename U> using Sequence = std::vector<U>;

  template <typename U> using Grid = Sequence<Sequence<U>>;

private:
  Grid<QueryReturnType> m_table;

public:
  using SizeType = typename Grid<QueryReturnType>::size_type;

public:
  SparseTable(SourceValueType identity_value)
      : m_identity_value(identity_value) {}
  SparseTable(SourceValueType identity_value, BinaryFunctor query_function)
      : m_identity_value(identity_value), m_query_function(query_function) {}

  template <typename ForwardIterator>
  SparseTable(SourceValueType identity_value, ForwardIterator first,
              ForwardIterator last);

  template <typename Container>
  SparseTable(SourceValueType identity_value, Container container);

  // copy constructor
  SparseTable(const SparseTable&) = default;

  // move copy constructor
  SparseTable(SparseTable&&) noexcept = default;

  // assignement operator
  SparseTable& operator=(const SparseTable&) = default;

  // move assignment operator
  SparseTable& operator=(SparseTable&&) noexcept = default;

  // Destructor
  ~SparseTable() = default;

  template <typename ForwardIterator>
  void build(ForwardIterator first, ForwardIterator last);

  template <typename Container> void build(Container container);

  QueryReturnType query(SizeType l, SizeType r) const;

private:
  static constexpr SizeType one = static_cast<SizeType>(1);
  static constexpr SizeType minus_one = static_cast<SizeType>(-1);

  SourceValueType m_identity_value;
  SizeType m_exp_max;
};

template <typename T, typename BinaryFunctor>
template <typename ForwardIterator>
SparseTable<T, BinaryFunctor>::SparseTable(SourceValueType identity_value,
                                           ForwardIterator first,
                                           ForwardIterator last)
    : m_identity_value(identity_value) {
  build(first, last);
}

template <typename T, typename BinaryFunctor>
template <typename Container>
SparseTable<T, BinaryFunctor>::SparseTable(SourceValueType identity_value,
                                           Container container)
    : m_identity_value(identity_value) {
  build(container);
}

template <typename T, typename BinaryFunctor>
template <typename ForwardIterator>
void SparseTable<T, BinaryFunctor>::build(ForwardIterator first,
                                          ForwardIterator last) {
  // show(m_identity_value);
  static_assert(std::is_base_of<std::forward_iterator_tag,
                                typename std::iterator_traits<
                                    ForwardIterator>::iterator_category>::value,
                "Iterators provided should at least have capabilities of "
                "forward iterators");

  SizeType sz = std::distance(first, last);
  m_exp_max = static_cast<SizeType>(std::log2(sz + 1)) + 1;
  m_table.clear();
  m_table.resize(sz, Sequence<QueryReturnType>(m_exp_max + 1));

  SizeType index = 0;
  for (auto iter = first; iter != last; ++iter, ++index) {
    m_table[index][0] = m_query_function(*iter, m_identity_value);
  }

  for (SizeType j = 1; j <= m_exp_max; ++j) {
    for (SizeType i = 0; i < sz; ++i) {
      if (i + (one << j) - 1 < sz) {
        m_table[i][j] = m_query_function(m_table[i][j - 1],
                                         m_table[i + (one << (j - 1))][j - 1]);
      }
    }
  }
}

template <typename T, typename BinaryFunctor>
template <typename Container>
void SparseTable<T, BinaryFunctor>::build(Container container) {
  build(begin(container), end(container));
}

template <typename T, typename BinaryFunctor>
typename SparseTable<T, BinaryFunctor>::QueryReturnType
SparseTable<T, BinaryFunctor>::query(SizeType l, SizeType r) const {
  QueryReturnType res = m_query_function(m_identity_value, m_identity_value);
  for (SizeType j = m_exp_max; j != minus_one; --j) {
    if (l + (one << j) - 1 <= r) {
      res = m_query_function(res, m_table[l][j]);
      l += (one << j);
    }
  }
  return res;
}
} // namespace dragon
#endif