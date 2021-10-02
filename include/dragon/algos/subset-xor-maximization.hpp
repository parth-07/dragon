#ifndef DRAGON_ALGOS_SUBSET_XOR_MAXIMIZATION_HPP
#define DRAGON_ALGOS_SUBSET_XOR_MAXIMIZATION_HPP
#include <algorithm>
#include <limits>
#include <vector>

#include "dragon/core/utils.hpp"

namespace dragon {
/**
 * Calculates maximum subset xor value.
 *
 * @param first begin iterator
 * @param last end iterator
 */
template <typename ForwardIterator>
typename ForwardIterator::value_type
maximum_subset_xor_value(ForwardIterator first, ForwardIterator last) {
  using ValueType = typename ForwardIterator::value_type;

  std::size_t bucket_sz = sizeof(ValueType) * details::bits_in_byte;
  std::vector<std::vector<ValueType>> buckets(bucket_sz);

  for (auto iter = first; iter != last; ++iter) {
    int pos = details::msb_pos(*iter);
    if (pos != -1)
      buckets[pos].push_back(*iter);
  }

  std::vector<ValueType> consider;

  for (std::size_t i = bucket_sz; i--;) {
    if (buckets[i].empty())
      continue;
    consider.push_back(buckets[i][0]);
    for (std::size_t j = 1; j < buckets[i].size(); ++j) {
      buckets[i][j] ^= buckets[i][0];
      int pos = details::msb_pos(buckets[i][j]);
      if (pos != -1)
        buckets[pos].push_back(buckets[i][j]);
    }
  }

  ValueType res = 0;
  for (auto item : consider) {
    if (res < (res ^ item))
      res ^= item;
  }

  return res;
}

/**
 * Calculates maximum subset xor value.
 *
 * @param container sequential container
 */
template <typename Container>
typename Container::value_type
maximum_subset_xor_value(const Container& container) {
  return maximum_subset_xor_value(std::begin(container), std::end(container));
}

} // namespace dragon
#endif