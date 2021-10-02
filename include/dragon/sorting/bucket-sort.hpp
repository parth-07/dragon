#ifndef DRAGON_SORTING_BUCKET_SORT_HPP
#define DRAGON_SORTING_BUCKET_SORT_HPP

#include <algorithm>
#include <iterator>
#include <type_traits>
#include <vector>

namespace dragon {
/**
 * Sorts the range [first, last) in place in linear time while mainting
 * relative order of equivalent elements.
 * Elements of the range should be uniformally distributed in range [0,1],
 *
 * @param first range begin iterator
 * @param last range end iterator
 */
template <typename ForwardIterator>
constexpr void bucket_sort(ForwardIterator first,
                           ForwardIterator last) noexcept {
  using std::vector;
  std::size_t sz = std::distance(first, last);
  vector<vector<std::decay_t<decltype(*first)>>> buckets(sz + 1);
  for (auto it = first; it != last; ++it) {
    std::size_t idx = sz * static_cast<std::size_t>(*it);
    buckets[idx].push_back(*it);
  }
  auto it = first;
  for (auto& bucket : buckets) {
    std::stable_sort(bucket.begin(), bucket.end());
    for (auto item : bucket) {
      *it = item;
      ++it;
    }
  }
}
} // namespace dragon

#endif