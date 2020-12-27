#ifndef DRAGON_TREE_TREE_HPP
#define DRAGON_TREE_TREE_HPP
#include <bits/stdc++.h>

namespace dragon {
template <typename ValueT, typename EdgeValueT = int> class Tree {
public:
  using SizeType = size_t;
  using ValueType = ValueT;
  using EdgeValueType = EdgeValueT;
  using EdgeType = std::map<SizeType, EdgeValueType>;
  class Node;

private:
  template <typename U> using Sequence = std::vector<U>;
  using NodeSequenceType = Sequence<Node>;

public:
  using iterator = typename NodeSequenceType::iterator;             // NOLINT
  using const_iterator = typename NodeSequenceType::const_iterator; // NOLINT

public:
  constexpr static SizeType npos = std::numeric_limits<SizeType>::max();
  constexpr static SizeType nweight = std::numeric_limits<EdgeValueType>::max();

public:
  Tree(SizeType sz = 0, SizeType root = 0)
      : m_nodes(decltype(m_nodes)(sz)), m_root(root){};

  Tree(const Tree&) = default;
  Tree(Tree&&) noexcept = default;

  Tree& operator=(const Tree&) = default;
  Tree& operator=(Tree&&) noexcept = default;

  ~Tree() = default;

  Node& operator[](SizeType u_i) { return m_nodes[u_i]; }
  const Node& operator[](SizeType u_i) const { return m_nodes[u_i]; }

  iterator begin() { return m_nodes.begin(); }
  iterator end() { return m_nodes.end(); }

  const_iterator begin() const { return m_nodes.begin(); }
  const_iterator end() const { return m_nodes.end(); }

  const_iterator cbegin() const { return m_nodes.cbegin(); }
  const_iterator cend() const { return m_nodes.cend(); }

  void add_directed_edge(SizeType u_i, SizeType v_i, EdgeValueType weight = 1);
  void add_undirected_edge(SizeType u_i, SizeType v_i,
                           EdgeValueType weight = 1);
  void remove_directed_edge(SizeType u_i, SizeType v_i);
  void remove_undirected_edge(SizeType u_i, SizeType v_i);

  void reset_color();

public:
  enum class Color { white, grey, black };
  class Node {
  public:
    Node(ValueType p_value = 0) : value(p_value) {} // NOLINT
    Node(const Node&) = default;
    Node(Node&&) noexcept = default;
    Node& operator=(const Node&) = default;
    Node& operator=(Node&&) noexcept = default;
    ~Node() = default;

    ValueType value;
    EdgeType edges;
    // NOLINTNEXTLINE
    SizeType parent, depth;
    Color color = Color::white;
  };

private:
  NodeSequenceType m_nodes;
  const SizeType m_root;
};

template <typename ValueT, typename EdgeValueT>
void Tree<ValueT, EdgeValueT>::add_directed_edge(SizeType u_i, SizeType v_i,
                                                 EdgeValueType weight) {
  m_nodes[u_i].edges[v_i] = weight;
}

template <typename ValueT, typename EdgeValueT>
void Tree<ValueT, EdgeValueT>::add_undirected_edge(SizeType u_i, SizeType v_i,
                                                   EdgeValueType weight) {
  m_nodes[u_i].edges[v_i] = weight;
  m_nodes[v_i].edges[u_i] = weight;
}

template <typename ValueT, typename EdgeValueT>
void Tree<ValueT, EdgeValueT>::remove_directed_edge(SizeType u_i,
                                                    SizeType v_i) {
  m_nodes[u_i].edges.erase(v_i);
}

template <typename ValueT, typename EdgeValueT>
void Tree<ValueT, EdgeValueT>::remove_undirected_edge(SizeType u_i,
                                                      SizeType v_i) {
  m_nodes[u_i].edges.erase(v_i);
  m_nodes[v_i].edges.erase(u_i);
}
} // namespace dragon
#endif