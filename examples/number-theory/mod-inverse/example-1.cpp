#include "dragon/number-theory/mod-inverse.hpp"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() {
  int a, m;
  a = 216;
  m = 7;
  cout << "Mod inverse using extended euclid algorithm = "
       << dragon::mod_inverse_using_extended_euclid(a, m) << endl;
  cout << "Mod inverse using binary exponentiation algorithm = "
       << dragon::mod_inverse_using_binary_exp(a, m)
       << endl; // can only be used if m is a prime number
}