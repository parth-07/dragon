/**
 * SqrtDecomposition is easy to use and generic implementation of
 * basic sqrt decomposition data structure.
 *
 * Time Complexity:
 *  building - O(N)
 *  query - O(sqrt(N))
 */
#ifndef DRAGON_DS_SQRT_DECOMPOSITION_HPP
#define DRAGON_DS_SQRT_DECOMPOSITION_HPP
#include <cmath>
#include <vector>
namespace dragon {

template <typename ValueT, typename BinaryFunctor> class SqrtDecomposition {
private:
  mutable BinaryFunctor m_query_functor;

public:
  using ValueType = ValueT;
  using QueryReturnType = decltype(
      m_query_functor(std::declval<ValueType>(), std::declval<ValueType>()));
  using QueryFunctorType = BinaryFunctor;
  using SizeType = std::size_t;

private:
  template <typename T> using Sequence = std::vector<T>;

public:
  // Special member functions
  SqrtDecomposition(const SqrtDecomposition&) = default;
  SqrtDecomposition(SqrtDecomposition&&) noexcept = default;
  SqrtDecomposition& operator=(const SqrtDecomposition&) = default;
  SqrtDecomposition& operator=(SqrtDecomposition&&) noexcept = default;
  ~SqrtDecomposition() = default;

  // Non-default constructors
  // identity value can only be provided while object construction and can
  // not be changed afterwards.
  template <typename ForwardIterator>
  SqrtDecomposition(ValueType identity_value, ForwardIterator first,
                    ForwardIterator last);
  template <typename Container>
  SqrtDecomposition(ValueType identity_value, const Container& container);

  template <typename Container> void build(const Container& container);
  template <typename ForwardIterator>
  void build(ForwardIterator first, ForwardIterator last);

  auto query(SizeType l, SizeType r) const;
  void update(SizeType index, ValueType val);
  void clear();

private:
  Sequence<QueryReturnType> m_blocks, m_source;
  const ValueType m_identity_value;
  SizeType m_block_size;
};

template <typename ValueT, typename BinaryFunctor>
template <typename ForwardIterator>
SqrtDecomposition<ValueT, BinaryFunctor>::SqrtDecomposition(
    ValueType identity_value, ForwardIterator first, ForwardIterator last)
    : m_identity_value(identity_value) {
  build(first, last);
}

template <typename ValueT, typename BinaryFunctor>
template <typename Container>
SqrtDecomposition<ValueT, BinaryFunctor>::SqrtDecomposition(
    ValueType identity_value, const Container& container)
    : m_identity_value(identity_value) {
  build(container);
}

template <typename ValueT, typename BinaryFunctor>
template <typename ForwardIterator>
void SqrtDecomposition<ValueT, BinaryFunctor>::build(ForwardIterator first,
                                                     ForwardIterator last) {
  static_assert(std::is_base_of<std::forward_iterator_tag,
                                typename std::iterator_traits<
                                    ForwardIterator>::iterator_category>::value,
                "Iterators provided should atleast have capabilities of "
                "forward iterators");
  m_blocks.clear();
  m_source.assign(first, last);
  m_block_size = static_cast<SizeType>(
      std::ceil(std::sqrt(static_cast<long double>(m_source.size()))));
  m_blocks.resize(m_block_size, m_identity_value);
  for (SizeType i = 0; i < m_source.size(); ++i) {
    m_blocks[i / m_block_size] = m_query_functor(m_blocks[i / m_block_size],
                                                 m_source[i]);
  }
}

template <typename ValueT, typename BinaryFunctor>
template <typename Container>
void SqrtDecomposition<ValueT, BinaryFunctor>::build(
    const Container& container) {
  build(begin(container), end(container));
}

template <typename ValueT, typename BinaryFunctor>
auto SqrtDecomposition<ValueT, BinaryFunctor>::query(SizeType l,
                                                     SizeType r) const {
  SizeType block_l = l / m_block_size;
  SizeType block_r = r / m_block_size;
  QueryReturnType res = m_identity_value;
  if (block_l == block_r) {
    for (SizeType i = l; i <= r; ++i)
      res = m_query_functor(res, m_source[i]);
  } else {
    for (SizeType i = l; i < (block_l + 1) * m_block_size; ++i)
      res = m_query_functor(res, m_source[i]);
    for (SizeType i = block_l + 1; i < block_r; ++i)
      res = m_query_functor(res, m_blocks[i]);
    for (SizeType i = block_r * m_block_size; i <= r; ++i)
      res = m_query_functor(res, m_source[i]);
  }
  return res;
}

template <typename ValueT, typename BinaryFunctor>
void SqrtDecomposition<ValueT, BinaryFunctor>::update(SizeType index,
                                                      ValueType val) {
  m_source[index] = val;
  SizeType block_index = index / m_block_size;
  m_blocks[block_index] = m_identity_value;
  for (SizeType i = block_index * m_block_size;
       i < (block_index + 1) * m_block_size; ++i) {
    m_blocks[block_index] = m_query_functor(m_blocks[block_index], m_source[i]);
  }
}

template <typename ValueT, typename BinaryFunctor>
void SqrtDecomposition<ValueT, BinaryFunctor>::clear() {
  m_source.clear();
  m_blocks.clear();
}

} // namespace dragon

#endif
