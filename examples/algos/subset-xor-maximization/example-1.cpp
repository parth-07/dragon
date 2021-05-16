#include <iostream>
#include <vector>
#include "dragon/algos/subset-xor-maximization.hpp"

int main() {
  std::vector<int> v{48, 32, 31};
  std::cout<<dragon::maximum_subset_xor_value(v)<<"\n";
  std::cout<<dragon::maximum_subset_xor_value(v.begin(), v.end())<<"\n";
}
