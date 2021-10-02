#include "dragon/graph/shortest_path.hpp"
#include <iostream>
#include <vector>

int main() {
  dragon::Graph<int, int> graph(6, 0);
  graph.add_directed_edge(0, 1, 1);
  graph.add_directed_edge(0, 3, 2);
  graph.add_directed_edge(1, 2, 4);
  graph.add_directed_edge(2, 3, 8);
  graph.add_directed_edge(3, 4, 5);
  graph.add_directed_edge(4, 5, 7);
  graph.add_directed_edge(1, 2, 4);
  graph.add_directed_edge(5, 3, 6);

  std::vector<decltype(graph)::EdgeValueType> bellman_ford_shortest_path_wt;
  bool valid = dragon::bellman_ford(graph, bellman_ford_shortest_path_wt);
  if (!valid)
    std::cout << "Negative weight cycle exists !!\n";
  else {
    std::cout << "Shortest path weights as calculated using bellman "
                 "ford:\n";
    for (auto i = 0U; i < graph.size(); ++i) {
      std::cout << "Shortest path of " << graph.root() << "->" << i << ": "
                << bellman_ford_shortest_path_wt[i] << "\n";
    }
  }
  std::cout<<"\n";
  auto djikstra_shortest_path_wt = dragon::djikstra(graph);
  std::cout << "Shortest path weights as calculated using djikstra:\n";
  for (auto i = 0U; i < graph.size(); ++i) {
    std::cout << "Shortest path of " << graph.root() << "->" << i << ": "
              << bellman_ford_shortest_path_wt[i] << "\n";
  }
}
