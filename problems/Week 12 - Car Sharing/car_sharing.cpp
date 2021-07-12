#include <iostream>
#include <vector>
#include <array>
#include <array>
#include <map>
#include <algorithm>

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

using vi = std::vector<int>;
using t5i = std::tuple<int, int, int, int, int>;
using vt5i = std::vector<t5i>;
using vi = std::vector<int>;
template <typename T>
T load() {
  T val;
  std::cin >> val;
  return val;
}

template<typename T>
T loadv(const int count) {
  T v(count);
  for(int i = 0; i < count; i++) {
    std::cin >> v[i];
  }
  return v;
}

vt5i loadvt5i(const int count) {
  vt5i v;
  v.reserve(count);
  for(int i = 0; i < count; i++) {
    int a, b, c, d, e;
    std::cin >> a >> b >> c >> d >> e;
    v.emplace_back(a-1, b-1, c, d, e);
  }
  return v;
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
  const auto nr_requests = load<int>();
  const auto nr_stations = load<int>();
  const auto cars_present = loadv<vi>(nr_stations);
  const auto requests = loadvt5i(nr_requests);

  const int cars_total = std::accumulate(std::begin(cars_present), std::end(cars_present), 0);
  std::array<std::map<int, int>, 10> time_points;

  // Fill all the time points for the stations
  for(int i = 0; i < nr_stations; i++) {
    time_points[i].emplace(0, 0);
    time_points[i].emplace(100'000, 0);
  }

  for(const auto &[from_station, to_station, departure_time, arrival_time, payment] : requests) {
    time_points[from_station].emplace(departure_time, 0);
    time_points[to_station].emplace(arrival_time, 0);
  }

  // Mark them with unique index
  int node_idx = 0;
  for(int i = 0; i < nr_stations; i++) {
    for(auto &[key, value] : time_points[i]) {
      value = node_idx++;
    }
  }

  // Create the graph
  graph G(node_idx);
  edge_adder adder(G);
  const vertex_desc source = boost::add_vertex(G);
  const vertex_desc target = boost::add_vertex(G);

  // Create the default edges (car not used)
  for(int i = 0; i < nr_stations; i++) {
    const int first = time_points[i].begin()->second;
    const int last = time_points[i].rbegin()->second;
    adder.add_edge(source, first, cars_present[i], 0);
    adder.add_edge(last, target, cars_total, 0);

    auto previous = time_points[i].begin();
    for(auto it = ++std::begin(time_points[i]); it != std::end(time_points[i]); ++it) {
      adder.add_edge(previous->second, it->second, cars_total, 100*(it->first - previous->first));
      previous = it;
    }
  }

  // Create edges for usage of a car
  for(const auto &[from_station, to_station, departure_time, arrival_time, payment] : requests) {
    const int from_idx = time_points[from_station][departure_time];
    const int to_idx = time_points[to_station][arrival_time];
    adder.add_edge(from_idx, to_idx, 1, (arrival_time-departure_time)*100 - payment);
  }

  boost::successive_shortest_path_nonnegative_weights(G, source, target);
  const int cost = boost::find_flow_cost(G);
  const int result = cars_total*100'000l*100l - cost;

  std::cout << result << std::endl;
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
