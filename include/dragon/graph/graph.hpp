#ifndef DRAGON_GRAPH_GRAPH_HPP
#define DRAGON_GRAPH_GRAPH_HPP
#include <limits>
#include <map>
#include <vector>

namespace dragon {
/**
 * `Graph` is an efficient, easy to use generic implementation of the basic
 * graph data structure.
 * 
 * @param ValueT type of value of graph nodes.
 * @param EdgeValueT type of weight of graph edges.
 * 
 * @note `Graph` do not support multiple edges between the same nodes.
 */
template <typename ValueT, typename EdgeValueT = int> class Graph {
public:
  using ValueType = ValueT;
  using EdgeValueType = EdgeValueT;
  using SizeType = std::size_t;
  using AdjacencyStructureType = std::map<SizeType, EdgeValueType>;
  class Node;

  using size_type = SizeType; // NOLINT

private:
  template <typename T> using Sequence = std::vector<T>;
  using NodeSequenceType = Sequence<Node>;

public:
  using iterator = typename NodeSequenceType::iterator;             // NOLINT
  using const_iterator = typename NodeSequenceType::const_iterator; // NOLINT

public:
  static constexpr SizeType npos = std::numeric_limits<SizeType>::max();
  static constexpr EdgeValueType
      nweight = std::numeric_limits<EdgeValueType>::max();

public:
  Graph(SizeType sz = 0, SizeType root = 0) : m_root(root) {
    for (auto i = 0U; i < sz; ++i) {
      m_nodes.emplace_back(i);
    }
  }
  Graph(const Graph&) = default;
  Graph(Graph&&) noexcept = default;
  Graph& operator=(const Graph&) = default;
  Graph& operator=(Graph&&) noexcept = default;
  ~Graph() = default;

  /// Returns a reference to ith node of the graph.
  auto& operator[](SizeType index) { return m_nodes[index]; }
  auto& operator[](SizeType index) const { return m_nodes[index]; }

  /// Returns begin iterator for the nodes of the graph.
  auto begin() { return m_nodes.begin(); }
  auto begin() const { return m_nodes.begin(); }

  /// Returns end iterator for the nodes of the graph.
  auto end() { return m_nodes.end(); }
  auto end() const { return m_nodes.end(); }
  auto cbegin() const { return m_nodes.cbegin(); }
  auto cend() const { return m_nodes.cend(); }
  /**
   * Clears all nodes of the graph.
   */
  void clear();

  /**
   * Adds a weighted directed edge from node `u` to `v` (`u` -> `v`),
   * 
   * If an edge already exists from node `u` to node `v`, then the edge weight
   * is updated.
   * 
   * @param u first node of the edge.
   * @param v second node of the edge.
   * @param weight weight of the edge.
   */
  void add_directed_edge(SizeType u_i, SizeType v_i, EdgeValueType weight = 1);

  /**
   * Adds a weighted undirected edge between node `u` and `v`.
   * 
   * If an undirected edge already exists between nodes `u` and `v`, then the edge
   * weight is updated.
   * 
   * @param u first node of the edge.
   * @param v second node of the edge.
   * @param weight weight of the edge.
   */
  void add_undirected_edge(SizeType u_i, SizeType v_i,
                           EdgeValueType weight = 1);

  /**
   * Remove a directed edge from node `u` to `v`.
   * 
   * Does nothing if no directed edge exist from node `u` to `v`.
   * 
   * @param u_i index of the first node
   * @param v_i index of the second node
   */
  void remove_directed_edge(SizeType u_i, SizeType v_i);
  /**
   * Remove an undirected edge between nodes `u` and `v`.
   * 
   * Does nothing if no undirected edge exist between nodes `u` and `v`.
   */

  void remove_undirected_edge(SizeType u_i, SizeType v_i);

  /// Reset all nodes color to `Color::white`.
  void reset_color();

  /// Returns the number of nodes in the graph.
  auto size() const;  

  /// Returns the index of the root node.
  auto root() const;

  enum class Color { white, grey, black };

  /**
   * `Node` is a data structure to represent a node of the graph.
   */
  class Node {
  public:
    Node(SizeType index) : m_index(index) {}
    Node(SizeType index, ValueType p_value) : m_index(index), value(p_value) {}
    Node(const Node&) = default;
    Node(Node&&) noexcept = default;
    Node& operator=(const Node&) = default;
    Node& operator=(Node&&) noexcept = default;
    ~Node() = default;

  public:
    ValueType value;
    AdjacencyStructureType edges;
    Color color = Color::white;
    SizeType parent = npos, depth = npos;
  
  private:
    const SizeType m_index;
  };

public:
  const NodeSequenceType& nodes = m_nodes; // NOLINT

private:
  /// Stores nodes of the graph.
  NodeSequenceType m_nodes;
  /// Stores index of the root node.
  const SizeType m_root;
};

template <typename ValueT, typename EdgeValueT>
constexpr typename Graph<ValueT, EdgeValueT>::SizeType
    Graph<ValueT, EdgeValueT>::npos;
template <typename ValueT, typename EdgeValueT>
constexpr typename Graph<ValueT, EdgeValueT>::EdgeValueType
    Graph<ValueT, EdgeValueT>::nweight;

template <typename ValueT, typename EdgeValueT>
void Graph<ValueT, EdgeValueT>::add_directed_edge(SizeType u_i, SizeType v_i,
                                                  EdgeValueType weight) {
  m_nodes[u_i].edges[v_i] = weight;
}

template <typename ValueT, typename EdgeValueT>
void Graph<ValueT, EdgeValueT>::add_undirected_edge(SizeType u_i, SizeType v_i,
                                                    EdgeValueType weight) {
  m_nodes[u_i].edges[v_i] = weight;
  m_nodes[v_i].edges[u_i] = weight;
}

template <typename ValueT, typename EdgeValueT>
void Graph<ValueT, EdgeValueT>::remove_directed_edge(SizeType u_i,
                                                     SizeType v_i) {
  m_nodes[u_i].edges.erase(v_i);
}

template <typename ValueT, typename EdgeValueT>
void Graph<ValueT, EdgeValueT>::remove_undirected_edge(SizeType u_i,
                                                       SizeType v_i) {
  m_nodes[u_i].edges.erase(v_i);
  m_nodes[v_i].edges.erase(u_i);
}

template <typename ValueT, typename EdgeValueT>
void Graph<ValueT, EdgeValueT>::clear() {
  m_nodes.clear();
}

template <typename ValueT, typename EdgeValueT>
void Graph<ValueT, EdgeValueT>::reset_color() {
  for (auto& node : m_nodes) {
    node.color = Color::white;
  }
}

template <typename ValueT, typename EdgeValueT>
auto Graph<ValueT, EdgeValueT>::size() const {
  return m_nodes.size();
}

template <typename ValueT, typename EdgeValueT>
auto Graph<ValueT, EdgeValueT>::root() const {
  return m_root;
}

} // namespace dragon

#endif