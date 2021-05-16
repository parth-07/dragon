#include <iostream>
#include "catch2/catch.hpp"
#include "dragon/core/utils.hpp"

TEST_CASE("msb-pos","[core-utility]") {
  REQUIRE(dragon::details::msb_pos(7) == 2);
  REQUIRE(dragon::details::msb_pos(65) == 6);
  REQUIRE(dragon::details::msb_pos(0) == -1);
  REQUIRE(dragon::details::msb_pos(1) == 0);
} 