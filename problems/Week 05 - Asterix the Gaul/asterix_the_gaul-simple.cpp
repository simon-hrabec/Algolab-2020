#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

template<typename T1, typename T2>
using vp = std::vector<std::pair<T1,T2>>;
using vi = std::vector<int>;
using vpii = vp<int, int>;

template <typename T>
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

template<typename T>
T loadvp(const int count) {
  T v(count);
  for(int i = 0; i < count; i++) {
    std::cin >> v[i].first;
    std::cin >> v[i].second;
  }
  return v;
}

vpii moves; // distance, time
vi potions;
std::array<int64_t, 31> best_without_potion;

void dfs(const int move, const int moves_used, const int64_t distance, const int64_t time) {
  if (move >= (int)moves.size() || time <= moves[move].second) {
    best_without_potion[moves_used] = std::min(best_without_potion[moves_used], distance);
    return;
  }

  dfs(move+1, moves_used, distance, time);
  dfs(move+1, moves_used+1, distance - moves[move].first, time - moves[move].second);
}

void solve() {
  const int nr_moves = load<int>();
  const int nr_potions = load<int>();
  const int64_t distance = load<int64_t>();
  const int64_t time = load<int64_t>();

  moves = loadvp<vpii>(nr_moves);
  potions = loadv<vi>(nr_potions);

  std::sort(std::begin(moves), std::end(moves), [](const auto &a, const auto &b){
    return a.second < b.second;
  });

  if (moves[0].second >= time) {
    std::cout << "Panoramix captured" << std::endl;
    return;
  }

  best_without_potion.fill(std::numeric_limits<int64_t>::max());
  dfs(0, 0, distance, time);

  int64_t best = std::numeric_limits<int64_t>::max();
  for(int i = 1; i <= nr_moves; i++) {
    if (best_without_potion[i] <= 0) {
      std::cout << "0" << std::endl;
      return;
    }
    if (best_without_potion[i] != std::numeric_limits<int64_t>::max()) {
      const int64_t needed_gain = (best_without_potion[i]-1)/(i)+1;
      if (const auto it = std::lower_bound(std::begin(potions), std::end(potions), needed_gain); it != std::end(potions)) {
        best = std::min(best, it-std::begin(potions)+1);
      }
    }
  }

  if(best == std::numeric_limits<int64_t>::max()) {
    std::cout << "Panoramix captured" << std::endl;
  } else {
    std::cout << best << std::endl;
  }
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
