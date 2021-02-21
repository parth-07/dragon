/**
 * Easy to use and efficient data structure to find 
 * longest common ancestor of any pair of nodes in the 
 * provided tree.
 * 
 * Time complexity:
 *  building - O(NlgN)
 *  query - O(1)
 *  Here N is number of nodes in the tree.
 *  
 */
#ifndef DRAGON_TREE_LOWEST_COMMON_ANCESTOR_HPP
#define DRAGON_TREE_LOWEST_COMMON_ANCESTOR_HPP

#include "dragon/ds/sparse-table-idempotent.hpp"
#include "dragon/tree/euler-tour.hpp"
#include "dragon/tree/tree.hpp"
#include <iostream>
#include <utility>
#include <vector>

namespace dragon {
  /**
   * @param TreeT - should be template class produced by dragon::Tree<ValueT,EdgeValueT> template
   */
template <typename TreeT> class LowestCommonAncestor {
public:
  using SizeType = typename TreeT::SizeType;
  // For consistency with STL
  using size_type = SizeType;
private:
  template <typename T> using Sequence = std::vector<T>;

public:
  // Special member functions
  LowestCommonAncestor() = default;
  LowestCommonAncestor(const LowestCommonAncestor&) = default;
  LowestCommonAncestor& operator=(const LowestCommonAncestor&) = default;
  LowestCommonAncestor(LowestCommonAncestor&&) noexcept = default;
  LowestCommonAncestor& operator=(LowestCommonAncestor&&) noexcept = default;
  ~LowestCommonAncestor() = default;

  LowestCommonAncestor(TreeT& tree) { build(tree); }

  void build(TreeT& tree);
  SizeType lca(SizeType u_i, SizeType v_i) const;
  void clear();

private:
  void refresh_depth(TreeT& tree);
  void refresh_depth_base(TreeT& tree, SizeType u_i);

  struct Min {
    auto operator()(std::pair<SizeType, SizeType> a,
                    std::pair<SizeType, SizeType> b) {
      if (a.second < b.second) {
        return a;
      } else {
        return b;
      }
    }
  };
  Sequence<SizeType> m_tour;
  Sequence<SizeType> m_first_seen;
  Sequence<std::pair<SizeType, SizeType>> m_depth;
  SparseTableIdempotent<std::pair<SizeType, SizeType>, Min> m_st;
};

template <typename TreeT> void LowestCommonAncestor<TreeT>::build(TreeT& tree) {
  m_tour.clear();
  m_first_seen.clear();
  m_depth.clear();

  m_tour = euler_tour(tree, EulerTourStyle::repetitive);
  refresh_depth(tree);
  m_first_seen.resize(tree.size(), TreeT::npos);
  m_depth.resize(m_tour.size());

  for (unsigned i = 0; i < m_tour.size(); ++i) {
    auto u_i = m_tour[i];
    if (m_first_seen[u_i] == TreeT::npos) {
      m_first_seen[u_i] = i;
    }
    m_depth[i] = {u_i, tree[u_i].depth};
  }

  m_st.build(m_depth);
}

/**
 * 
 */
template <typename TreeT>
typename LowestCommonAncestor<TreeT>::SizeType
LowestCommonAncestor<TreeT>::lca(SizeType u_i, SizeType v_i) const {
  u_i = m_first_seen[u_i];
  v_i = m_first_seen[v_i];
  SizeType l = std::min(u_i, v_i);
  SizeType r = std::max(u_i, v_i);
  return m_st.query(l, r).first;
}

template <typename TreeT>
void LowestCommonAncestor<TreeT>::refresh_depth(TreeT& tree) {
  tree.reset_color_for_impl();
  for (auto& node : tree) {
    node.depth = TreeT::npos;
  }
  tree[tree.get_root()].depth = 0;
  refresh_depth_base(tree, tree.get_root());
}

template <typename TreeT>
void LowestCommonAncestor<TreeT>::refresh_depth_base(TreeT& tree,
                                                     SizeType u_i) {
  auto& u = tree[u_i];
  u.color_for_impl = TreeT::Color::grey;
  for (auto edge : u.edges) {
    auto v_i = edge.first;
    auto& v = tree[v_i];
    if (v.color_for_impl == TreeT::Color::white) {
      v.depth = u.depth + 1;
      refresh_depth_base(tree, v_i);
    }
  }
  u.color_for_impl = TreeT::Color::black;
}

template<typename TreeT>
void LowestCommonAncestor<TreeT>::clear() {
  m_tour.clear();
  m_first_seen.clear();
  m_depth.clear();
  m_st.clear();
}
} // namespace dragon

#endif