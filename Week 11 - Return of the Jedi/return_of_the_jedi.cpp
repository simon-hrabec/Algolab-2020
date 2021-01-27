#include<iostream>
#include<array>
#include<vector>
#include<stack>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

using Graph = boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::undirectedS,
  boost::no_property,
  boost::property<boost::edge_weight_t, int>
>;
using edge_desc = boost::graph_traits<Graph>::edge_descriptor;

std::array<std::array<int, 1000>, 1000> costs;
std::array<std::array<int, 1000>, 1000> longest_edge;
std::array<std::array<bool, 1000>, 1000> used;

template <typename T>
T load(){
  T val;
  std::cin >> val;
  return val;
}

void solve() {
  const int nr_planets = load<int>();
  const int start = load<int>()-1;
  
  Graph G(nr_planets);
  auto weights = boost::get(boost::edge_weight, G);
  const auto add_edge = [&G, &weights](const int from, const int to, const int weight){
    auto e = boost::add_edge(from, to, G).first;
    weights[e] = weight;
  };
  
  for(int i = 0; i < nr_planets; i++) {
    for(int j = i+1; j < nr_planets; j++) {
      used[i][j] = used[j][i] = false;
      const int cost = load<int>();
      costs[i][j] = costs[j][i] = cost;
      add_edge(i, j, cost);
    }
  }
  
  std::vector<edge_desc> mst;
  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
  std::vector<std::vector<int>> neighbors(nr_planets);
  
  int optimal_cost = 0;
  for(const auto edge : mst) {
    const int from = boost::source(edge, G);
    const int to = boost::target(edge, G);
    
    neighbors[from].push_back(to);
    neighbors[to].push_back(from);
    
    used[from][to] = used[to][from] = true;
    
    optimal_cost += weights[edge];
  }
  
  // Find longest edge on the MST between each edge
  for(int i = 0; i < nr_planets; i++) {
    std::vector<uint8_t> visited(nr_planets);
    std::stack<std::tuple<int, int, int>> stack; // vertex idx, neigbor iter, current longest_edge
    stack.emplace(i, -1, 0);
    
    while(!stack.empty()) {
      auto&[vertex_idx, neigbor_iter, current_max] = stack.top();
      neigbor_iter++;
      if (neigbor_iter == (int)neighbors[vertex_idx].size()) {
        stack.pop();
        continue;
      }
      
      const int next_neigbor = neighbors[vertex_idx][neigbor_iter];
      if (visited[next_neigbor]) {
        continue;
      }
      
      const int next_max = std::max(current_max, costs[vertex_idx][next_neigbor]);
      longest_edge[i][next_neigbor] = longest_edge[next_neigbor][i] = next_max;
      visited[next_neigbor] = true;
      stack.emplace(next_neigbor, -1, next_max);
    }
  }
  
  int min_diff = std::numeric_limits<int>::max();
  
  for(int i = 0; i < nr_planets; i++) {
    for(int j = i+1; j < nr_planets; j++) {
      if (!used[i][j]) {
        min_diff = std::min(min_diff, costs[i][j] - longest_edge[i][j]);
      }
    }
  }
  
  std::cout << optimal_cost+min_diff << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
  return 0;
}
