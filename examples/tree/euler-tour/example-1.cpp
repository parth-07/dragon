#include <iostream>
#include "dragon/tree/tree.hpp"
#include "dragon/tree/euler-tour.hpp"

int main() {
  dragon::Tree<int> tree;
  // tree will have 17 nodes, from index 0 to 16 
  // node having index 0 is root of the tree
  tree.build(17,0);

  tree.add_undirected_edge(0,1);
  tree.add_undirected_edge(0,2);
  tree.add_undirected_edge(0,3);
  tree.add_undirected_edge(1,4);
  tree.add_undirected_edge(4,7);
  tree.add_undirected_edge(4,8);
  tree.add_undirected_edge(2,5);
  tree.add_undirected_edge(5,9);
  tree.add_undirected_edge(5,10);
  tree.add_undirected_edge(9,11);
  tree.add_undirected_edge(11,15);
  tree.add_undirected_edge(11,16);
  tree.add_undirected_edge(10,12);
  tree.add_undirected_edge(10,13);
  tree.add_undirected_edge(10,14);
  tree.add_undirected_edge(3,6);

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

  auto tour = dragon::euler_tour(tree,dragon::EulerTourStyle::basic);
  std::cout<<"dragon::EulerTourStyle::basic tour"<<"\n";
  for(auto item : tour) {
    std::cout<<item<<" ";
  }
  std::cout<<"\n";
  std::cout<<"dragon::EulerTourStyle::repetitive"<<"\n";
  tour = dragon::euler_tour(tree,dragon::EulerTourStyle::repetitive);
  for(auto item : tour) {
    std::cout<<item<<" ";
  }
}