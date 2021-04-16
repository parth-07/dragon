#ifndef DRAGON_GRAPH_MIN_SPANNING_TREE_HPP
#define DRAGON_GRAPH_MIN_SPANNING_TREE_HPP
#include <limits>
#include <utility>
#include <vector>

#include "dragon/graph/graph.hpp"
#include "dragon/tree/tree.hpp"

namespace dragon {

template<typename GraphT>
auto prim(GraphT graph, typename GraphT::SizeType root = GraphT::npos) {
  using ValueType = typename GraphT::ValueType;
  using EdgeValueType = typename GraphT::EdgeValueType;
  using SizeType = typename GraphT::SizeType;
  
  const EdgeValueType inf_weight = std::numeric_limits<EdgeValueType>::max();

  if (root == GraphT::npos) {
    root = graph.root();
  }

  std::vector<bool> selected(graph.size(),false);
  std::vector<std::pair<EdgeValueType, SizeType>> min_edge(graph.size(),{inf_weight, GraphT::npos});

  min_edge[root].first=0;
  min_edge[root].second=root;

  Tree<ValueType,EdgeValueType> tree(graph.size(),root);
  for (auto i = 0U; i<graph.size(); ++i) {
    SizeType u_i = GraphT::npos;
    for (auto j=0U; j<min_edge.size(); ++j) {
      if (!selected[j] && (u_i == GraphT::npos || min_edge[j].first < min_edge[u_i].first)) {
        u_i = j;
      }
    }
    if (u_i == GraphT::npos) {
      return Tree<ValueType,EdgeValueType>(0);
    }
    selected[u_i] = true;
    const auto& u = graph[u_i];
    for (auto j=0U; j<graph.size(); ++j) {
      if (u.edges.count(j)) {
        if (u.edges.at(j) < min_edge[j].first) {
          min_edge[j] = {u.edges.at(j), u_i};
        }
      }
    }
  }

  for (auto i=0U; i<min_edge.size(); ++i) {
    tree.add_undirected_edge(i,min_edge[i].second,min_edge[i].first);
  }
  tree.remove_undirected_edge(root, root);
  return tree;
}

} // namespace dragon

#endif