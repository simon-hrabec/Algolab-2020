#include <iostream>
#include <array>
#include <vector>

template <typename T>
T load(){
  T val;
  std::cin >> val;
  return val;
}

void solve(){
  // Load data
  const int position_count = load<int>();
  const int transition_count = load<int>();
  const int r_start = load<int>();
  const int b_start = load<int>();

  std::vector<std::vector<int>> transition_array(position_count+1);

  for(int i = 0; i < transition_count; i++) {
    const int from = load<int>();
    const int to = load<int>();
    transition_array[from].push_back(to);
  }

  // Set base case
  std::vector<std::array<int, 2>> hop_count(position_count+1);
  hop_count[position_count] = {0, 0};

  // Fill the DP table
  const int rb_min = std::min(r_start, b_start);
  for(int i = position_count-1; i >= rb_min; i--) {
    int min = hop_count[transition_array[i][0]][1]; 
    int max = hop_count[transition_array[i][0]][0];

    for(int j = 1; j < (int)transition_array[i].size(); j++) {
      const auto &minmax = hop_count[transition_array[i][j]];

      min = std::min(min, minmax[1]);
      max = std::max(max, minmax[0]);
    }

    hop_count[i][0] = min + 1;
    hop_count[i][1] = max + 1;
  }

  // Interpret results
  const int red = hop_count[r_start][0];
  const int black = hop_count[b_start][0];

  if (red <= 1 || (red)/2 < (black+1)/2) {
    std::cout << 0 << std::endl;
  } else {
    std::cout << 1 << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
  return 0;
}
