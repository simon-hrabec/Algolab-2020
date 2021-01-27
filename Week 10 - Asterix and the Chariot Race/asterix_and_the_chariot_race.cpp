#include <iostream>
#include <array>
#include <limits>
#include <vector>
#include <tuple>

template <typename T>
T load(){
  T val;
  std::cin >> val;
  return val;
}

std::array<std::vector<int>, 100000> neigbors;
std::array<int, 100000> costs;

// Node is selected - Use the node and return sum of  not covered
// Node is covered - sum of covered nodes + one selected
// Node is not covered - sum of covered
std::tuple<int, int, int> dfs(const int node) {
  const int current_cost = costs[node];
  
  int selected_sum = 0;
  int covered_sum = 0;
  int not_covered_sum = 0;

  int min_selected_diff = std::numeric_limits<int>::max();
  for(int i = 0; i < (int)neigbors[node].size(); i++) {
    const auto[selected, covered, not_covered] = dfs(neigbors[node][i]);

    selected_sum += selected;
    covered_sum += covered;
    not_covered_sum += not_covered;
    min_selected_diff = std::min(min_selected_diff, selected - covered);
  }
  
  const int selected_result = current_cost + not_covered_sum;
  const int covered_result = std::min(selected_result, covered_sum + min_selected_diff);
  const int not_covered_result = std::min(selected_result, covered_sum);
  
  return {selected_result, covered_result, not_covered_result};
}

void solve(){
  const int city_count = load<int>();
  for(int i = 0; i < city_count; i++) {
    neigbors[i].clear();
  }
  
  for(int i = 0; i < city_count-1; i++) {
    const int from = load<int>();
    const int to = load<int>();
    neigbors[from].push_back(to);
  }
  
  for(int i = 0; i < city_count; i++) {
    std::cin >> costs[i];
  }
  
  std::cout << std::get<1>(dfs(0)) << std::endl;
}

int main(){
  int T;
  std::cin >> T;
  while(T--) {
    solve();
  }
}
