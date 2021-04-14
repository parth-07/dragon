/**
 * Functions to compute and returns length of strictly increasing subsequence.
 * Input sequence will not be modified.
 * Time complexity: O(NlgN) 
 */
#ifndef DRAGON_ALGORITHMS_LONGEST_INCREASING_SUBSEQUENCE_HPP
#define DRAGON_ALGORITHMS_LONGEST_INCREASING_SUBSEQUENCE_HPP

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

namespace dragon {
template<class ForwardIterator>
auto longest_increasing_subsequence_length(ForwardIterator first,ForwardIterator last);

template<class Container>
auto longest_increasing_subsequence_length(const Container& container);

/**
 * @param container container should be a sequence
 * @return length of strictly increasing subsequence
 * 
 */
template<class Container>
auto longest_increasing_subsequence_length(const Container& container) {
  return longest_increasing_subsequence_length(container.begin(),container.end());
}

/**
 * @param first iterator pointing to beginning of the sequence
 * @param last iterator pointing to one past the end of the sequence
 * @return length of strictly increasing subsequence
 * 
 */
template <class ForwardIterator>
auto longest_increasing_subsequence_length(ForwardIterator first,ForwardIterator last) {
  using ValueType = typename std::iterator_traits<ForwardIterator>::value_type;  //NOLINT
  using SizeType = std::size_t;

  SizeType sz = std::distance(first,last);
  std::vector<ValueType> tails(
      sz, std::numeric_limits<ValueType>::max());
  for (auto source_it=first;source_it!=last;++source_it) {
    auto iter = lower_bound(tails.begin(), tails.end(), *source_it);
    *iter = *source_it;
  }
  for (SizeType i = sz - 1; i != static_cast<SizeType>(-1); --i) {
    if (tails[i] != std::numeric_limits<ValueType>::max())
      return i + 1;
  }
  return static_cast<SizeType>(0);
}

} // namespace dragon
#endif