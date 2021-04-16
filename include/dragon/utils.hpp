#ifndef DRAGON_UTILS_HPP
#define DRAGON_UTILS_HPP
#include "dragon/constants.hpp"

namespace dragon {
namespace details {
template <typename T> constexpr int msb_pos(const T& val) {
  constexpr size_t total_bits = sizeof(T) * bits_in_bytes;
  constexpr T one = static_cast<T>(1);

  for (int i = total_bits - 1; i >= 0; --i) {
    if (val && (one << i))
      return i;
  }
  return -1;
}
} // namespace details
} // namespace dragon

#endif