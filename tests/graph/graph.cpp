#include "catch2/catch.hpp"
#include "dragon/graph/graph.hpp"

TEST_CASE("graph basic", "[graph][graph_graph]") {
  dragon::Graph<int, int> graph(7);
  for (int i=0; i<7; ++i)
    graph[i].value = i;

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

  REQUIRE(graph[4].edges.begin()->first == 5);

  REQUIRE(graph[6].value == 6);

  REQUIRE(graph.root() == 0);

  REQUIRE(graph.size() == 7);

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
  
  REQUIRE(graph[5].edges.empty());
  REQUIRE(graph[1].edges.size() == 1);
}