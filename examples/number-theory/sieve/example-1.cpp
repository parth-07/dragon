#include<iostream>
#include "dragon/number-theory/sieve.hpp"

using namespace std;

int main()
{
  dragon::Sieve<int> sieve(47);
  for(auto prime_num : sieve.prime)
    cout<<prime_num<<" ";
}