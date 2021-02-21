#include <iostream>
#include <vector>
#include <algorithm>

#include "dragon/ds/sparse-table-idempotent.hpp"

int main() {
  int arr[6] = {0,1,2,3,5,4};
  struct Max {
    int operator()(int a,int b) {
      return std::max(a,b);
    }
  };
  dragon::SparseTableIdempotent<int,Max> st(arr,arr+6);

  std::cout<<st.query(0,3)<<"\n";
  std::cout<<st.query(3,3)<<"\n";
  std::cout<<st.query(3,5)<<"\n";
}