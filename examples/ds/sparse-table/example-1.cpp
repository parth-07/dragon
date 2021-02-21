#include "dragon/ds/sparse-table.hpp"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

using namespace std;

int main() {
  struct Sum {
    int operator()(int a, int b) { return a+b; }
  };
  // Identity value for sum function is 0
  dragon::SparseTable<int, Sum> sparse_table(0);

  vector<int> v{1, 3, 5, 7, 9, 11, 13, 15};

  sparse_table.build(v);

  cout << sparse_table.query(0, 2) << endl;
  cout << sparse_table.query(2, 3) << endl;
}
