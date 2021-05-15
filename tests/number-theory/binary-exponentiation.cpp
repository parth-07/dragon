#include "catch2/catch.hpp"
#include "dragon/number-theory/binary-exponentiation.hpp"

TEST_CASE("binary-exponentiation", "[binary-exponentiation]") {
  int a = 4, b = 5;
  REQUIRE(dragon::binary_exponentiation(4, 5) == 1024);
}

TEST_CASE("binary-exponentiation-with-mod", "[binary-exponentiation]") {
  int a = 4, b = 5, m=5;
  REQUIRE(dragon::binary_exponentiation(4, 5, 5) == 4);
}