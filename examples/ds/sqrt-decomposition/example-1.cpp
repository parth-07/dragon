#include<iostream>
#include<vector>
#include "dragon/ds/sqrt-decomposition.hpp"

using namespace std;

int main()
{
  vector<int> a{1,2,3,4,5,6,7,8,9,10};
  struct Sum{
    int operator()(int a,int b) {
      return a+b;
    }
  };
  dragon::SqrtDecomposition<int,Sum> sd(0,a);
  cout<<sd.query(1,3)<<"\n";
  cout<<sd.query(0,3)<<"\n";
  sd.update(2,10);
  cout<<sd.query(1,3)<<"\n";
  cout<<sd.query(0,3)<<"\n";
}