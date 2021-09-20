#include<iostream>
#include<vector>
#include "dragon/maths/chinese-remainder-theorem.hpp"

using namespace std;

int main()
{
  vector<int> a{1,2,3};
  vector<int> m{3,5,7};

  cout<<dragon::solve_typical_crt_problem(a,m)<<"\n";
}