#include "catch2/catch.hpp"
#include "dragon/ds/disjoint_set_union.hpp"

TEST_CASE("disjoint_set_union basic", "[ds][disjoint_set_union]") {
  dragon::DisjointSetUnion<int> dsu;
  for (int i=0; i<= 10; ++i) {
    dsu.make_set(i);
  }

  SECTION("odd even sets test") {
    // Put all odd numbers in one set.
    dsu.join(1, 3);
    dsu.join(3, 5);
    dsu.join(5, 7);
    dsu.join(7, 9);

    // Put all even numbers in one set.
    dsu.join(0, 2);
    dsu.join(2, 4);
    dsu.join(4, 6);
    dsu.join(6, 8);
    dsu.join(8, 10);

    REQUIRE(dsu.in_same_set(1, 9));
    REQUIRE(dsu.in_same_set(2, 8));
    REQUIRE_FALSE(dsu.in_same_set(1, 8));
  }
}