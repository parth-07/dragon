#ifndef DRAGON_GRAPH_MIN_SPANNING_TREE_HPP
#define DRAGON_GRAPH_MIN_SPANNING_TREE_HPP

#include "dragon/graph/graph.hpp"
#include "dragon/tree/tree.hpp"
#include "dragon/ds/disjoint_set_union.hpp"

#include <limits>
#include <set>
#include <utility>
#include <vector>


namespace dragon {

template<typename GraphT>
auto prim(const GraphT& graph, typename GraphT::SizeType root = GraphT::npos) {
  using ValueType = typename GraphT::ValueType;
  using EdgeValueType = typename GraphT::EdgeValueType;
  using SizeType = typename GraphT::SizeType;

  const EdgeValueType inf_weight = std::numeric_limits<EdgeValueType>::max();

  if (root == GraphT::npos) {
    root = graph.root();
  }

  // use set as the priority queue for finding safe edge at each iteration.
  std::set<std::pair<EdgeValueType, SizeType>> setpq;
  for (auto u_i=0U; u_i<graph.size(); ++u_i) {
    setpq.insert({inf_weight, u_i});
  }

  // Make root weight = 0 in the priority queue.
  setpq.erase({inf_weight, root});
  setpq.insert({0, root});

  std::vector<EdgeValueType> min_weight(graph.size(), inf_weight);
  min_weight[root] = 0;

  // tree to represent the minimum spanning tree
  Tree<ValueType, EdgeValueType> tree(graph.size(), root);
  tree[root].parent = root;

  while (! setpq.empty()) {
    // index of the next node to insert.
    SizeType u_i = setpq.begin()->second;
    setpq.erase(setpq.begin());

    // Given graph is not fully connected.
    // Return empty tree to denote that the minimum spanning tree cannot be formed.
    if (min_weight[u_i] == inf_weight) {
      return Tree<ValueType,EdgeValueType>(0);
    }

    const auto& u = graph[u_i];
    for (auto edge : u.edges) {
      auto v_i = edge.first;
      if (! setpq.count({min_weight[v_i], v_i}))
        continue;
      if (edge.second < min_weight[v_i]) {
        setpq.erase({min_weight[v_i], v_i});
        min_weight[v_i] = edge.second;
        setpq.insert({min_weight[v_i], v_i});
        tree[v_i].parent = u_i;
      }
    }
  }

  for (auto u_i=0U; u_i<graph.size(); ++u_i) {
    tree.add_undirected_edge(u_i, tree[u_i].parent, min_weight[u_i]);
  }
  tree[root].edges.erase(root);
  return tree;
}

template<class GraphT>
auto kruskal(const GraphT& graph, typename GraphT::SizeType root = GraphT::npos) {
  using SizeType = typename GraphT::SizeType;
  using EdgeValueType = typename GraphT::EdgeValueType;

  if (root == GraphT::npos) {
    root = graph.root();
  }

  DisjointSetUnion<SizeType> dsu;

  for (auto u_i=0U; u_i < graph.size(); ++u_i) {
    dsu.make_set(u_i);
  }

  std::set<std::pair<EdgeValueType, std::pair<SizeType, SizeType>>> setpq;

  for (auto u_i=0U; u_i<graph.size(); ++u_i) {
    for (auto edge : graph[u_i].edges) {
      auto v_i = edge.first;
      setpq.insert({edge.second, {u_i, v_i}});
    }
  }

  Tree<typename GraphT::ValueType, EdgeValueType> tree(graph.size(), root);

  SizeType num_of_edges = 0;

  while (! setpq.empty()) {
    auto vertices = setpq.begin()->second;
    auto u_i = vertices.first;
    auto v_i = vertices.second;

    if (! dsu.in_same_set(u_i, v_i)) {
      dsu.join(u_i, v_i);
      tree.add_undirected_edge(u_i, v_i, graph[u_i].edges.at(v_i));
      ++num_of_edges;
    }
    setpq.erase(setpq.begin());
  }
  if (num_of_edges != graph.size()-1)
    return Tree<typename GraphT::ValueType, EdgeValueType>(0);
  return tree;
}

} // namespace dragon

#endif