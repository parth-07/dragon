#include <iostream>
#include "dragon/maths/factorization.hpp"

using std::cout;

int main() {
  int n = 16;
  auto factors = dragon::cal_factors(n);
  auto prime_factors = dragon::cal_prime_factorization(n);

  cout<<"Factors of "<<n<<" are: ";
  for (auto item : factors)
    cout<<item<<" ";
  cout<<"\n";

  cout<<"Prime factorization of "<<n<<" are ";
  for (auto item : prime_factors) 
    cout<<item<<" ";
}