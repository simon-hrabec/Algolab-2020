#include <iostream>
#include <vector>
#include <tuple>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

using traits = boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS>;
using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
    boost::property<boost::edge_residual_capacity_t, long,
    boost::property<boost::edge_reverse_t, traits::edge_descriptor,
    boost::property<boost::edge_weight_t, long>>>>>;

using edge_desc = boost::graph_traits<Graph>::edge_descriptor;

class edge_adder {
 Graph &G;

 public:
  explicit edge_adder(Graph &G) : G(G) {}
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

template<typename T>
T load(){
  T val;
  std::cin >> val;
  return val;
}

void solve(){
  const int nr_cities = load<int>();
  const int nr_guides = load<int>();
  const int budget = load<int>();
  const int start = load<int>();
  const int finish = load<int>();

  int start_capacity = 0, finish_capacity = 0;

  std::vector<std::tuple<int, int, int, int>> guides(nr_guides);
  for(int i = 0; i < nr_guides; i++) {
    const int from = load<int>();
    const int to = load<int>();
    const int unit_cost = load<int>();
    const int capacity = load<int>();
    guides[i] = {from, to, unit_cost, capacity};

    if(from == start) {
      start_capacity += capacity;
    }

    if(to == finish) {
      finish_capacity += capacity;
    }
  }

  int low = 0, high = std::min(start_capacity, finish_capacity);
  while (true) {
    const int mid = (low+high+1)/2;

    Graph G(nr_cities);
    edge_adder adder(G);
    const auto source = boost::add_vertex(G);

    adder.add_edge(source, start, mid, 0);

    for(const auto[from, to, cost, capacity] : guides) {
      adder.add_edge(from, to, capacity, cost);
    }

    boost::successive_shortest_path_nonnegative_weights(G, source, finish);
    auto c_map = boost::get(boost::edge_capacity, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);
    const auto first_edge = *boost::out_edges(boost::vertex(source, G), G).first;

    const int cost = boost::find_flow_cost(G);
    const int flow = c_map[first_edge] - rc_map[first_edge];

    if (low == high || (cost <= budget && flow < mid)) {
      std::cout << flow << std::endl;
      break;
    }

    if (cost > budget) {
      high = mid-1;
    } else {
      low = mid;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T;
  std::cin >> T;
  while(T--) {
    solve();
  }
  return 0;
}
