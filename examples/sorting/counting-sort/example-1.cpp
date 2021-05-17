#include <iostream>
#include <vector>
#include <map>
#include "dragon/sorting/counting-sort.hpp"

int main() {
  std::vector<int> v{11, 23, 1, 7, 3};
  std::cout<<"Before sorting: ";
  for (auto item : v) {
    std::cout<<item<<" ";
  }
  std::cout<<"\n";
  dragon::counting_sort(v.begin(), v.end());
  std::cout<<"After sorting: ";
  for (auto item : v)
    std::cout<<item<<" ";

}