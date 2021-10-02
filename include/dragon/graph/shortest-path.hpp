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

} // namespace dragon

#endif