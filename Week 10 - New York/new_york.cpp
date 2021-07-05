#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <algorithm>

template <typename T>
T load(){
  T val;
  std::cin >> val;
  return val;
}

std::array<std::vector<int>, 100'000> neigbors;
std::array<int, 100'000> temperatures;
int trip_len;
int max_temperature_difference;

std::array<std::pair<int, bool>, 100'000> dfs_stack; // temperature, valid start node
std::map<int, int> count_map;
std::array<int, 100'000> viable_points;
int viable_point_count;
int depth;

int remove(const int elem) {
  const auto it = count_map.find(elem);
  if (--(it->second) == 0) {
    count_map.erase(it);
  }
  return elem;
}

int temperature_difference() {
  const int low = std::begin(count_map)->first;
  const int high = std::rbegin(count_map)->first;
  return high-low;
}

int sums() {
  int result = 0;
  for(const auto [key, value] : count_map) {
    result += value;
  }
  return result;
}

void dfs(const int node) {
  depth++;

  auto &current = dfs_stack[depth-1];
  auto &start = dfs_stack[depth-trip_len];
  auto &not_included = dfs_stack[depth-trip_len-1];

  // Update temperature count map to match current "sliding" window
  current = {temperatures[node], false};
  count_map[current.first]++;
  if (depth > trip_len) {
    remove(not_included.first);
  }

  // Check if path ending here is valid
  if (depth >= trip_len && temperature_difference() <= max_temperature_difference) {
    start.second = true;
  }

  // Go deeper
  for(const int child : neigbors[node]) {
    dfs(child);
  }

  // Reverse temperature count map to original state
  if (depth > trip_len) {
    count_map[not_included.first]++;
  }
  remove(current.first);

  // Check if this is a valid path start
  if (current.second) {
    viable_points[viable_point_count++] = node;
  }
  depth--;
}

void solve(){
  const int point_count = load<int>();
  trip_len = load<int>();
  max_temperature_difference = load<int>();

  count_map.clear();
  for(int i = 0; i < point_count; i++) {
    neigbors[i].clear();
  }

  for(int i = 0; i < point_count; i++) {
    std::cin >> temperatures[i];
  }

  for(int i = 0; i < point_count-1; i++) {
    const int from = load<int>();
    const int to = load<int>();
    neigbors[from].push_back(to);
  }

  viable_point_count = 0;
  depth = 0;

  dfs(0);

  if (viable_point_count) {
    std::sort(std::begin(viable_points), std::begin(viable_points)+viable_point_count);
    for(auto it = std::begin(viable_points); it != std::begin(viable_points)+viable_point_count; ++it) {
      std::cout << *it << ' ';
    }
    std::cout << std::endl;
  } else {
    std::cout << "Abort mission" << std::endl;
  }
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int T;
  std::cin >> T;
  while(T--) {
    solve();
  }
  return 0;
}
