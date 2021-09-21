#include <iostream>

#include "dragon/graph/graph.hpp"

int main() {
  dragon::Graph<int, int> graph(7);
  for (int i=0; i<7; ++i) {
    graph[i].value = i;
  }

  // nodes are 0 index based.
  graph.add_directed_edge(0, 1);
  graph.add_directed_edge(0, 4);
  graph.add_directed_edge(1, 2);
  graph.add_directed_edge(1, 3);
  graph.add_directed_edge(4, 5);
  graph.add_directed_edge(5, 6);

  /**
   * Created graph is as follows:
   * 
   *              0
   *             / \
   *            1   4
   *           / \   \
   *          2   3   5
   *                   \
   *                    6                   
   */

  std::cout<<"Indices of node 4 immediate neighbours: ";
  for (auto edge : graph[4].edges) {
    std::cout<<edge.first<<" ";
  }
  std::cout<<"\n";
  std::cout<<"Value of node 6: "<<graph[6].value<<"\n";

  std::cout<<"Index of root of the tree: "<<graph.root()<<"\n";

  std::cout<<"Total number of nodes in the tree: "<<graph.size()<<"\n";

  // remove edge 1->3
  graph.remove_directed_edge(1, 3);
  // remove edge 4->6
  graph.remove_directed_edge(5, 6);

  /**
   * Updated tree is as follows:
   *              0
   *             / \
   *            1   4
   *           /     \
   *          2       5
   */

}