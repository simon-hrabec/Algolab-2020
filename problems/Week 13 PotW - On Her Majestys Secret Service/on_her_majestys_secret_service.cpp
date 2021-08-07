#include <iostream>
#include <vector>
#include <limits>
#include <array>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using distance_graph = boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::directedS,
  boost::no_property,
  boost::property<boost::edge_weight_t, int>
>;

using matching_graph = boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::undirectedS,
  boost::no_property
>;
using matching_graph_vertex_desc = boost::graph_traits<matching_graph>::vertex_descriptor;

using vi = std::vector<int>;

template <typename T>
T load(){
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

void solve() {
  // Load data
  const int vertex_count = load<int>();
  const int edge_count = load<int>();
  const int agent_count = load<int>();
  const int shelter_count = load<int>();
  const int capacity = load<int>();
  const int enter_time = load<int>();

  distance_graph DG(vertex_count);
  const auto add_edge = [weights = boost::get(boost::edge_weight, DG), &DG](const int from, const int to, const int weight){
    const auto edge = boost::add_edge(from, to, DG).first;
    weights[edge] = weight;
  };

  // Construct input graph (distance graph) 
  for(int i = 0; i < edge_count; i++) {
    const bool both_sides = (load<char>() == 'L');
    const int from = load<int>();
    const int to = load<int>();
    const int weight = load<int>();

    add_edge(from, to, weight);
    if (both_sides) {
      add_edge(to, from, weight);
    }
  }

  const auto agents = loadv<vi>(agent_count);
  const auto shelters = loadv<vi>(shelter_count);

  // Calculate pairwise distances
  std::array<std::array<int, 100>, 100> distances;
  std::vector<int> distance_map(vertex_count);
  for(int i = 0; i < agent_count; i++) {
    boost::dijkstra_shortest_paths(DG, agents[i], boost::distance_map(boost::make_iterator_property_map(distance_map.begin(), boost::get(boost::vertex_index, DG))));
    for(int j = 0; j < shelter_count; j++) {
      distances[i][j] = distance_map[shelters[j]];
    } 
  }

  // Run binary search on achievable time
  int low = 0; 
  int high = 50002000;
  while (low < high) {
    const int mid = (low == 0 && high == 50002000) ? 10 : (low+high)/2; // allows to solve small problems quickly
    const int total_vertex_count = agent_count + shelter_count * capacity;
    const int shelter_offset = agent_count;

    matching_graph MG(total_vertex_count);

    for(int i = 0; i < agent_count; i++) {
      for(int j = 0; j < shelter_count; j++) {
        const int path_len = distances[i][j];
        if (path_len == std::numeric_limits<int>::max()) {
          continue;
        }

        for(int k = 1; k <= capacity; k++) {
          if (path_len + k * enter_time <= mid) {
            boost::add_edge(i, shelter_offset + (k-1) * shelter_count + j, MG);
          }
        }
      }
    }

    std::vector<matching_graph_vertex_desc> matchings(agent_count + capacity * shelter_count);
    boost::edmonds_maximum_cardinality_matching(MG, &matchings[0]);
    const bool possible = static_cast<int>(boost::matching_size(MG, &matchings[0])) == agent_count;

    if (possible) {
      high = mid;
    } else {
      low = mid+1;
    }
  }

  std::cout << low << std::endl;
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
