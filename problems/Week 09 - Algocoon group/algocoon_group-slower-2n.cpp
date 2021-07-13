#include <iostream>
#include <limits>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using traits = boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS>;
using graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
            boost::property<boost::edge_capacity_t, long,
            boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>>;

using edge_desc = boost::graph_traits<graph>::edge_descriptor;

class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
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
  const auto figure_count = load<int>();
  const auto limb_count = load<int>();

  graph G(figure_count);
  edge_adder adder(G);

  for(int i = 0; i < limb_count; i++) {
    const int from = load<int>();
    const int to = load<int>();
    const int cost = load<int>();

    adder.add_edge(from, to, cost);
  }

  long flow = std::numeric_limits<long>::max();
  for(int i = 1; i < figure_count; i++) {
    flow = std::min(flow, boost::push_relabel_max_flow(G, 0, i));
    flow = std::min(flow, boost::push_relabel_max_flow(G, i, 0));
  }

  std::cout << flow << std::endl;
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
