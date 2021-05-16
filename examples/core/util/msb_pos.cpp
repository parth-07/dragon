#include <iostream>
#include "dragon/core/utils.hpp"

using std::cout;

int main() {
  cout<<dragon::details::msb_pos(7)<<"\n";
  cout<<dragon::details::msb_pos(65)<<"\n";
  cout<<dragon::details::msb_pos(0)<<"\n";
  cout<<dragon::details::msb_pos(1)<<"\n";
}