#include <bits/stdc++.h>

#include "dragon/maths/binary-exponentiation.hpp"

using std::cin;
using std::cout;
using std::endl;

int main() {
  long long a, b, m;
  m = 3;
  a = 4;
  b = 5;
  cout << dragon::binary_exponentiation(a, b, m) << endl;
  cout << dragon::binary_exponentiation(a, b) << endl;
}