/**
 * Easy to use and efficient function to obtain euler tour of the provided 
 * tree, just pass the tree and get euler tour as return value.  
 * Two types of euler tour are currently supported:
 * 1) dragon::EulerTourStyle::basic - index of a node appears exactly two times.
 * 2) dragon::EulerTourStyle::repetitive - index of the node can appear multiple times
 * Consider tree is as follows:
 *                 0
 *               / | \ 
 *              1  2  3
 *              |
 *              4
 * Then basic euler tour of this tree will be as follows:     0,1,4,4,1,2,2,3,3,1
 * and repetitive euler tour of this tree will be as follows: 0,1,4,1,0,2,0,3,0
 */
#ifndef DRAGON_TREE_EULER_TOUR_HPP
#define DRAGON_TREE_EULER_TOUR_HPP

#include <iostream>
#include <vector>
#include "dragon/tree/tree.hpp"

namespace dragon {
enum class EulerTourStyle { basic, repetitive };

/**
 * @param TreeT should be a template class produced by dragon::Tree<ValueT,EdgeValueT> template
 * @param style
 * @returns std::vector<typename TreeT::SizeType> object containing euler tour of the provided tree
 */
template <typename TreeT>
auto euler_tour(TreeT& tree, EulerTourStyle style = EulerTourStyle::basic) {
  tree.reset_color_for_impl();
  std::vector<typename TreeT::SizeType> tour;
  tour.reserve(2*tree.size());
  euler_tour_base(tree, tour, tree.get_root(), style);
  return tour;
}

template <typename TreeT>
void euler_tour_base(TreeT& tree, std::vector<typename TreeT::SizeType>& tour,
                     typename TreeT::SizeType u_i, EulerTourStyle style) {
  tour.push_back(u_i);
  tree[u_i].color_for_impl = TreeT::Color::grey;
  for (auto edge : tree[u_i].edges) {
    auto v_i = edge.first;
    if (tree[v_i].color_for_impl == TreeT::Color::white) {
      euler_tour_base(tree, tour, v_i, style);
      if (style == EulerTourStyle::repetitive) {
        tour.push_back(u_i);
      }
    }
  }
  tree[u_i].color_for_impl = TreeT::Color::black;
  if (style == EulerTourStyle::basic) {
    tour.push_back(u_i);
  }
}
} // namespace dragon

#endif