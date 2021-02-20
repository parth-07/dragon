#include<iostream>
#include<vector>
#include "dragon/ds/segment-tree.hpp"

int main()
{
  std::vector<int> v{1,2,3,4,5,6,7,8,9,10};
  struct sum {
    int operator()(int a,int b) {
      return a+b;
    }
  };
  // Construct SegmentTree having sum as query functor for sequences
  // of values of type int, and with function identity value = 0,
  // here source sequence is vector v
  dragon::SegmentTree<int,sum> segtree(0,v);

  // query in range [2,3] (inclusive range)
  // queries are 0-indexing based
  std::cout<<segtree.query(2,3)<<"\n";
  std::cout<<segtree.query(2,5)<<"\n";
  // update value at 5th index to 100
  segtree.update(5,100);
  std::cout<<segtree.query(2,5)<<"\n";
}