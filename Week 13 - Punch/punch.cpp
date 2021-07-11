#include <iostream>
#include <limits>
#include <array>
#include <tuple>

template<typename T>
T load(){
  T val;
  std::cin >> val;
  return val;
}

std::array<std::pair<int, int>, 100> drinks; // price, litres
std::array<std::array<std::tuple<int,int,bool>, 10001>, 101> dp; // price, count, used

void solve() {
  const int nr_drinks = load<int>();
  const int nr_people = load<int>();

  for(int i = 0; i < nr_drinks; i++) {
    std::cin >> drinks[i].first >> drinks[i].second;
  }

  for(int i = 0; i <= nr_drinks; i++) {
    dp[i][0] = {0, 0, false};
  }
  for(int i = 1; i <= nr_people; i++) {
    dp[0][i] = {std::numeric_limits<int>::max(), 0, false};
  }

  for(int i = 1; i <= nr_drinks; i++) {
    for(int j = 1; j <= nr_people; j++) {
      const int price = drinks[i-1].first;
      const int litres = drinks[i-1].second;
      const int with_idx = std::max(0, j-litres);

      const int with_price = std::get<0>(dp[i][with_idx]) + price;
      const int with_count = std::get<1>(dp[i][with_idx]) + !std::get<2>(dp[i][with_idx]);
      const int without_price = std::get<0>(dp[i-1][j]);
      const int without_count = std::get<1>(dp[i-1][j]);


      if (std::make_tuple(with_price, -with_count) < std::make_tuple(without_price, -without_count)) {
        dp[i][j] = {with_price, with_count, true};
      } else {
        dp[i][j] = {without_price, without_count, false};
      }
    }
  }

  std::cout << std::get<0>(dp[nr_drinks][nr_people]) << " " << std::get<1>(dp[nr_drinks][nr_people]) << std::endl;
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
