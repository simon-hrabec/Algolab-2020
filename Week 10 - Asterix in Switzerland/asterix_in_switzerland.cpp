#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using traits = boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS>;
using graph = boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::directedS,
  boost::no_property,
  boost::property<boost::edge_capacity_t, int,
  boost::property<boost::edge_residual_capacity_t, int,
  boost::property<boost::edge_reverse_t, traits::edge_descriptor
>>>>;

using vertex_desc = boost::graph_traits<graph>::vertex_descriptor;

class edge_adder {
  graph &g;

 public:
  explicit edge_adder(graph &g) : g(g) {}

  void add_edge(int from, int to, int capacity) {
    auto c_map = boost::get(boost::edge_capacity, g);
    auto r_map = boost::get(boost::edge_reverse, g);
    const auto e = boost::add_edge(from, to, g).first;
    const auto rev_e = boost::add_edge(to, from, g).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0;
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

template<typename T>
T load(){
  T val;
  std::cin >> val;
  return val;
}

void solve() {
  const int vertex_count = load<int>();
  const int edge_count = load<int>();
  
  graph G(vertex_count);
  edge_adder adder(G);
  const vertex_desc source = boost::add_vertex(G);
  const vertex_desc target = boost::add_vertex(G);
  
  int in = 0;
  
  for(int i = 0; i < vertex_count; i++) {
    int value = load<int>();
    if (value > 0) {
      adder.add_edge(source, i, value);
      in += value;
    }
    if (value < 0) {
      adder.add_edge(i, target, -value);
    }
  }
  
  for(int i = 0; i < edge_count; i++) {
    const int from = load<int>();
    const int to = load<int>();
    const int value = load<int>();
    
    adder.add_edge(from, to, value);
  }
  
  const int flow = boost::push_relabel_max_flow(G, source, target);
  std::cout << (flow < in ? "yes" : "no") << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int T;
  std::cin >> T;
  while(T--) {
    solve();
  }
  return 0;
}
