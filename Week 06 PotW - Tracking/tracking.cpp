#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
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
using vertex_desc = boost::graph_traits<graph>::vertex_descriptor;

void solve(){
  int vertex_count, edge_count, rivers, start, target; std::cin >> vertex_count >> edge_count >> rivers >> start >> target;
  const int levels = rivers+1;
  const int total_vertex_count = levels * vertex_count;
  const int real_target = target + rivers * vertex_count;

  graph g(total_vertex_count);
  weight_map weights = boost::get(boost::edge_weight, g);

  for(int i = 0; i < edge_count; i++) {
    int from, to, weight, is_river; std::cin >> from >> to >> weight >> is_river;
    for(int j = 0; j < levels; j++) {
      const int offset = j * vertex_count;
      const int from_2 = from + offset;
      const int to_2 = to + offset;
      const edge_desc edge = boost::add_edge(from_2, to_2, g).first;
      weights[edge] = weight;
    }

    if (is_river) {
      for(int j = 0; j < levels-1; j++) {
        const int offset1 = j * vertex_count;
        const int offset2 = (j+1) * vertex_count;
        const edge_desc edge1 = boost::add_edge(from + offset1, to + offset2, g).first;
        const edge_desc edge2 = boost::add_edge(from + offset2, to + offset1, g).first;
        weights[edge1] = weight;
        weights[edge2] = weight;
      }
    }
  }

  std::vector<int> distance_map(total_vertex_count);
  boost::dijkstra_shortest_paths(g, start,
    boost::distance_map(boost::make_iterator_property_map(std::begin(distance_map), boost::get(boost::vertex_index, g)
  )));

  std::cout << distance_map[real_target] << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T;
  std::cin >> T;
  while(T--){
    solve();
  }
  return 0;
}
