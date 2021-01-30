#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

using traits = boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS>;
using graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property,
  boost::property<boost::edge_capacity_t, long,
  boost::property<boost::edge_residual_capacity_t, long,
  boost::property<boost::edge_reverse_t, traits::edge_descriptor,
  boost::property<boost::edge_weight_t, long
>>>>>;

using edge_desc = boost::graph_traits<graph>::edge_descriptor;
using vertex_desc = boost::graph_traits<graph>::vertex_descriptor;

template<typename T>
T load() {
  T val;
  std::cin >> val;
  return val;
}

class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};

void solve() {
  const auto nr_boats = load<int>();
  const auto nr_sailors = load<int>();
  const auto nr_pairs = load<int>();

  const int sailor_offset = nr_boats;
  graph G(nr_boats + nr_sailors);
  edge_adder adder(G);
  const vertex_desc source = boost::add_vertex(G);
  const vertex_desc target = boost::add_vertex(G);

  // Add edges for boats
  for(int i = 0; i < nr_boats; i++) {
    adder.add_edge(source, i, 1, 0);
    adder.add_edge(i, target, 1, 50);
  }

  // Add edges for sailors
  for(int i = 0; i < nr_sailors; i++) {
    adder.add_edge(i+sailor_offset, target, 1, 0);
  }

  // Add edges between boats and sailors
  for(int i = 0; i < nr_pairs; i++) {
    const auto from_boat = load<int>();
    const auto to_sailor = load<int>();
    const auto factor = load<int>();
    adder.add_edge(from_boat, to_sailor+sailor_offset, 1, 50-factor);
  }

  boost::successive_shortest_path_nonnegative_weights(G, source, target);
  const int cost = boost::find_flow_cost(G);
  const int result = nr_boats*50-cost;

  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
}
