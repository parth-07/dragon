#include "dragon/sorting/counting-sort.hpp"
#include "catch2/catch.hpp"
#include <iostream>
#include <vector>

using Catch::Matchers::Equals;

TEST_CASE("counting-sort-basic", "[counting-sort][sorting]") {
  std::vector<int> v{11, 45, 98, 1, 11, 7};
  dragon::counting_sort(v.begin(), v.end());
  REQUIRE_THAT(v, Equals(std::vector<int>{1, 7, 11, 11, 45, 98}));
}

TEST_CASE("counting-sort-composite", "[counting-sort][sorting]") {
  struct Character {
    std::string name;
    int rank;
    bool operator==(const Character& rhs) const {
      return name == rhs.name && rank == rhs.rank;
    }

    bool operator!=(const Character& rhs) const { return !(*this == rhs); }
  };
  std::vector<Character> characters = {{"Mikasa", 5},
                                       {"Touka", 1},
                                       {"Kugisaki", 7},
                                       {"Kurisu", 4},
                                       {"Christina", 3}};
  dragon::counting_sort(
      characters.begin(), characters.end(),
      [](const Character& character) { return character.rank; });
  REQUIRE_THAT(characters, Equals(std::vector<Character>{{"Touka", 1},
                                                         {"Christina", 3},
                                                         {"Kurisu", 4},
                                                         {"Mikasa", 5},
                                                         {"Kugisaki", 7}}));
}