#include <iostream>

void solve(){
  int N; std::cin >> N;

  int sum = 0;
  int even = 0;
  int odd = 0;

  for(int i = 0; i < N; i++) {
    int num; std::cin >> num;
    sum += num;
    odd += (sum)&1;
    even += (~sum)&1;
  }

  const int result = (even*(even-1))/2 + even + (odd*(odd-1))/2;

  std::cout << result << std::endl; 
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
  return 0;
}
