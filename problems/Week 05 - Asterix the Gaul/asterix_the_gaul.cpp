#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <tuple>

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

using storage_array = std::array<std::vector<std::pair<int64_t, int64_t>>, 16>;

vpii moves; // distance, time
vi potions;
std::array<int64_t, 31> best_without_potion;
storage_array first_half, second_half;

void dfs_fill(const int move, const int moves_used, const int64_t distance, const int64_t time, const int max_move, storage_array& arr) {
  if (time <= 0) {
    return;
  }

  if(move >= max_move) {
    arr[moves_used].emplace_back(time, distance);
  } else {
    dfs_fill(move+1, moves_used, distance, time, max_move, arr);
    dfs_fill(move+1, moves_used+1, distance-moves[move].first, time-moves[move].second, max_move, arr);
  }
}

void sort_and_remove_suboptimal(storage_array &arr) {
  for(auto &row : arr) {
    if(row.size() <= 1) {
      continue;
    }

    std::sort(std::begin(row), std::end(row), [](const auto &a, const auto &b){
      if (a.first == b.first) {
        return a.second > b.second;
      }
      return a.first < b.first;
    });

    int shift = 0;
    int64_t min_distance = row.back().second;
    for(int i = row.size()-2; i >= 0; i--) {
      if (row[i].second >= min_distance) {
        shift++;
      } else {
        row[i+shift] = row[i];
        min_distance = row[i].second;
      }
    }

    if (shift > 0) {
      for(int i = 0; i < (int)row.size()-shift; i++) {
        row[i] = row[i+shift];
      }
      row.resize(row.size()-shift);
    }
  }
}

void clear(){
  for(auto &v : first_half) v.clear();
  for(auto &v : second_half) v.clear();
}

void solve() {
  clear();
  const int nr_moves = load<int>();
  const int nr_potions = load<int>();
  const int64_t distance = load<int64_t>();
  const int64_t time = load<int64_t>();

  moves = loadvp<vpii>(nr_moves);
  potions = loadv<vi>(nr_potions);

  best_without_potion.fill(std::numeric_limits<int64_t>::max());

  dfs_fill(0, 0, distance, time, (nr_moves+1)/2, first_half);
  dfs_fill((nr_moves+1)/2, 0, distance, time, nr_moves, second_half);

  sort_and_remove_suboptimal(first_half);
  sort_and_remove_suboptimal(second_half);

  for(int i = 0; i <= (nr_moves+1)/2; i++) {
    for(const auto &elem : first_half[i]) {
      for(int j = 0; j <= nr_moves/2; j++) {
        const auto &row = second_half[j];
        const auto it = std::upper_bound(std::begin(row), std::end(row), time-elem.first, [](const auto &value, const auto &elem){
          return value < elem.first;
        });
        if (it == std::end(row)) {
          break;
        }
        const int moves_used = i+j;
        best_without_potion[moves_used] = std::min(best_without_potion[moves_used], elem.second+it->second-distance);
      }
    }
  }

  int64_t best = std::numeric_limits<int64_t>::max();
  for(int i = 1; i <= nr_moves; i++) {
    if (best_without_potion[i] <= 0) {
      std::cout << "0" << std::endl;
      return;
    }
    if (best_without_potion[i] != std::numeric_limits<int64_t>::max()) {
      const int64_t needed_gain = (best_without_potion[i]-1)/(i)+1;
      if (const auto it = std::lower_bound(std::begin(potions), std::end(potions), needed_gain); it != std::end(potions)){
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
