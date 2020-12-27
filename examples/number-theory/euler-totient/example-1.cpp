#include<iostream>
#include "dragon/number-theory/euler-totient.hpp"

using namespace std;

int main()
{
  int a = 715;
  cout<<dragon::get_euler_totient(a)<<"\n";

  dragon::EulerTotient<int> euler(800);
  cout<<euler.get_totient(a)<<"\n";
  cout<<euler[a]<<"\n";
}