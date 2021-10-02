#ifndef DRAGON_SORTING_COUNTING_SORT_HPP
#define DRAGON_SORTING_COUNTING_SORT_HPP

#include <algorithm>
#include <iterator>
#include <vector>
#include "dragon/core/utils.hpp"

namespace dragon {
/**
 * Sorts the range [first, last) inplace in O(max_val-min_val) time
 * while maintaining relative ordering of equivalent elements
 * (sort is stable).
 *
 * @param first range begin iterator
 * @param last range end iterator
 * @param extract_key extract comparison key from values, key should be of
 * integral type
 * @param min_val minimum key value
 * @param max_val maximum key value
 *
 * TODO: Restrict ExtractKey call operator to be of signature R(T).
 */
template <typename ForwardIterator, typename ExtractKey, typename T>
void counting_sort(ForwardIterator first, ForwardIterator last,
                   ExtractKey extract_key, T min_val, T max_val) {
  using ValueType = typename ForwardIterator::value_type;
  using KeyType = decltype(extract_key(std::declval<ValueType>()));

  max_val -= min_val;
  std::vector<std::vector<ValueType>> count(max_val + 1);
  for (auto it = first; it != last; ++it) {
    KeyType key = extract_key(*it);
    key -= min_val;
    // TODO: instead of copying values, we should perhaps move them.
    count[key].push_back(*it);
  }
  auto it = std::next(last, -1);
  for (auto i = max_val + 1; i-- > 0;) {
    while (!count[i].empty()) {
      *it = count[i].back();
      count[i].pop_back();
      --it;
    }
  }
}

/**
 * Sorts the range [first, last) inplace in O(max_val-min_val) time
 * while maintaining relative ordering of equivalent elements
 * (sort is stable).
 *
 * @param first range begin iterator
 * @param last range end iterator
 * @param extract_key extract comparison key from values, key should be of
 * integral type
 * TODO: Restrict ExtractKey call operator to be of signature R(T).
 */
template <typename ForwardIterator, typename ExtractKey = details::Identity<
                                        typename ForwardIterator::value_type>>
void counting_sort(
    ForwardIterator first, ForwardIterator last,
    ExtractKey extract_key =
        details::Identity<typename ForwardIterator::value_type>()) {

  using ValueType = typename ForwardIterator::value_type;
  using KeyType = decltype(extract_key(std::declval<ValueType>()));

  KeyType min_value, max_value;
  std::vector<KeyType> comparison_keys(std::distance(first, last));
  std::transform(first, last, comparison_keys.begin(), extract_key);

  auto min_and_max_iter = std::minmax_element(comparison_keys.begin(),
                                              comparison_keys.end());
  min_value = *(min_and_max_iter.first);
  max_value = *(min_and_max_iter.second);

  counting_sort(first, last, extract_key, min_value, max_value);
}

} // namespace dragon

#endif