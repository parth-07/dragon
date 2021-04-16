/**
 * Tree is an efficient, easy to use and generic template implementation
 * of basic tree data structure to conveniently use tree data structure and
 * perform tree operations.
 * This template class objects will further be used as tree parameter for various tree 
 * algorithms
 * 
 */
#ifndef DRAGON_TREE_TREE_HPP
#define DRAGON_TREE_TREE_HPP

#include <iostream>
#include <limits>
#include <map>
#include <vector>

namespace dragon {
  /**
   * Generic data structure to easily 
   * 
   * @param ValueT type of value of tree nodes
   * @param EdgeValueT type of weight of tree edges
   */
template <typename ValueT, typename EdgeValueT = int> class Tree {
public:
  using SizeType = std::size_t;
  using ValueType = ValueT;
  using EdgeValueType = EdgeValueT;
  using AdjacencyStructureType = std::map<SizeType, EdgeValueType>;

  //for consistency with STL
  using size_type = SizeType;  //NOLINT
  class Node;
private:
  template <typename U> using Sequence = std::vector<U>;
  using NodeSequenceType = Sequence<Node>;

public:
  using iterator = typename NodeSequenceType::iterator;             // NOLINT
  using const_iterator = typename NodeSequenceType::const_iterator; // NOLINT

public:
  enum class Color { white, grey, black };
  class Node {
  public:
    Node() = default;
    Node(const Node&) = default;
    Node(Node&&) noexcept = default;
    Node& operator=(const Node&) = default;
    Node& operator=(Node&&) noexcept = default;
    ~Node() = default;

    Node(ValueType p_value) : value(p_value) {} // NOLINT
    ValueType value;
    AdjacencyStructureType edges;
    // NOLINTNEXTLINE
    SizeType parent=npos, depth=npos, distance=npos;
    Color color = Color::white;
    Color color_for_impl = Color::white;
  };

public:
// Values for depecting no position and no weight, useful to be used as sentinel values.
  constexpr static SizeType npos = std::numeric_limits<SizeType>::max();
  constexpr static EdgeValueType nweight = std::numeric_limits<EdgeValueType>::max();

public:
// Default special member functions
  Tree(const Tree&) = default;
  Tree(Tree&&) noexcept = default;
  Tree& operator=(const Tree&) = default;
  Tree& operator=(Tree&&) noexcept = default;
  ~Tree() = default;

// Non-default constructors
  Tree(SizeType sz = 0, SizeType root = 0) {
    build(sz, root);
  };

// [] operator is overloaded to use tree[i] to 
// access i th node of the tree
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
  SizeType root() const {
    return m_root;
  }
  
  // Reset all nodes color attribute to Color::white
  void reset_color();
  // Reset all nodes color_for_impl attribute to Color::white
  void reset_color_for_impl();
  // As of now root value can only be changed while constructing or building the tree
  void build(SizeType sz,SizeType root=0);
  void clear();
  SizeType size() const {
    return m_nodes.size(); 
  }

private:
  NodeSequenceType m_nodes;
  SizeType m_root{};
public:
  const NodeSequenceType& nodes= m_nodes;
};

template<typename ValueT,typename EdgeValueT>
constexpr typename Tree<ValueT,EdgeValueT>::SizeType Tree<ValueT,EdgeValueT>::npos;

template<typename ValueT,typename EdgeValueT>
constexpr EdgeValueT Tree<ValueT,EdgeValueT>::nweight; 

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

template<typename ValueT,typename EdgeValueT>
void Tree<ValueT,EdgeValueT>::reset_color()
{
  for(auto &node : m_nodes) {
    node.color = Color::white;
  }
}

template<typename ValueT,typename EdgeValueT>
void Tree<ValueT,EdgeValueT>::reset_color_for_impl()
{
  for(auto &node : m_nodes) {
    node.color_for_impl = Color::white;
  }
}

template<typename ValueT, typename EdgeValueT>
void Tree<ValueT,EdgeValueT>::build(SizeType sz,SizeType root)
{
  clear();
  m_root = root;
  m_nodes.resize(sz);
}

template<typename ValueT, typename EdgeValueT>
void Tree<ValueT,EdgeValueT>::clear()
{
  m_nodes.clear();
}
} // namespace dragon
#endif