#include "dragon/ds/sparse-table.hpp"
#include <iostream>
#include <limits>

using std::cout;
using std::endl;

using namespace std;

int main() {
  struct Min {
    int operator()(int a, int b) { return min(a,b); }
  };

  // identity value for min function is maximum value
  // possible for the value type of data
  dragon::SparseTable<int, Min> sparse_table(std::numeric_limits<int>::max());

  int arr[8] = {1, 3, 5, 7, 9, 11, 13, 15};

  sparse_table.build(arr,arr+8);

  cout << sparse_table.query(0, 2) << endl;
  cout << sparse_table.query(2, 3) << endl;
}
