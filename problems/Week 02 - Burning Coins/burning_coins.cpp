#include <iostream>
#include <array>

std::array<std::array<int, 2500>,2500> dp;
std::array<int, 2500> coins;

void solve(){
  // Load data
  int N; std::cin >> N;
  for(int i = 0; i < N; i++){
    std::cin >> coins[i];
  }

  // Set the base cases
  if(N & 1) {
    for(int i = 0; i < N; i++) {
      dp[i][i] = coins[i];
    }
  } else{
    for(int i = 0; i < N; i++) {
      dp[i][i] = 0;
    }
  }

  // Fill the table
  for(int i = N-1; i >= 0; i--) {
    for(int j = i+1; j < N; j++) {
      if ((N+j-i+1) & 1) {
        dp[i][j] = std::min(dp[i+1][j], dp[i][j-1]);
      } else {
        dp[i][j] = std::max(dp[i+1][j] + coins[i], dp[i][j-1] + coins[j]);
      }
    }
  }

  std::cout << dp[0][N-1] << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
  return 0;
}
