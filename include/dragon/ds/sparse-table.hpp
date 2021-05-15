#ifndef DRAGON_DS_SPARSE_TABLE_HPP
#define DRAGON_DS_SPARSE_TABLE_HPP
#include <bits/stdc++.h>

namespace dragon {
/**
 * Generic sparse table data structure.
 * Offers computing queries on interval in logarithmic time.
 * Query function should be associative, commutative and cannot be modified.
 * Initial building of sparse table takes NlgN time.
 * For idempotent queries, see SparseTableIdempotent.
 * 
 * @param T type of data
 * @param BinaryFunctor query functor class
 */
template <typename T, typename BinaryFunctor> class SparseTable {

public:
  using QueryReturnType =
      decltype(BinaryFunctor()(std::declval<T>(), std::declval<T>()));
  using SourceValueType = T;
  using QueryFunctorType = BinaryFunctor;

protected:
  template <typename U> using Sequence = std::vector<U>;
  template <typename U> using Grid = Sequence<Sequence<U>>;

public:
  using SizeType = typename Grid<QueryReturnType>::size_type;
  // For consistency with STL
  using size_type = SizeType;

public:
  // Special member functions;
  SparseTable() = default;
  SparseTable(const SparseTable&) = default;
  SparseTable(SparseTable&&) noexcept = default;
  SparseTable& operator=(const SparseTable&) = default;
  SparseTable& operator=(SparseTable&&) noexcept = default;
  virtual ~SparseTable() = default;

  /**
   * `identity_value` can only be specified during object construction and cannot 
   * be modified.
   * `identity_value` is a value that always satisfies, query(a, identity_value) = a
   * @param identity_value 
   */
  SparseTable(SourceValueType identity_value)
      : m_identity_value(identity_value) {}

  /**
   * Constructs sparse table from iterator range [first, last).
   * @param identity_value 
   * @param first begin iterator
   * @param last end iterator
   */
  template <typename ForwardIterator>
  SparseTable(SourceValueType identity_value, ForwardIterator first,
              ForwardIterator last);

  /**
   * Constructs sparse table of provided container.
   * @param container
   */
  template <typename Container>
  SparseTable(SourceValueType identity_value, Container container);

  /**
   * Builds sparse table from iterator range [first, last)
   * @param first begin iterator
   * @param last end iterator
   */
  template <typename ForwardIterator>
  void build(ForwardIterator first, ForwardIterator last);

  /**
   * Builds sparse table from container.
   * @param container
   */
  template <typename Container> void build(Container container);

  // Computes the query for interval [l, r]
  auto query(SizeType l, SizeType r) const;

  // Reset the object 
  void clear();
  
  // Compute query on values (a, b)
  virtual QueryReturnType query_function(SourceValueType a,
                                         SourceValueType b) const;
  
  // Compute query on values (a, identity_value)
  virtual QueryReturnType query_function(SourceValueType a) const;


protected:
  static constexpr SizeType one = static_cast<SizeType>(1);
  static constexpr SizeType minus_one = static_cast<SizeType>(-1);

  mutable BinaryFunctor m_query_functor;
  Grid<QueryReturnType> m_table;
  SourceValueType m_identity_value;
  SizeType m_exp_max;
};

template <typename T, typename BinaryFunctor>
template <typename ForwardIterator>
SparseTable<T, BinaryFunctor>::SparseTable(SourceValueType identity_value,
                                           ForwardIterator first,
                                           ForwardIterator last
                                      )
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
typename SparseTable<T, BinaryFunctor>::QueryReturnType
SparseTable<T, BinaryFunctor>::query_function(SourceValueType a,
                                              SourceValueType b) const {
  return m_query_functor(a, b);
}

template <typename T, typename BinaryFunctor>
typename SparseTable<T, BinaryFunctor>::QueryReturnType
SparseTable<T, BinaryFunctor>::query_function(SourceValueType a) const {
  return m_query_functor(a, m_identity_value);
}

template <typename T, typename BinaryFunctor>
template <typename ForwardIterator>
void SparseTable<T, BinaryFunctor>::build(ForwardIterator first,
                                          ForwardIterator last) {
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
    m_table[index][0] = query_function(*iter);
  }

  for (SizeType j = 1; j <= m_exp_max; ++j) {
    for (SizeType i = 0; i < sz; ++i) {
      if (i + (one << j) - 1 < sz) {
        m_table[i][j] = query_function(m_table[i][j - 1],
                                       m_table[i + (one << (j - 1))][j - 1]);
      }
    }
  }
}

template <typename T, typename BinaryFunctor>
template <typename Container>
void SparseTable<T, BinaryFunctor>::build(Container container) {
  build(std::begin(container), std::end(container));
}

template <typename T, typename BinaryFunctor>
auto SparseTable<T, BinaryFunctor>::query(SizeType l, SizeType r) const {
  QueryReturnType res = query_function(m_identity_value, m_identity_value);
  for (SizeType j = m_exp_max; j != minus_one; --j) {
    if (l + (one << j) - 1 <= r) {
      res = query_function(res, m_table[l][j]);
      l += (one << j);
    }
  }
  return res;
}

template<typename T, typename BinaryFunctor>
void SparseTable<T, BinaryFunctor>::clear() {
  m_table.clear();
}

} // namespace dragon
#endif