#include <iostream>
#include <array>
#include <iterator>
#include <algorithm>
#include <numeric>

void solve() {
  int K; std::cin >> K;
  int sum = 0;

  while(K--) {
    int num; std::cin >> num;
    sum += num;
  }

  std::cout << sum << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
}
