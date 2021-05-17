#include "catch2/catch.hpp"
#include "dragon/algos/highest-power-of-two.hpp"
#include <iostream>

TEST_CASE("cal-highest-power-of-two", "[highest-power-of-two]") {
  int n = 7;
  REQUIRE(dragon::cal_highest_power_of_two(n) == 4);
  n = 79;
  REQUIRE(dragon::cal_highest_power_of_two(n) == 64);
}