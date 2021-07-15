#include <iostream>
#include <vector>
#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using graph = boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::undirectedS,
  boost::no_property,
  boost::property<boost::edge_weight_t, int>
>;
using weight_map = boost::property_map<graph, boost::edge_weight_t>::type;
using edge_desc = boost::graph_traits<graph>::edge_descriptor;

int get_mst_price(const graph &g){
  std::vector<edge_desc> mst;
  boost::kruskal_minimum_spanning_tree(g, std::back_inserter(mst));
  const auto &weights = boost::get(boost::edge_weight, g);
  
  int mst_price = 0;
  for(const auto &edge : mst) {
    mst_price += weights[edge];
  }
  
  return mst_price;
}

int get_max_distance(const graph &g){
    const int vertice_count = boost::num_vertices(g);
    std::vector<int> distance_map(vertice_count);
    
    boost::dijkstra_shortest_paths(g, 0, 
      boost::distance_map(boost::make_iterator_property_map(std::begin(distance_map), boost::get(boost::vertex_index, g)
    )));
    
    return *std::max_element(std::begin(distance_map), std::end(distance_map));
}

void solve(){
  int vertex_count, edge_count; std::cin >> vertex_count >> edge_count;
  
  graph g(vertex_count);
  weight_map weights = boost::get(boost::edge_weight, g);
  
  for(int i = 0; i < edge_count; i++) {
    int from, to, weight; std::cin >> from >> to >> weight;
    const edge_desc edge = boost::add_edge(from, to, g).first;
    weights[edge] = weight;
  }
  
  std::cout << get_mst_price(g) << " " << get_max_distance(g) << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
}
