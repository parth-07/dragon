#include "dragon/number-theory/factorization.hpp"
#include "catch2/catch.hpp"
#include <iostream>

using Catch::Matchers::Equals;

TEST_CASE("prime-factorization", "[factorization]") {
  int n = 21;
  REQUIRE_THAT(dragon::cal_prime_factorization(n), Equals(std::vector<int>{3, 7}));
}

TEST_CASE("factors", "[factorization]") {
  int n = 21;
  REQUIRE_THAT(dragon::cal_factors(n), Equals(std::vector<int>{1, 3, 7, 21}));
}