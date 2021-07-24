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
      boost::property<boost::edge_reverse_t, traits::edge_descriptor>
    >
  >
>;

class edge_adder {
  graph &g;

 public:
  explicit edge_adder(graph &g) : g(g) {}

  void add_edge(int from, int to, int capacity, bool is_directed) {
    auto c_map = boost::get(boost::edge_capacity, g);
    auto r_map = boost::get(boost::edge_reverse, g);
    const auto e = boost::add_edge(from, to, g).first;
    const auto rev_e = boost::add_edge(to, from, g).first;
    c_map[e] = capacity;
    c_map[rev_e] = is_directed ? 0 : capacity; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

using vertex_desc = boost::graph_traits<graph>::vertex_descriptor;

template<typename T>
T load() {
  T val;
  std::cin >> val;
  return val;
}

void solve() {
  const int intersection_count = load<int>();
  const int street_count = load<int>();
  const int store_count = load<int>();

  graph g(intersection_count);
  edge_adder adder(g);
  const vertex_desc target = boost::add_vertex(g);

  // add edges from stores to target
  for(int i = 0; i < store_count; i++) {
    const int store_vertex = load<int>();
    adder.add_edge(store_vertex, target, 1, true);
  }

  // add all regular edges connecting intersections
  for(int i = 0; i < street_count; i++) {
    const int from = load<int>();
    const int to = load<int>();
    adder.add_edge(from, to, 1, false);
  }

  const int result = boost::push_relabel_max_flow(g, 0, target);
  std::cout << (result == store_count ? "yes" : "no") << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
  return 0;
}
