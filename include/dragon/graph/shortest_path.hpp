#ifndef DRAGON_GRAPH_SHORTEST_PATH_HPP
#define DRAGON_GRAPH_SHORTEST_PATH_HPP
#include <limits>
#include <set>
#include <utility>
#include <vector>
#include "dragon/graph/graph.hpp"

namespace dragon {
template <typename GraphT>
std::vector<typename GraphT::EdgeValueType>
djikstra(const GraphT& graph, typename GraphT::SizeType source = GraphT::npos) {
  using SizeType = typename GraphT::SizeType;
  using EdgeValueType = typename GraphT::EdgeValueType;
  if (source == GraphT::npos)
    source = graph.root();
  const auto inf_weight = std::numeric_limits<EdgeValueType>::max();
  std::vector<EdgeValueType> shortest_paths_weight(graph.size(), inf_weight);
  shortest_paths_weight[source] = 0;
  std::set<std::pair<EdgeValueType, SizeType>> priority_q;
  for (auto i = 0U; i < shortest_paths_weight.size(); ++i) {
    priority_q.insert({shortest_paths_weight[i], i});
  }
  while (!priority_q.empty()) {
    auto top = *priority_q.begin();
    if (top.first == inf_weight) {
      break;
    }
    priority_q.erase(priority_q.begin());
    const auto& u = graph[top.second];
    for (auto edge : u.edges) {
      auto v_i = edge.first;
      auto temp_dist = top.first + edge.second;
      auto& cur_dist = shortest_paths_weight[v_i];
      if (temp_dist < cur_dist) {
        priority_q.erase({cur_dist, v_i});
        cur_dist = temp_dist;
        priority_q.insert({cur_dist, v_i});
      }
    }
  }
  return shortest_paths_weight;
}

template <class GraphT>
bool bellman_ford(const GraphT& graph,
                  std::vector<typename GraphT::EdgeValueType>& shortest_path_wt,
                  typename GraphT::SizeType source = GraphT::npos) {
  using SizeType = typename GraphT::SizeType;
  using EdgeValueType = typename GraphT::EdgeValueType;

  if (source == GraphT::npos) {
    source = graph.root();
  }
  EdgeValueType inf_wt = std::numeric_limits<EdgeValueType>::max();
  shortest_path_wt.clear();
  shortest_path_wt.resize(graph.size(), inf_wt);
  shortest_path_wt[source] = 0;
  for (auto i = 0U; i < graph.size() - 1; ++i) {
    for (const auto& u : graph) {
      SizeType u_i = u.index();
      if (shortest_path_wt[u_i] == inf_wt)
        continue;
      for (const auto& edge : u.edges) {
        if (shortest_path_wt[u_i] + edge.second <
            shortest_path_wt[edge.first]) {
          SizeType v_i = edge.first;
          shortest_path_wt[v_i] = shortest_path_wt[u_i] + edge.second;
        }
      }
    }
  }

  for (const auto& u : graph) {
    for (const auto& edge : u.edges) {
      SizeType u_i = u.index();
      SizeType v_i = edge.first;
      if (shortest_path_wt[v_i] > shortest_path_wt[u_i] + edge.second)
        return false;
    }
  }
  return true;
}
} // namespace dragon

#endif