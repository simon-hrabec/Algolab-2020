#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

using graph = boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::undirectedS,
  boost::no_property,
  boost::property<boost::edge_weight_t, int>
>;
using weight_map = boost::property_map<graph, boost::edge_weight_t>::type;
using edge_desc = boost::graph_traits<graph>::edge_descriptor;
using vertex_desc = boost::graph_traits<graph>::vertex_descriptor;

uint64_t pack(uint32_t first, uint32_t second) {
  if (first < second) {
    std::swap(first, second);
  }
  return (uint64_t(first) << 32) | uint64_t(second);
}

std::pair<uint32_t, uint32_t> unpack(const uint64_t both) {
  const uint64_t mask = (uint64_t(1)<< 32) - 1;
  return {both & (mask << 32), both & mask};
}

void solve(){
  int vertex_count, edge_count, species_count, source, target; std::cin >> vertex_count >> edge_count >> species_count >> source >> target;
  
  graph g(vertex_count);
  weight_map weights = boost::get(boost::edge_weight, g);
  
  std::vector<std::vector<int>> edge_weight_for_spiecies(edge_count, std::vector<int>(species_count));
  std::vector<edge_desc> edge_ids;
  std::vector<int> species_starts(species_count);
  std::vector<int> best_weights(edge_count, std::numeric_limits<int>::max());
  std::unordered_map<uint64_t, uint32_t> edge_map;
  
  // Load input
  for(int i = 0; i < edge_count; i++) {
    int from, to; std::cin >> from >> to;
    const edge_desc edge = boost::add_edge(from, to, g).first;
    edge_ids.push_back(edge);
    edge_map[pack(from, to)] = i;
    
    for(int j = 0; j < species_count; j++) {
      std::cin >> edge_weight_for_spiecies[i][j];
    }
  }
  
  for(int i = 0; i < species_count; i++) {
    std::cin >> species_starts[i];
  }
  
  // Calculate networks
  for(int i = 0; i < species_count; i++) {
    for(int j = 0; j < edge_count; j++) {
      weights[edge_ids[j]] = edge_weight_for_spiecies[j][i];
    }
    
    std::vector<edge_desc> mst;
    boost::kruskal_minimum_spanning_tree(g, std::back_inserter(mst));
    
    for(const auto edge : mst) {
      const int edge_id = edge_map[pack(boost::source(edge, g), boost::target(edge, g))];
      best_weights[edge_id] = std::min(best_weights[edge_id], edge_weight_for_spiecies[edge_id][i]);
    }
  }
  
  // Update weight for best case/species
  for(int i = 0; i < edge_count; i++) {
    if (best_weights[i] == std::numeric_limits<int>::max()) {
      remove_edge(edge_ids[i], g);
    } else {
      weights[edge_ids[i]] = best_weights[i];
    }
  }
  
  // Calculate result
  std::vector<vertex_desc> dist_map(vertex_count);
  boost::dijkstra_shortest_paths(g, source,
    boost::distance_map(boost::make_iterator_property_map(std::begin(dist_map), boost::get(boost::vertex_index, g)))
  );
  
  std::cout << dist_map[target] << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
}
