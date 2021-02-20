#include "dragon/tree/tree.hpp"
#include <iostream>
#include <string>

int main() {
  dragon::Tree<std::string> tree;
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
  // Assigning some values to each node
  tree[0].value = "zero";
  tree[1].value = "one";
  tree[2].value = "two";
  tree[3].value = "three";
  tree[4].value = "four";
  tree[5].value = "five";
  tree[6].value = "six";
  tree[7].value = "seven";
  tree[8].value = "eight";
  tree[9].value = "nine";
  tree[10].value = "ten";
  tree[11].value = "eleven";
  tree[12].value = "twelve";
  tree[13].value = "thirteen";
  tree[14].value = "fourteen";
  tree[15].value = "fifteen";
  tree[16].value = "sixteen";

  // display nodes information using ordinary loop
  for (unsigned i = 0; i < tree.size(); ++i) {
    std::cout << i << "\n";
    std::cout << "value = " << tree[i].value << "\n";
    std::cout << "Number of adjacent nodes which can reached from node " << i
              << " = " << tree[i].edges.size() << "\n";
  }
  std::cout << "\n";

  // Display nodes information using range-based loop
  unsigned node_counter = 0;
  for (auto node : tree) {
    std::cout << node_counter << "\n";
    std::cout << "value = " << node.value << "\n";
    std::cout << "Number of adjacent nodes which can reached from node "
              << node_counter << " = " << node.edges.size() << "\n";
    node_counter++;
  }
}