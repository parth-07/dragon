#include "catch2/catch.hpp"
#include "dragon/graph/min_spanning_tree.hpp"

TEST_CASE("min spanning tree basic", "[min-spanning-tree][graph]") {
  dragon::Graph<int> graph(5);
  graph.add_undirected_edge(0, 1, 1);
  graph.add_undirected_edge(0, 3, 2);
  graph.add_undirected_edge(0, 2, 10);
  graph.add_undirected_edge(1, 2, 11);
  graph.add_undirected_edge(1, 4, 3);
  graph.add_undirected_edge(2, 3, 12);
  graph.add_undirected_edge(2, 4, 13);
  graph.add_undirected_edge(3, 4, 4);

  auto prim_tree = dragon::prim(graph);
  auto kruskal_tree = dragon::kruskal(graph);

  int prim_wt, kruskal_wt;
  prim_wt = kruskal_wt = 0;

  for (auto node : prim_tree) {
    for (auto edge : node.edges) {
      prim_wt += edge.second;
    }
  }
  prim_wt /= 2;

  for (auto node : kruskal_tree) {
    for (auto edge : node.edges) {
      kruskal_wt += edge.second;
    }
  }
  kruskal_wt /= 2;

  REQUIRE(prim_wt == 16);
  REQUIRE(kruskal_wt == 16);
}