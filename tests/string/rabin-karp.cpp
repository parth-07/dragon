#include <string>
#include "dragon/string/rabin_karp.hpp"
#include "catch2/catch.hpp"

using Catch::Matchers::Contains;

TEST_CASE("rabin karp basic","[string][rabin_karp]") {
  std::string s = "crazy hello to crazy world";
  std::string pattern = "crazy";
  auto res = dragon::rabin_karp(s, pattern);
  REQUIRE_THAT(res, Contains(std::vector<unsigned int>{0, 15}));
}