#include <iostream>
#include <vector>
#include <limits>
#include <array>

struct edge {
  int from;
  int weight;
};

template<typename T>
T load(){
  T val;
  std::cin >> val;
  return val;
}

void solve(){
  // Load data
  const auto vertex_count = load<int>();
  const auto edge_count = load<int>();
  const auto score = load<int64_t>();
  const auto moves = load<int>();

  std::vector<int64_t> dp1(vertex_count, std::numeric_limits<int64_t>::min());
  std::vector<int64_t> dp2(vertex_count, std::numeric_limits<int64_t>::min());
  std::array<std::vector<edge>, 1000> edges;
  std::array<int, 1000> outgoing = {};

  for(int i = 0; i < edge_count; i++) {
    const auto from = load<int>();
    const auto to = load<int>();
    const auto weight = load<int>();

    edges[to].push_back({from, weight});
    outgoing[from]++;
  }

  // Add special edges back to origin for sinks (vertices without outgoing edge)
  for(int i = 0; i < vertex_count; i++) {
    if (!outgoing[i]) {
      for(const auto &e : edges[i]) {
        edges[0].push_back({e.from, e.weight});
      }
    }
  }

  // Set base case
  dp1[0] = 0;

  // Fill DP table (row by row)
  for(int i = 0; i < moves; i++) {
    for(int j = 0; j < vertex_count; j++) {
      if (edges[j].size()) {
        const auto &[first_from, first_weight] = edges[j][0];
        int64_t best = dp1[first_from] + first_weight;
        for(int k = 1; k < (int)edges[j].size(); k++) {
          const auto &[from, weight] = edges[j][k];
          best = std::max(best, dp1[from] + weight);  
        }
        dp2[j] = best;
      }

      if(dp2[j] >= score) {
        std::cout << i+1 << std::endl;
        return;
      }
    }

    std::swap(dp1, dp2);
  }

  std::cout << "Impossible" << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
  return 0;
}
