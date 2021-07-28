#include <iostream>
#include <array>
#include <vector>
#include <limits>
#include <algorithm>

void solve(){
  // Load data
  int words; std::cin >> words;
  std::vector<int> word_counts(words);
  
  int total_words = 0;
  for(int i = 0; i < words; i++){
    int count; std::cin >> count;
    total_words += count;
    word_counts[i] = count;
  }
  
  // position, index
  std::vector<std::pair<int,int>> words_array;
  words_array.reserve(total_words);
  
  for(int i = 0; i < (int)word_counts.size(); i++) {
    for(int j = 0; j < word_counts[i]; j++) {
      int position; std::cin >> position;
      words_array.emplace_back(position, i);
    }
  }
  
  std::sort(std::begin(words_array), std::end(words_array), [&](const auto &p1, const auto &p2){
    return p1.first < p2.first;
  });
  
  std::vector<int> counts(words, 0);
  int remaining_words = words;
  int min_range = std::numeric_limits<int>::max();
  int back = 0;
  
  // Iterate over the sorted input with two pointers
  for(int i = 0; i < (int)words_array.size(); i++) {
    if (!counts[words_array[i].second]++) {
      remaining_words--;
    }
    
    while(!remaining_words) {
      const int range = words_array[i].first - words_array[back].first + 1;
      min_range = std::min(range, min_range);
        
      if (!--counts[words_array[back++].second]) {
        remaining_words++;
      }
    }
  }
  
  std::cout << min_range << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false)
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
  return 0;
}
