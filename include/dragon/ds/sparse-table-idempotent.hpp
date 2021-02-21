/**
 * Easy to use and generalized template implementation of
 * sparse table. This class inherits from 
 * dragon::SparseTable<T,BinaryFunctor>, use this class only
 * when query function is idempotent, as this class assumes
 * provided query function is idempotent and is thus optimized
 * based on that assumption.
 * 
 * Query function is idempotent when f(a,a) = a for all values 'a',
 * where f is the query function 
 * 
 */
#ifndef DRAGON_DS_SPARSE_TABLE_IDEMPOTENT_HPP
#define DRAGON_DS_SPARSE_TABLE_IDEMPOTENT_HPP

#include <algorithm>
#include <iostream>
#include "dragon/ds/sparse-table.hpp"
namespace dragon {

template <typename T, typename BinaryFunctor>
class SparseTableIdempotent : public SparseTable<T, BinaryFunctor> {
public:
  using typename SparseTable<T, BinaryFunctor>::SourceValueType;
  using typename SparseTable<T, BinaryFunctor>::SizeType;
  using typename SparseTable<T,BinaryFunctor>::QueryReturnType;
public:
  //Special member functions
  SparseTableIdempotent() = default;
  SparseTableIdempotent(const SparseTableIdempotent&) = default;
  SparseTableIdempotent& operator=(const SparseTableIdempotent&) = default;
  SparseTableIdempotent(SparseTableIdempotent&&) noexcept = default;
  SparseTableIdempotent& operator=(SparseTableIdempotent&&) noexcept = default;
  ~SparseTableIdempotent() = default;

  // Non default constructors
  template <typename ForwardIterator>
  SparseTableIdempotent(ForwardIterator first, ForwardIterator last);
  template <typename Container>
  SparseTableIdempotent(const Container& container);

  template <typename ForwardIterator>
  void build(ForwardIterator first, ForwardIterator last);

  template <typename Container>
  void build(const Container&);

  // Query range is inclusive = [l,r]
  auto query(SizeType l, SizeType r) const;

  QueryReturnType query_function(SourceValueType a, SourceValueType b) const;
  QueryReturnType query_function(SourceValueType a) const;

private:
  static void extend_lg_precomputed_range(SizeType range_max);

private:
  static std::vector<int> lg;
};

template <typename T, typename BinaryFunctor>
std::vector<int> SparseTableIdempotent<T, BinaryFunctor>::lg(2, 0);

template <typename T, typename BinaryFunctor>
template <typename ForwardIterator>
SparseTableIdempotent<T, BinaryFunctor>::SparseTableIdempotent(
    ForwardIterator first, ForwardIterator last) {
  this->build(first, last);
}

template <typename T, typename BinaryFunctor>
template <typename Container>
SparseTableIdempotent<T, BinaryFunctor>::SparseTableIdempotent(
    const Container& container) {
  this->build(container);
}

template <typename T, typename BinaryFunctor>
template <typename Container>
void SparseTableIdempotent<T, BinaryFunctor>::build(
                                                    const Container& container) {
  build(std::begin(container),std::end(container));
}

template <typename T, typename BinaryFunctor>
template <typename ForwardIterator>
void SparseTableIdempotent<T, BinaryFunctor>::build(ForwardIterator first,
                                                    ForwardIterator last) {
  SparseTable<T, BinaryFunctor>::build(first, last);
  extend_lg_precomputed_range(this->m_table.size());
}

template <typename T, typename BinaryFunctor>
typename SparseTableIdempotent<T,BinaryFunctor>::QueryReturnType SparseTableIdempotent<T, BinaryFunctor>::query_function(
    SourceValueType a, SourceValueType b) const {
  return this->m_query_functor(a, b);
}

template <typename T, typename BinaryFunctor>
typename SparseTableIdempotent<T,BinaryFunctor>::QueryReturnType SparseTableIdempotent<T, BinaryFunctor>::query_function(
    SourceValueType a) const {
  return this->m_query_functor(a, a);
}

template<typename T, typename BinaryFunctor>
auto SparseTableIdempotent<T,BinaryFunctor>::query(SizeType l,SizeType r) const {
  SizeType j = lg[r-l+1];
  return query_function(this->m_table[l][j],this->m_table[r-((this->one)<<j)+1][j]);
}

template <typename T, typename BinaryFunctor>
void SparseTableIdempotent<T, BinaryFunctor>::extend_lg_precomputed_range(
    SizeType range_max) {
  SizeType i = lg.size();
  lg.resize(std::max(i, range_max + 1));
  for (; i <= range_max; ++i) {
    lg[i] = lg[i / 2] + 1;
  }
}

} // namespace dragon

#endif