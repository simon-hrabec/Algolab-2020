#include <iostream>
#include <vector>

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

void solve(){
  const int card_count = load<int>();
  const int target = load<int>();
  const auto cards = loadv<vi>(card_count);

  int from_best = 0, to_best = 0, diff_best = std::abs(cards[0]-target);

  int from = 0, to = 0, sum = cards[0];

  while(true) {
    if (sum <= target || from == to) {
      if (++to == card_count) {
        break;
      }
      sum += cards[to];
    } else {
      sum -= cards[from];
      from++;
    }

    const int diff = std::abs(sum-target);

    if (diff < diff_best) {
      diff_best = diff;
      from_best = from;
      to_best = to;
    }
  }

  std::cout << from_best << " " << to_best << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
  return 0;
}
