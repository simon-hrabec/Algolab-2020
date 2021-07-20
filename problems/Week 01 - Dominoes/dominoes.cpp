#include <iostream>

void read_n(int num) {
  while(num--) {
    int temp; std::cin >> temp;
  }
}

void solve(){
  int N; std::cin >> N;
  int reach = 0;

  for(int i = 0; i < N; i++) {
    if (i > reach) {
      read_n(N-i);
      break;
    }
    int current; std::cin >> current;
    reach = std::max(reach, i + current - 1);
  }

  std::cout << std::min(reach+1, N) << std::endl; 
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
}
