#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <tuple>

template<typename T>
T load() {
  T val;
  std::cin >> val;
  return val;
}

int ball_count;
std::array<bool, 65535> defused;

int check(const int index) {
  if (index >= ball_count || defused[index]) {
    return 0;
  }
  
  defused[index] = true;
  return check(index*2+1)+check(index*2+2)+1;
};

void solve() {
  ball_count = load<int>();
  std::vector<std::pair<int,int>> balls(ball_count); // detonation time, index
  for(int i = 0; i < ball_count; i++) {
    std::cin >> balls[i].first;
    balls[i].second = i;
  }

  std::sort(std::begin(balls), std::end(balls));
  std::fill(std::begin(defused), std::begin(defused)+ball_count, false);

  int time = 0;
  bool possible = true;

  for(int i = 0; i < ball_count; i++) {
    const int turn = check(balls[i].second);
    time += turn;
    if (time > balls[i].first) {
      possible = false;
      break;
    }
  }

  std::cout << (possible ? "yes" : "no") << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  int N; std::cin >> N;
  while(N--) {
    solve();
  }
  return 0;
}
