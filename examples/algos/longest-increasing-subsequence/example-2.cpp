#include<iostream>
#include "dragon/algos/longest-increasing-subsequence.hpp"

int main() {
  int arr[13] = {21,20,19,35,1,10,2,11,3,11,4,11,5};
  std::cout<<"Length of longest increasing subsequence = "<<dragon::longest_increasing_subsequence_length(arr,arr+13)<<std::endl;
}