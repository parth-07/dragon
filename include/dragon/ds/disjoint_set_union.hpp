#ifndef DRAGON_DS_DISJOINT_SET_UNION_HPP
#define DRAGON_DS_DISJOINT_SET_UNION_HPP
#include <map>
#include <vector>

namespace dragon {

/**
 * `DisjointSetUnion` is an efficient, easy to use generic implementation of 
 * disjoint set union data structure. It is implemented as disjoint forest
 * of trees, with union by rank and path compression heuristics to improve runtime 
 * complexity. 
 * 
 * @param ValueT type of data
 */
template<typename ValueT>
class DisjointSetUnion {
public:
  using ValueType = ValueT;
  using SizeType = std::size_t;

private:
  template <typename T>
  using Sequence = std::vector<T>;

  template <typename Key, typename Value>
  using AssociativeContainer = std::map<Key, Value>;

public:
  DisjointSetUnion() = default;
  DisjointSetUnion(const DisjointSetUnion&) = default;
  DisjointSetUnion(DisjointSetUnion&&) noexcept = default;
  DisjointSetUnion& operator=(const DisjointSetUnion&) = default;
  DisjointSetUnion& operator=(DisjointSetUnion&&) noexcept = default;
  ~DisjointSetUnion()=default;

  /**
   * Create a new set containing one element with the value provided as the
   * `value` argument.
   * 
   * @param value value of the given element.
   */
  void make_set(const ValueType& value);

  /**
  * Join sets containing elements `u` and `v`.
  * 
  * @param u element 1
  * @param v element 2
  */
  void join(const ValueType& u, const ValueType& v);

  /**
   * Returns true if `u` and `v` belongs to the same set.
   */
  bool in_same_set(const ValueType& u, const ValueType& v);

private:
  /**
   * Link sets containing element with indices `u_i` and `v_i`.
   */
  void link(SizeType u_i, SizeType v_i);
  /**
   * Returns index of the representative element of the set that contains
   * element with index `u_i`.
   */
  SizeType find_representative(SizeType u_i);
private:
  /// Store index of parent of each element.
  Sequence<std::size_t> m_parent;
  /// Store rank of each element.
  Sequence<std::size_t> m_rank;
  /// Store the mapping, element value -> index.
  AssociativeContainer<ValueType, SizeType> m_identifier;
};

template<typename ValueT>
void DisjointSetUnion<ValueT>::make_set(const ValueType& value) {
  SizeType value_identifier = m_identifier.size();
  m_identifier[value] = value_identifier;
  m_parent.push_back(value_identifier);
  m_rank.push_back(0);
}

template<typename ValueT>
void DisjointSetUnion<ValueT>::link(SizeType u_i, SizeType v_i) {
  if (m_rank[u_i] > m_rank[v_i]) {
    m_parent[v_i] = u_i;
  }
  else {
    m_parent[u_i]= v_i;
    if (m_rank[u_i] == m_rank[v_i]) {
      ++m_rank[v_i];
    }
  }
}

template<typename ValueT>
typename DisjointSetUnion<ValueT>::SizeType DisjointSetUnion<ValueT>::find_representative(SizeType u_i) {
  if (m_parent[u_i] != u_i) {
    m_parent[u_i] = find_representative(m_parent[u_i]);
  }
  return m_parent[u_i];
}

template<typename ValueT>
void DisjointSetUnion<ValueT>::join(const ValueType& u, const ValueType& v) {
  auto u_i = find_representative(m_identifier[u]);
  auto v_i = find_representative(m_identifier[v]);
  if (u_i != v_i) {
    link(u_i, v_i);
  }
}

template<typename ValueT>
bool DisjointSetUnion<ValueT>::in_same_set(const ValueType& u, const ValueType& v) {
  return find_representative(m_identifier[u]) == find_representative(m_identifier[v]);
}

} // namespace dragon

#endif