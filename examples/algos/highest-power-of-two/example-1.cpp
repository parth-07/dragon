#include "dragon/algos/highest-power-of-two.hpp"
#include <iostream>

int main() {
  int n = 7;
  std::cout<<dragon::cal_highest_power_of_two(n)<<"\n";
  n = 79;
  std::cout<<dragon::cal_highest_power_of_two(n)<<"\n";
}