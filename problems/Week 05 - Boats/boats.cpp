#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using vpii = std::vector<std::pair<int,int>>;

template <typename T>
T load() {
  T val;
  std::cin >> val;
  return val;
}

template<typename T>
T loadvp(const int count) {
  T v(count);
  for(int i = 0; i < count; i++) {
    std::cin >> v[i].first;
    std::cin >> v[i].second;
  }
  return v;
}

void solve() {
  const int boat_count = load<int>();
  auto boats = loadvp<vpii>(boat_count);

  std::sort(std::begin(boats), std::end(boats), [](const auto &a, const auto &b){
    return a.second < b.second;
  });

  int used_boats = 0;

  int definitelly_used = std::numeric_limits<int>::min();
  int last_used = std::numeric_limits<int>::min();

  for(const auto& [length, position] : boats) {
    if (position >= last_used) {
      // add the boat and put it as much left as possible
      used_boats++;
      definitelly_used = last_used;
      last_used = std::max(last_used+length, position);
    } else {
      // consider replacing the last boat
      const int new_used = std::max(definitelly_used+length, position);
      last_used = std::min(last_used, new_used);
    }
  }

  std::cout << used_boats << std::endl;;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
}
