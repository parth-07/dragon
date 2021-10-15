#include <iostream>

#include "dragon/string/rabin_karp.hpp"

int main() {
  std::string s = "crazy hello to crazy world";
  std::string p = "crazy";
  auto crazy_positions = dragon::rabin_karp(s, p);
  for (auto pos : crazy_positions) {
    std::cout<<pos<<" ";
  }

}