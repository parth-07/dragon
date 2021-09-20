#include "dragon/maths/extended-euclid-gcd.hpp"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() {
  int a, b;
  int x, y;

  a = 5;
  b = 7;
  int g = dragon::gcd(a, b, x, y);

  /* cout<<(-5%2)<<endl;
  cout<<(5%-2)<<endl;
  cout<<(-5%-2)<<endl;
  cout<<(4%-4)<<endl; */
  cout << a << "*" << x << "+" << b << "*" << y << " = " << g << endl;
}
