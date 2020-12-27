#include<iostream>
#include<vector>
#include "dragon/ds/segment-tree.hpp"

using namespace std;

int main()
{
  vector<int> v{1,2,3,4,5,6,7,8,9,10};
  struct sum {
    int operator()(int a,int b) {
      return a+b;
    }
  };
  dragon::SegmentTree<int,sum> segtree(0,v);

  cout<<segtree.query(2,3)<<"\n";
  cout<<segtree.query(2,5)<<"\n";
}