#include "dragon/algos/subset-xor-maximization.hpp"
#include "catch2/catch.hpp"
#include "vector"

TEST_CASE("maximum-subset-xor-value", "[subset-xor-maximization]") {
  std::vector<int> v = {48, 32, 31};
  REQUIRE(dragon::maximum_subset_xor_value(v) == 63);
  REQUIRE(dragon::maximum_subset_xor_value(v.begin(), v.end()) == 63);
}