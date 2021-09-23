#include "dragon/tree/tree.hpp"
#include <iostream>

int main() {
  dragon::Tree<int> tree;
  // tree will have 17 nodes, from index 0 to 16
  // node having index 0 is root of the tree
  tree.build(17, 0);

  tree.add_undirected_edge(0, 1);
  tree.add_undirected_edge(0, 2);
  tree.add_undirected_edge(0, 3);
  tree.add_undirected_edge(1, 4);
  tree.add_undirected_edge(4, 7);
  tree.add_undirected_edge(4, 8);
  tree.add_undirected_edge(2, 5);
  tree.add_undirected_edge(5, 9);
  tree.add_undirected_edge(5, 10);
  tree.add_undirected_edge(9, 11);
  tree.add_undirected_edge(11, 15);
  tree.add_undirected_edge(11, 16);
  tree.add_undirected_edge(10, 12);
  tree.add_undirected_edge(10, 13);
  tree.add_undirected_edge(10, 14);
  tree.add_undirected_edge(3, 6);

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

  // To display adjacent nodes which can be reached from node with index 10
  for (auto edge : tree[10].edges) {
    // edge.first gives index of the node
    // edge.second gives weight of the node
    std::cout << edge.first << " ";
  }
  std::cout << "\n";
  tree.clear(); // Clear the tree;

  // building tree having 5 nodes and node with index 2 as root
  tree.build(5, 2);

  tree.add_directed_edge(2, 3);
  tree.add_directed_edge(2, 4);
  tree.add_directed_edge(2, 0);
  tree.add_directed_edge(4, 1);

  /**
   *               2
   *             / | \
   *            3  4  0
   *               |
   *               1
   */

  // To display adjacent nodes which can be reached from node with index 4
  for (auto edge : tree[4].edges) {
    std::cout << edge.first << " ";
  }
}