#include "dragon/graph/shortest_path.hpp"
#include "catch2/catch.hpp"
#include <vector>

TEST_CASE("shortest path basic","[graph][shortest_path]") {
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
  auto djikstra_shortest_path_wt = dragon::djikstra(graph);

  REQUIRE(djikstra_shortest_path_wt[0] == bellman_ford_shortest_path_wt[0]);
  REQUIRE(djikstra_shortest_path_wt[0] == 0);
  REQUIRE(djikstra_shortest_path_wt[1] == bellman_ford_shortest_path_wt[1]);
  REQUIRE(djikstra_shortest_path_wt[1] == 1);
  REQUIRE(djikstra_shortest_path_wt[2] == bellman_ford_shortest_path_wt[2]);
  REQUIRE(djikstra_shortest_path_wt[2] == 5);
  REQUIRE(djikstra_shortest_path_wt[3] == bellman_ford_shortest_path_wt[3]);
  REQUIRE(djikstra_shortest_path_wt[3] == 2);
  REQUIRE(djikstra_shortest_path_wt[4] == bellman_ford_shortest_path_wt[4]);
  REQUIRE(djikstra_shortest_path_wt[4] == 7);
  REQUIRE(djikstra_shortest_path_wt[5] == bellman_ford_shortest_path_wt[5]);
  REQUIRE(djikstra_shortest_path_wt[5] == 14);
}
