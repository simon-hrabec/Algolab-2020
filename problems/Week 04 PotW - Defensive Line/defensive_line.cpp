#include <iostream>
#include <vector>

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

using vi = std::vector<int>;

int dp[101][100'001];

void solve(){
  const int defenders_count = load<int>();
  const int attackers_count = load<int>();
  const int strength = load<int>();

  const auto defenders = loadv<vi>(defenders_count);
  std::vector<int> sequence_length(defenders_count);

  int sum = 0;
  int back_position = 0;

  for(int i = 0; i < defenders_count; i++) {
    sum += defenders[i];
    while(sum > strength) {
      sum -= defenders[back_position++];
    }
    
    if (sum == strength) {
      sequence_length[i] = i-back_position+1;
    }
  }

  for(int i = 0; i <= defenders_count; i++) {
    dp[0][i] = 0;
  }
  for(int i = 1; i <= attackers_count; i++) {
    dp[i][0] = -1;
  }

  for(int i = 1; i <= attackers_count; i++) {
    for(int j = 1; j <= defenders_count; j++) {
      const int len = sequence_length[j-1];
      if (len && dp[i-1][j-len] != -1) {
        dp[i][j] = std::max(dp[i-1][j-len] + len, dp[i][j-1]);
      } else {
        dp[i][j] = dp[i][j-1];  
      }
    }
  }

  const int result = dp[attackers_count][defenders_count];
  if (result == -1) {
    std::cout << "fail" << std::endl;
  } else {
    std::cout << result << std::endl;
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
