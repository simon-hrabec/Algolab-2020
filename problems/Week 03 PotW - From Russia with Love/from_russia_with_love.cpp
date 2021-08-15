
#include <iostream>
#include <vector>
#include <array>

void solve(){
  // Load data
  int coin_count, people_count, position;
  std::cin >> coin_count >> people_count >> position;

  std::array<std::array<int,1000>,1000> arr;
  std::array<bool,1000> modulos;
  std::vector<int> coins(coin_count);

  for(int i = 0; i < coin_count; i++){
    std::cin >> coins[i];
  }

  const int last_move = (coin_count-position+people_count-1)%people_count;

  modulos.fill(false);
  for(int i = last_move; i < coin_count; i += people_count) {
    modulos[i] = true;
  }

  // Set base case  
  if (last_move) {
    for(int i = 0; i < coin_count; i++) {
      arr[0][i] = 0;
    }
  } else {
    for(int i = 0; i < coin_count; i++) {
      arr[0][i] = coins[i];
    }
  }

  // Fill the table
  for(int i = 1; i < coin_count; i++) {
    const bool is_target_player = modulos[i];

    if (is_target_player) {
      for (int j = 0; j < coin_count-i; j++) {
        arr[i][j] = std::max(coins[j]+arr[i-1][j+1], coins[j+i]+arr[i-1][j]);
      }
    } else {
      for (int j = 0; j < coin_count-i; j++) {
        arr[i][j] = std::min(arr[i-1][j+1], arr[i-1][j]);
      } 
    }
  }

  std::cout << arr[coin_count-1][0] << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
}
