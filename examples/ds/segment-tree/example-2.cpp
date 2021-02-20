#include <iostream>
#include <limits>
#include "dragon/ds/segment-tree.hpp"

int main()
{
  int arr[11] = {0,1,2,3,4,5,6,7,8,9,10};
  struct Max {
    int operator()(int a,int b) {
      return std::max(a,b);
    }
  };
  // Construct SegmentTree having Min as query functor for sequences
  // of values of type int, and with function identity value = std::numeric_limits<int>::min(),
  // here source sequence is array a
  dragon::SegmentTree<int,Max> segtree(std::numeric_limits<int>::min(),arr,arr+11);

  // query in range [2,3] (inclusive range)
  // queries are 0-indexing based
  std::cout<<segtree.query(2,3)<<"\n";
  std::cout<<segtree.query(2,5)<<"\n";
  // update value at 5th index to 100
  segtree.update(5,100);
  std::cout<<segtree.query(2,5)<<"\n";

  // Clear the data structure, and make it ready for 
  // building segment tree again on some different sequence
  segtree.clear();

  int arr_2[5] = {11,22,44,33,55};
  segtree.build(arr_2,arr_2+5);

  std::cout<<segtree.query(1,3)<<"\n";
}