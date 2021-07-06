#include <iostream>
#include <vector>
#include <unordered_map>

using vi = std::vector<int>;
template<typename T>
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

void solve() {
  // Load data
  const int island_count = load<int>();
  const int men_count = load<int>();
  const int way_count = load<int>();
  
  const auto islands = loadv<vi>(island_count);
  std::vector<std::vector<int>> ways(way_count);
  for(int i = 0; i < way_count; i++) {
    const int len = load<int>();
    ways[i] = loadv<vi>(len);
  }
  
  // 2 pointers scan for each waterway
  int max_islands = 0;
  for(int i = 0; i < way_count; i++) {
    const int len = ways[i].size();
    int from = 0; // inclusive
    int to = 0; // exclusive
    int sum = 0;
    while(true) {
      const int current_count = to-from;
      if (sum == men_count) {
        max_islands = std::max(max_islands, current_count);
        sum -= islands[ways[i][from++]];
      } else if (sum < men_count) {
        if (to == len) {
          break;
        }
        sum += islands[ways[i][to++]];
      } else if (sum > men_count) {
        sum -= islands[ways[i][from++]];
      }
    }
  }
  
  // Use lookup for V shaped solution (using 2 waterways and the center island 0)
  std::unordered_map<int ,int> most_islands_for_men;
  std::vector<int> sums;
  sums.reserve(island_count);
  for(int i = 0; i < way_count; i++) {
    // Include only the middle island
    sums.resize(1);
    
    // Precompute sums in given waterway
    const int len = ways[i].size();
    for(int j = 1, sum = 0; j < len; j++) {
      sum += islands[ways[i][j]];
      if (sum >= men_count) {
        break;
      }
      sums.push_back(sum);
    }
    
    // Lookup for results in other waterways
    for(int j = 1; j < (int)sums.size(); j++) {
      auto iter = most_islands_for_men.find(men_count - sums[j] - islands[0]);
      if (iter != std::end(most_islands_for_men)) {
        max_islands = std::max(max_islands, iter->second + j + 1);
      }
    }
    
    // Include results of this waterway in the lookup hashmap
    for(int j = 1; j < (int)sums.size(); j++) {
      auto iter = most_islands_for_men.find(sums[j]);
      if (iter != std::end(most_islands_for_men) && iter->second < j) {
        if (iter->second < j) {
          iter->second = j;
        }
      } else {
        most_islands_for_men.emplace_hint(iter, sums[j], j);
      } 
    }
  }
  
  std::cout << max_islands << std::endl;
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
