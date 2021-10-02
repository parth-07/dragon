#ifndef DRAGON_ALGOS_HIGHEST_POWER_OF_TWO_HPP
#define DRAGON_ALGOS_HIGHEST_POWER_OF_TWO_HPP

#include <iostream>
#include "dragon/core/constants.hpp"
namespace dragon {

/**
 * @return highest power of 2 not greater than n
 */
template <typename T> T cal_highest_power_of_two(T num) {
  std::size_t sz = (sizeof num) * details::bits_in_byte;
  const T one = static_cast<T>(1);
  if (num & (one << (sz - 1)))
    return (one << (sz - 1));

  size_t shift = 1;
  while (shift < sz) {
    num |= (num >> shift);
    shift *= 2;
  }
  return ((num + 1) >> 1);
}
} // namespace dragon
#endif