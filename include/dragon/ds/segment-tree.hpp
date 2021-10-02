#ifndef DRAGON_DS_SEGMENT_TREE_HPP
#define DRAGON_DS_SEGMENT_TREE_HPP
#include <cmath>
#include <iostream>
#include <type_traits>
#include <vector>
namespace dragon {

/**
 * Generic segment tree data structure without lazy propagation.
 * Offers computing range queries and doing updates in logarithmic time.
 * Query function should be commutative and associative.
 * Initial building of segment tree takes O(NlgN) time.
 *
 * @param ValueT type of data
 * @param BinaryFunctor query functor class
 */
template <typename ValueT, typename BinaryFunctor> class SegmentTree {
private:
  mutable BinaryFunctor m_query_functor;

public:
  using SourceValueType = ValueT;
  using QueryReturnType = std::result_of_t<BinaryFunctor(ValueT, ValueT)>;
  using QueryFunctorType = BinaryFunctor;
  using SizeType = std::size_t;

private:
  template <typename T> using Sequence = std::vector<T>;

public:
  // Default special member functions
  SegmentTree(const SegmentTree&) = default;
  SegmentTree(SegmentTree&&) noexcept = default;
  SegmentTree& operator=(const SegmentTree&) = default;
  SegmentTree& operator=(SegmentTree&&) noexcept = default;
  ~SegmentTree() = default;

  SegmentTree(SourceValueType identity_value);

  template <typename ForwardIterator>
  SegmentTree(SourceValueType identity_value, ForwardIterator first,
              ForwardIterator last);

  template <typename Container>
  SegmentTree(SourceValueType identity_value, const Container& container);

  template <typename ForwardIterator>
  void build(ForwardIterator first, ForwardIterator last);

  template <typename Container> void build(const Container& source);

  auto query(SizeType l, SizeType r) const;
  void update(SizeType index, SourceValueType value);

  void clear();

private:
  SizeType get_left_child_index(SizeType index) const {
    return (index << 1) + 1;
  }
  SizeType get_right_child_index(SizeType index) const {
    return (index + 1) << 1;
  }

  void build_base(SizeType index, SizeType first, SizeType last);
  auto query_base(SizeType index, SizeType first, SizeType last, SizeType l,
                  SizeType r) const;
  void update_base(SizeType index, SizeType first, SizeType last,
                   SizeType source_index, SourceValueType value);

private:
  constexpr static SizeType one = static_cast<SizeType>(1);
  Sequence<QueryReturnType> m_nodes;
  Sequence<SourceValueType> m_source;
  const SourceValueType m_identity_value;
};

/**
 * `identity_value` is a value which satisfies, query(a, identity_value) = a.
 * `identity_value` can only be provided during object construction.
 *
 * @param identity_value
 */
template <typename ValueT, typename BinaryFunctor>
SegmentTree<ValueT, BinaryFunctor>::SegmentTree(SourceValueType identity_value)
    : m_identity_value(identity_value) {}

template <typename ValueT, typename BinaryFunctor>
template <typename Container>
SegmentTree<ValueT, BinaryFunctor>::SegmentTree(SourceValueType identity_value,
                                                const Container& container)
    : m_identity_value(identity_value) {
  build(container);
}

/**
 * Construct segment tree from iterator range
 *
 * @param first - begin iterator
 * @param last - end iterator
 *
 */
template <typename ValueT, typename BinaryFunctor>
template <typename ForwardIterator>
SegmentTree<ValueT, BinaryFunctor>::SegmentTree(SourceValueType identity_value,
                                                ForwardIterator first,
                                                ForwardIterator last)
    : m_identity_value(identity_value) {
  build(first, last);
}
/**
 * Builds segment tree from sequential container
 *
 * @param container sequential container
 */
template <typename ValueT, typename BinaryFunctor>
template <typename Container>
void SegmentTree<ValueT, BinaryFunctor>::build(const Container& container) {
  build(begin(container), end(container));
}

/**
 * Builds segment tree from iterator range
 *
 * @param first begin iterator
 * @param last end iterator
 */
template <typename ValueT, typename BinaryFunctor>
template <typename ForwardIterator>
void SegmentTree<ValueT, BinaryFunctor>::build(ForwardIterator first,
                                               ForwardIterator last) {
  static_assert(std::is_base_of<std::forward_iterator_tag,
                                typename std::iterator_traits<
                                    ForwardIterator>::iterator_category>::value,
                "Iterators provided should atleast have capabilities of "
                "forward iterators");
  m_source.assign(first, last);
  SizeType tree_sz = 2 * (one << static_cast<SizeType>(
                              std::ceil(std::log2(m_source.size()))));
  m_nodes.resize(tree_sz + 1);
  build_base(0, 0, m_source.size() - 1);
}

template <typename ValueT, typename BinaryFunctor>
void SegmentTree<ValueT, BinaryFunctor>::build_base(SizeType index,
                                                    SizeType first,
                                                    SizeType last) {
  if (first == last) {
    m_nodes[index] = m_source[first];
    return;
  }
  SizeType mid = first + (last - first) / 2;
  SizeType left_child_i = get_left_child_index(index);
  SizeType right_child_i = get_right_child_index(index);
  build_base(left_child_i, first, mid);
  build_base(right_child_i, mid + 1, last);
  m_nodes[index] = m_query_functor(m_nodes[left_child_i],
                                   m_nodes[right_child_i]);
}

/**
 * Query the array in inclusive range [l,r] in logarithmic time.
 * Range should be 0-index based.
 */
template <typename ValueT, typename BinaryFunctor>
auto SegmentTree<ValueT, BinaryFunctor>::query(SizeType l, SizeType r) const {
  return query_base(0, 0, m_source.size() - 1, l, r);
}

template <typename ValueT, typename BinaryFunctor>
auto SegmentTree<ValueT, BinaryFunctor>::query_base(SizeType index,
                                                    SizeType first,
                                                    SizeType last, SizeType l,
                                                    SizeType r) const {
  if (r < first || l > last)
    return m_identity_value;
  if (l <= first && r >= last)
    return m_nodes[index];
  QueryReturnType l_res, r_res;
  auto mid = first + (last - first) / 2;
  l_res = query_base(get_left_child_index(index), first, mid, l, r);
  r_res = query_base(get_right_child_index(index), mid + 1, last, l, r);
  return m_query_functor(l_res, r_res);
}

/**
 * Updates element at given index of the array in logarithmic time.
 *
 * @param index index of element to update
 * @param value new value
 */
template <typename ValueT, typename BinaryFunctor>
void SegmentTree<ValueT, BinaryFunctor>::update(SizeType index,
                                                SourceValueType value) {
  update_base(0, 0, m_source.size() - 1, index, value);
}

template <typename ValueT, typename BinaryFunctor>
void SegmentTree<ValueT, BinaryFunctor>::update_base(SizeType index,
                                                     SizeType first,
                                                     SizeType last,
                                                     SizeType source_index,
                                                     SourceValueType value) {
  if (first > source_index || last < source_index)
    return;
  if (first == last) {
    m_source[source_index] = value;
    m_nodes[index] = value;
    return;
  }
  auto mid = first + (last - first) / 2;
  auto left_child_i = get_left_child_index(index);
  auto right_child_i = get_right_child_index(index);
  update_base(left_child_i, first, mid, source_index, value);
  update_base(right_child_i, mid + 1, last, source_index, value);
  m_nodes[index] = m_query_functor(m_nodes[left_child_i],
                                   m_nodes[right_child_i]);
}

template <typename ValueT, typename BinaryFunctor>
void SegmentTree<ValueT, BinaryFunctor>::clear() {
  m_source.clear();
  m_nodes.clear();
}
} // namespace dragon

#endif