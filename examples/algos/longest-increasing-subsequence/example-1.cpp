#include <iostream>
#include <vector>
#include "dragon/algos/longest-increasing-subsequence.hpp"

int main()
{
  std::vector<int> v{11,13,5,15,6,11,7,11,9,1};
  std::cout<<"Length of longest increasing subsequence = "<<dragon::longest_increasing_subsequence_length(v)<<std::endl;
  std::cout<<"Length of longest increasing subsequence = "<<dragon::longest_increasing_subsequence_length(v.begin(),v.end())<<std::endl;
  std::cout<<"Length of longest increasing subsequence = "<<dragon::longest_increasing_subsequence_length(v.cbegin(),v.cend())<<std::endl;
  
}