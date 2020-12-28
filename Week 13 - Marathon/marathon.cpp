#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

namespace distance{
  using graph = boost::adjacency_list< 
    boost::vecS, 
    boost::vecS, 
    boost::undirectedS,
    boost::no_property,
    boost::property<boost::edge_weight_t, int>
  >;
  using weight_map = boost::property_map<graph, boost::edge_weight_t>::type;  
}

namespace flow {
  using traits = boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS>;
  using graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
      boost::property<boost::edge_capacity_t, int64_t,
      boost::property<boost::edge_residual_capacity_t, int64_t,
      boost::property<boost::edge_reverse_t, traits::edge_descriptor,
      boost::property <boost::edge_weight_t, int64_t>>>>
  >;
}

template <typename T>
T load(){
  T val;
  std::cin >> val;
  return val;
}

void solve() {
    const int nr_cities = load<int>();
    const int nr_streets = load<int>();
    const int start = load<int>();
    const int finish = load<int>();
    
    // Graph definition (for min distance)
    distance::graph DG(nr_cities);
    distance::weight_map distance_weights = boost::get(boost::edge_weight, DG);
    const auto add_edge_to_distance_graph = [&DG, distance_weights](const int from, const int to, const int distance){
      const auto edge = boost::add_edge(from, to, DG).first;
      distance_weights[edge] = distance;
    };
    
    // Graph definition (for flow cost binary search)
    flow::graph FG(nr_cities);
    const auto source = boost::add_vertex(FG);
    auto flow_c_map = boost::get(boost::edge_capacity, FG);
    auto flow_r_map = boost::get(boost::edge_reverse, FG);
    auto flow_w_map = boost::get(boost::edge_weight, FG); // new!
    const auto add_edge_to_flow_graph = [&flow_c_map, &flow_r_map, &flow_w_map, &FG](const int from, const int to, const int capacity, const int cost){
      const auto edge = boost::add_edge(from, to, FG).first;
      const auto rev_edge = boost::add_edge(to, from, FG).first;
      flow_c_map[edge] = capacity;
      flow_c_map[rev_edge] = 0;
      flow_r_map[edge] = rev_edge;
      flow_r_map[rev_edge] = edge;
      flow_w_map[edge] = cost;
      flow_w_map[rev_edge] = -cost;
    };
    
    // Load edges and add them to graphs
    for(int i = 0; i < nr_streets; i++) {
      const int from = load<int>();
      const int to = load<int>();
      const int capacity = load<int>();
      const int distance = load<int>();
      
      add_edge_to_distance_graph(from, to, distance);
      add_edge_to_flow_graph(from, to, capacity, distance);
      add_edge_to_flow_graph(to, from, capacity, distance);
    }
    
    // Add special edge to regulate max capacity
    const auto source_edge = boost::add_edge(source, start, FG).first;
    const auto source_rev_edge = boost::add_edge(start, source, FG).first;
    flow_c_map[source_edge] = std::numeric_limits<int>::max();
    flow_c_map[source_rev_edge] = 0;
    flow_r_map[source_edge] = source_rev_edge;
    flow_r_map[source_rev_edge] = source_edge;
    flow_w_map[source_edge] = 0;
    flow_w_map[source_rev_edge] = 0;
    
    // Save set capacity
    const auto flow_c_map_backup = flow_c_map;
    const auto set_graph_to_max_cap = [source_edge, &flow_c_map, &flow_c_map_backup](const int capacity){
      flow_c_map = flow_c_map_backup;
      flow_c_map[source_edge] = capacity;
    };
    
    // Run dijkstra to find the shortest path
    std::vector<int> dist_map(nr_cities);
    boost::dijkstra_shortest_paths(DG, start,
      boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, DG))));
    const int total_distance = dist_map[finish];
    
    // Run binary search to find biggest possible number of participants
    const long max_capacity = boost::push_relabel_max_flow(FG, source, finish);
    long low = 1, high = max_capacity;
    while(low != high) {
      const long mid = (low+high+1)/2;
      const long expected_cost = total_distance * mid;
      set_graph_to_max_cap(mid);
      boost::successive_shortest_path_nonnegative_weights(FG, source, finish);
      const long cost = boost::find_flow_cost(FG);
      if (cost == expected_cost) {
        low = mid;
      } else {
        high = mid-1;
      }
    }
    
    std::cout << low << std::endl;
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
