#include <iostream>
#include <vector>

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

  void add_edge(int from, int to, int capacity) {
    auto c_map = boost::get(boost::edge_capacity, g);
    auto r_map = boost::get(boost::edge_reverse, g);
    const auto e = boost::add_edge(from, to, g).first;
    const auto rev_e = boost::add_edge(to, from, g).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
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
  const int location_count = load<int>();
  const int edge_count = load<int>();

  graph g(location_count);
  edge_adder adder(g);
  const vertex_desc source = boost::add_vertex(g);
  const vertex_desc target = boost::add_vertex(g);

  std::vector<int> demands(location_count);
  int required = 0;

  for(int i = 0; i < location_count; i++) {
    const int start_with = load<int>();
    const int end_with = load<int>();
    demands[i] += end_with-start_with;
  }

  for(int i = 0; i < edge_count; i++) {
    const int from = load<int>();
    const int to = load<int>();
    const int min_flow = load<int>();
    const int max_flow = load<int>();

    const int difference = max_flow-min_flow;
    if (difference) {
      adder.add_edge(from, to, difference);
    }

    demands[from] += min_flow;
    demands[to] -= min_flow;
  }

  for(int i = 0; i < location_count; i++) {
    if (demands[i] > 0) {
      adder.add_edge(i, target, demands[i]);
      required += demands[i];
    } else if (demands[i] < 0) {
      adder.add_edge(source, i, -demands[i]);
    }
  }

  const int flow = boost::push_relabel_max_flow(g, source, target);
  std::cout << (flow == required ? "yes" : "no") << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
  return 0;
}
