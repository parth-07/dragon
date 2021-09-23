#ifndef DRAGON_TREE_TREE_HPP
#define DRAGON_TREE_TREE_HPP

#include <iostream>
#include <limits>
#include <map>
#include <vector>

namespace dragon {
/**
 * `Tree` is an efficient and easy to use generic implementation of the basic
 * tree data structure.
 *
 * @param ValueT type of value of tree nodes
 * @param EdgeValueT type of weight of tree edges
 *
 * @note `Tree` do not supports multiple edges between the same nodes.
 */
template <typename ValueT, typename EdgeValueT = int> class Tree {
public:
  using SizeType = std::size_t;
  using ValueType = ValueT;
  using EdgeValueType = EdgeValueT;
  using AdjacencyStructureType = std::map<SizeType, EdgeValueType>;

  // for consistency with STL
  using size_type = SizeType; // NOLINT
  class Node;

private:
  template <typename U> using Sequence = std::vector<U>;
  using NodeSequenceType = Sequence<Node>;

public:
  using iterator = typename NodeSequenceType::iterator;             // NOLINT
  using const_iterator = typename NodeSequenceType::const_iterator; // NOLINT

public:
  enum class Color { white, grey, black };
  /**
   * `Node` is a data structure to represent a node of the tree.
   */
  class Node {
  public:
    Node(const Node&) = default;
    Node(Node&&) noexcept = default;
    Node& operator=(const Node&) = default;
    Node& operator=(Node&&) noexcept = default;
    ~Node() = default;

    Node(SizeType index) : m_index(index) {}
    Node(SizeType index, ValueType p_value)
        : m_index(index), value(p_value) {} // NOLINT

    SizeType index() const {
      return m_index;
    }
    
    ValueType value;
    AdjacencyStructureType edges;
    SizeType parent = npos, depth = npos, distance = npos;
    Color color = Color::white;
    Color color_for_impl = Color::white;

  private:
    const SizeType m_index;
  };

public:
  // Sentinel value for invalid position.
  constexpr static SizeType npos = std::numeric_limits<SizeType>::max();
  // Sentinel value for invalid weight.
  constexpr static EdgeValueType
      nweight = std::numeric_limits<EdgeValueType>::max();

public:
  Tree(const Tree&) = default;
  Tree(Tree&&) noexcept = default;
  Tree& operator=(const Tree&) = default;
  Tree& operator=(Tree&&) noexcept = default;
  ~Tree() = default;

  /// Initialise tree with size and root.
  Tree(SizeType sz = 0, SizeType root = 0) { build(sz, root); };

  
  /// Returns reference to the ith node of the tree.
  auto& operator[](SizeType i) { return m_nodes[i]; }
  auto& operator[](SizeType i) const { return m_nodes[i]; }

  /// Returns begin iterator for the nodes of the tree.
  iterator begin() { return m_nodes.begin(); }
  const_iterator begin() const { return m_nodes.begin(); }
  const_iterator cbegin() const { return m_nodes.cbegin(); }

  /// Returns end iterator for the nodes of the tree.
  iterator end() { return m_nodes.end(); }
  const_iterator end() const { return m_nodes.end(); }
  const_iterator cend() const { return m_nodes.cend(); }


  /**
   * Adds a weighted directed edge from node `u` to node `v` (`u` -> `v`).
   * 
   * If an edge already exists from node `u` to node `v`, then the edge weight
   * is updated.
   * 
   * @param u first node for the edge.
   * @param v second node for the edge.
   * @param weight weight for the edge.
   */
  void add_directed_edge(Node& u, Node& v, EdgeValueType weight = 1);
  void add_directed_edge(SizeType u_i, SizeType v_i, EdgeValueType weight = 1);
  
  /**
   * Adds a weighted undirected edge between nodes `u` and `v`.
   * 
   * If an undirected edge already exists between nodes `u` and `v`, then the
   * edge weight is updated.
   * 
   * @param u first node of the edge
   * @param v second node of the edge
   * @param weight weight of the edge.
   */
  void add_undirected_edge(SizeType u_i, SizeType v_i,
                           EdgeValueType weight = 1);
  void add_undirected_edge(Node& u, Node& v, EdgeValueType weight = 1);

  /**
   * Removes a directed edge from node `u` to `v`.
   * 
   * Does nothing if no directed edge exists from node `u` to `v`.
   */
  void remove_directed_edge(SizeType u_i, SizeType v_i);
  void remove_directed_edge(Node& u, Node& v);

  /**
   * Removes an undirected edge between nodes `u` and `v`.
   * 
   * Does nothing if no undirected edge exists between nodes `u` and `v`.
   */
  void remove_undirected_edge(SizeType u_i, SizeType v_i);
  void remove_undirected_edge(Node& u, Node& v);

  /// Returns index of the root node.
  SizeType root() const { return m_root; }

  /// Reset all nodes color attribute to `Color::white`.
  void reset_color();

  /// Reset all nodes color_for_impl attribute to `Color::white`
  void reset_color_for_impl();

  /**
   * Builds a tree with `sz` number of nodes and node with index `root` as the
   * root node.
   * 
   * @param sz number of nodes that the tree should contain.
   * @param root index of the root node.
   * 
   * @Note As of now root value can only be changed while constructing or building the
   * tree.
   */
  void build(SizeType sz, SizeType root = 0);

  /// Clears all the nodes of the tree.
  void clear();

  /// Returns the number of nodes in the tree.
  SizeType size() const { return m_nodes.size(); }

public:
  const NodeSequenceType& nodes = m_nodes;

private:
  NodeSequenceType m_nodes;
  SizeType m_root{};

};

template <typename ValueT, typename EdgeValueT>
constexpr
    typename Tree<ValueT, EdgeValueT>::SizeType Tree<ValueT, EdgeValueT>::npos;

template <typename ValueT, typename EdgeValueT>
constexpr EdgeValueT Tree<ValueT, EdgeValueT>::nweight;

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

template <typename ValueT, typename EdgeValueT>
void Tree<ValueT, EdgeValueT>::reset_color() {
  for (auto& node : m_nodes) {
    node.color = Color::white;
  }
}

template <typename ValueT, typename EdgeValueT>
void Tree<ValueT, EdgeValueT>::reset_color_for_impl() {
  for (auto& node : m_nodes) {
    node.color_for_impl = Color::white;
  }
}

template <typename ValueT, typename EdgeValueT>
void Tree<ValueT, EdgeValueT>::build(SizeType sz, SizeType root) {
  clear();
  m_root = root;
  for (auto i=0U; i<sz; ++i) {
    m_nodes.emplace_back(i);
  }
}

template <typename ValueT, typename EdgeValueT>
void Tree<ValueT, EdgeValueT>::clear() {
  m_nodes.clear();
}
} // namespace dragon
#endif