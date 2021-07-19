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

template <typename T>
T load(){
  T val;
  std::cin >> val;
  return val;
}

void solve(){
  const int stop_count = load<int>();
  const int mission_count = load<int>();
  const int train_limit = load<int>();
  const int step_max = 128;

  graph G(stop_count);
  edge_adder adder(G);
  const vertex_desc source = boost::add_vertex(G);

  for(int i = 0; i < mission_count; i++) {
    const int from = load<int>();
    const int to = load<int>();
    const int priority = load<int>();
    
    adder.add_edge(from, to, 1, (to-from) * step_max - priority);
  }

  adder.add_edge(source, 0, train_limit, 0);
  for(int i = 0; i < stop_count-1; i++) {
    adder.add_edge(i, i+1, train_limit, step_max);
  }

  boost::successive_shortest_path_nonnegative_weights(G, source, stop_count-1);
  const int cost = boost::find_flow_cost(G);
  const int result = train_limit * step_max * (stop_count-1) - cost;

  std::cout << result << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int T;
  std::cin >> T;
  while(T--) {
    solve();
  }
}
