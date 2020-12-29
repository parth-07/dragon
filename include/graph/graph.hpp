#ifndef GRAPH_GRAPH_HPP
#define GRAPH_GRAPH_HPP
#include <limits>
#include <map>
#include <vector>

namespace dragon {
template <typename ValueT, typename EdgeValueT = int> class Graph {
public:
  using ValueType = ValueT;
  using EdgeValueType = EdgeValueT;
  using SizeType = size_t;
  using AdjacencyStructureType = std::map<SizeType, EdgeValueType>;
  class Node;

private:
  template <typename T> using Sequence = std::vector<T>;
  using NodeSequenceType = Sequence<Node>;

public:
  static constexpr SizeType npos = std::numeric_limits<SizeType>::max();
  static constexpr SizeType nweight = std::numeric_limits<EdgeValueType>::max();

public:
  Graph(SizeType sz = 0, SizeType root = 0)
      : m_nodes(NodeSequenceType(sz)), m_root(root) {}
  Graph(const Graph&) = default;
  Graph(Graph &&) noexcept = default;
  Graph& operator=(const Graph&) = default;
  Graph& operator=(Graph&&) noexcept = default;
  ~Graph() = default;

  auto operator[](SizeType index) { return m_nodes[index]; }
  auto operator[](SizeType index) const { return m_nodes[index]; }

  auto begin() { return m_nodes.begin(); }
  auto begin() const { return m_nodes.begin(); }
  auto end() { return m_nodes.end(); }
  auto end() const { return m_nodes.end(); }
  auto cbegin() const { return m_nodes.cbegin(); }
  auto cend() const { return m_nodes.cend(); }

  void add_directed_edge(SizeType u_i, SizeType v_i, EdgeValueType weight = 1);
  void add_undirected_edge(SizeType u_i, SizeType v_i, EdgeValueType weight = 1);

  void remove_directed_edge(SizeType u_i,SizeType v_i);
  void remove_undirected_edge(SizeType u_i,SizeType v_i);

private:
public:
  enum class Color { white, grey, black };
  class Node {
  public:
    Node(ValueType p_value) : value(p_value) {}
    Node() = default;
    Node(const Node&) = default;
    Node(Node&&) noexcept = default;
    Node& operator=(const Node&) = default;
    Node& operator=(Node&&) noexcept = default;
    ~Node() = default;

  public:
    ValueType value;
    AdjacencyStructureType edges;
    Color color = Color::white;
    SizeType parent=npos, depth=npos;
  };

private:
  NodeSequenceType m_nodes;
  const SizeType m_root;

public:
  const NodeSequenceType& nodes = m_nodes;  //NOLINT
};

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

template<typename ValueT,typename EdgeValueT>
void Graph<ValueT,EdgeValueT>::remove_directed_edge(SizeType u_i,SizeType v_i)
{
  m_nodes[u_i].erase(v_i);
}

template<typename ValueT, typename EdgeValueT>
void Graph<ValueT,EdgeValueT>::remove_undirected_edge(SizeType u_i,SizeType v_i)
{
  m_nodes[u_i].erase(v_i);
  m_nodes[v_i].erase(u_i);
}

} // namespace dragon

#endif