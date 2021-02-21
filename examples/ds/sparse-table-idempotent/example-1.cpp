#include <iostream>
#include <vector>
#include "dragon/ds/sparse-table-idempotent.hpp"

using namespace std;

int main()
{
  struct Min {
    int operator()(int a,int b) {
      return min(a,b);
    }
  };
  vector<int> v{1,11,3,5,4,12};
  dragon::SparseTableIdempotent<int,Min> st;
  st.build(v);
  cout<<st.query(0,5)<<"\n";
  cout<<st.query(3,5)<<"\n";
}
