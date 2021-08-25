#include <iostream>
#include <array>

std::array<std::array<int,201>, 201> arr = {};

int sum(const int x1, const int x2, const int y1, const int y2) {
  return arr[x2][y2] - arr[x1-1][y2] - arr[x2][y1-1] + arr[x1-1][y1-1];
}

void solve(){
  int N; std::cin >> N;
  for(int i = 1; i <= N; i++) {
    for(int j = 1; j <= N; j++){
      int num; std::cin >> num;
      arr[i][j] = arr[i-1][j] + arr[i][j-1] - arr[i-1][j-1] + num;
    }
  }

  uint64_t res= 0;

  for(int i = 1; i <= N; i++) {
    for(int i2 = i;  i2 <= N; i2++) {
      int odd = 0;
      int even = 0;
      for(int x = 1; x <= N; x++) {
        if (sum(i,i2,1,x) & 1) {
          odd++;
        }  else {
          even++;
        }
      }

      res += (even*(even-1))/2 + even + (odd*(odd-1))/2;
    }
  }

  std::cout << res << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
  return 0;
}
