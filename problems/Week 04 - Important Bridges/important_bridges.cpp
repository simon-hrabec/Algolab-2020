#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

struct edge_component_t
{
  enum
  { num = 555 };
  using kind = boost::edge_property_tag;
} edge_component;

using graph = boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::undirectedS,
  boost::no_property,
  boost::property<edge_component_t,std::size_t>
>;

using edge_component_map = boost::property_map<graph, edge_component_t>::type;
using edge_iter = boost::graph_traits<graph>::edge_iterator;


void solve(){
  int vertex_count, edge_count; std::cin >> vertex_count >> edge_count;
  
  graph g(vertex_count);
  edge_component_map components = boost::get(edge_component, g);
  
  // Load input
  for(int i = 0; i < edge_count; i++) {
    int from, to; std::cin >> from >> to;
    boost::add_edge(from, to, g).first;
  }
  
  // Use biconnected components, find important edges
  biconnected_components(g, components);
  
  // first iterate over edges and count how many edges component has
  std::unordered_map<int,int> component_sizes;
  edge_iter iter, iter_end;
  for(boost::tie(iter, iter_end) = edges(g); iter != iter_end; ++iter) {
    component_sizes[components[*iter]]++;
  }
  
  // then iterate over the edges save the ones that are the sole edge of a compontn
  std::vector<std::pair<int,int>> results;
  for(boost::tie(iter, iter_end) = edges(g); iter != iter_end; ++iter) {
    const auto edge = *iter;
    if (component_sizes[components[edge]] == 1) {
      const int v1 = boost::source(edge, g);
      const int v2 = boost::target(edge, g);
      results.emplace_back(std::min(v1, v2), std::max(v1, v2));
    }
  }
  
  // print results
  std::sort(std::begin(results), std::end(results));
  std::cout << results.size() << std::endl;
  for(const auto &e : results) {
    std::cout << e.first << " " << e.second << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
}
