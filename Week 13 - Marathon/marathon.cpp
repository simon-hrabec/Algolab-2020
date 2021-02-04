#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using traits = boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS>;
using graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, int64_t,
    boost::property<boost::edge_residual_capacity_t, int64_t,
    boost::property<boost::edge_reverse_t, traits::edge_descriptor,
    boost::property <boost::edge_weight_t, int64_t>>>>
>;

class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, int64_t capacity, int64_t cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = capacity;
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;
    w_map[rev_e] = cost; 
  }
};

template <typename T>
T load(){
  T val;
  std::cin >> val;
  return val;
}

template <typename T>
struct iter_wrapper{
  T iter, iter_end;
  T begin() const {return iter;}
  T end() const {return iter_end;}
};

template <typename T>
iter_wrapper<typename T::first_type> range_loop_wrapper(const T& iter_pair) {
  return iter_wrapper<typename T::first_type>{iter_pair.first, iter_pair.second};
}

void dijsktra_wrapper(const graph &G, std::vector<int64_t> &distance_map, const int start_vertex) {
  boost::dijkstra_shortest_paths(G, start_vertex, boost::distance_map(
      boost::make_iterator_property_map(distance_map.begin(), boost::get(boost::vertex_index,G)))
  );
}

void solve() {
    const auto nr_cities = load<int>();
    const auto nr_streets = load<int>();
    const auto start = load<int>();
    const auto finish = load<int>();
    
    graph G(nr_cities);
    edge_adder adder(G);
    auto capacity_map = boost::get(boost::edge_capacity, G);
    auto weight_map = boost::get(boost::edge_weight, G);

    // Load edges and add them to graphs
    for(int i = 0; i < nr_streets; i++) {
      const auto from = load<int>();
      const auto to = load<int>();
      const auto capacity = load<int>();
      const auto distance = load<int>();

      adder.add_edge(from, to, capacity, distance);
    }

    // Run dijstra twice to find distances from both start and finish
    std::vector<int64_t> distance_from_start(nr_cities), distance_from_finish(nr_cities);
    dijsktra_wrapper(G, distance_from_start, start);
    dijsktra_wrapper(G, distance_from_finish, finish);
    const int64_t min_distance = distance_from_start[finish];

    // Discard edges that are not on the shortest path (paths)
    for(const auto &edge : range_loop_wrapper(boost::edges(G))) {
      const auto from = boost::source(edge, G);
      const auto to  = boost::target(edge, G);
      if (weight_map[edge] + distance_from_start[from] + distance_from_finish[to] != min_distance) {
        capacity_map[edge] = 0;
      }
    }

    const int64_t result = boost::push_relabel_max_flow(G, start, finish);
    std::cout << result << std::endl;
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
