#include "dragon/tree/tree.hpp"
#include "catch2/catch.hpp"

TEST_CASE("tree basic", "[tree][tree_tree]") {
  dragon::Tree<int> tree;
  tree.build(17, 0);

  tree.add_directed_edge(0, 1);
  tree.add_directed_edge(0, 2);
  tree.add_directed_edge(0, 3);
  tree.add_directed_edge(1, 4);
  tree.add_directed_edge(4, 7);
  tree.add_directed_edge(4, 8);
  tree.add_directed_edge(2, 5);
  tree.add_directed_edge(5, 9);
  tree.add_directed_edge(5, 10);
  tree.add_directed_edge(9, 11);
  tree.add_directed_edge(11, 15);
  tree.add_directed_edge(11, 16);
  tree.add_directed_edge(10, 12);
  tree.add_directed_edge(10, 13);
  tree.add_directed_edge(10, 14);
  tree.add_directed_edge(3, 6);

  /** Visual Representation of the given tree
   *  here node represents index of the node.
   *
   *               0
   *             / | \
   *           1   2   3
   *          /    |    \
   *         4     5     6
   *        / \   / \
   *       7   8 9   10
   *            /   / | \
   *           11  12 13 14
   *          / \
   *         15  16
   */

  REQUIRE(tree.size() == 17);
  REQUIRE(tree[3].edges.size() == 1);
  REQUIRE(tree[13].edges.empty());
  REQUIRE(tree[10].edges.find(13) != tree[10].edges.end());
}