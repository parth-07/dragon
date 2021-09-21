#include <iostream>

#include "dragon/ds/disjoint_set_union.hpp"

int main() {
  dragon::DisjointSetUnion<int> dsu;

  for (int i=0; i<10; ++i)
    dsu.make_set(i);

  // Put all odd numbers in one set.
  dsu.join(1, 3);
  dsu.join(3, 5);
  dsu.join(5, 7);
  dsu.join(7, 9);

  // Put all even numbers in one set.
  dsu.join(0, 2);
  dsu.join(2, 4);
  dsu.join(4, 6);
  dsu.join(6, 8);
  
  // outputs 1 1 0
  std::cout<<dsu.in_same_set(1, 9)<<" ";
  std::cout<<dsu.in_same_set(2, 6)<<" ";
  std::cout<<dsu.in_same_set(1, 8)<<" ";
}