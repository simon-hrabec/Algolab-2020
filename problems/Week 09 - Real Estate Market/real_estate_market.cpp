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

using out_edge_iter = boost::graph_traits<graph>::out_edge_iterator;
using edge_desc = boost::graph_traits<graph>::edge_descriptor;
using vertex_desc = boost::graph_traits<graph>::vertex_descriptor;

class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0;
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;
    w_map[rev_e] = -cost;
  }
};

int max_flow_in_graph(const graph &G, const int source) {
  auto c_map = boost::get(boost::edge_capacity, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);

  int flow = 0;
  out_edge_iter e, eend;
  for(boost::tie(e, eend) = boost::out_edges(boost::vertex(source,G), G); e != eend; ++e) {
    flow += c_map[*e] - rc_map[*e];     
  }

  return flow;
}

template <typename T>
T load() {
  T val;
  std::cin >> val;
  return val;
}

void solve() {
  const int buyer_count = load<int>();
  const int house_count = load<int>();
  const int state_count = load<int>();

  const int total_vertex_count = buyer_count + house_count + state_count;
  graph G(total_vertex_count);
  edge_adder adder(G);
  const vertex_desc source = boost::add_vertex(G);
  const vertex_desc target = boost::add_vertex(G);

  const int house_offset = buyer_count;
  const int state_offset = buyer_count + house_count;

  for(int i = 0; i < buyer_count; i++) {
    const int buyer = i;
    adder.add_edge(source, buyer, 1, 0);
  }

  for(int i = 0; i < state_count; i++) {
    const int state_max = load<int>();
    const int state = i+state_offset;
    adder.add_edge(state, target, state_max, 0);
  }

  for(int i = 0; i < house_count; i++) {
    const int house_state = load<int>()-1;
    const int house = i+house_offset;
    const int state = house_state+state_offset;
    adder.add_edge(house, state, 1, 0);
  }

  for(int i = 0; i < buyer_count; i++) {
    for(int j = 0; j < house_count; j++) {
      const int bid = load<int>();
      const int buyer = i;
      const int house = j+house_offset;
      adder.add_edge(buyer, house, 1, -bid+100);
    }
  }

  boost::successive_shortest_path_nonnegative_weights(G, source, target);
  const int result_houses = max_flow_in_graph(G, source);
  const int result_profit = -boost::find_flow_cost(G) + result_houses*100;

  std::cout << result_houses << " " << result_profit << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T;
  std::cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
