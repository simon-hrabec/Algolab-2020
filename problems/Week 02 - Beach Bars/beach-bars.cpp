#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

void solve(){
  int place_count; std::cin >> place_count;
  std::vector<int> places(place_count);
  for(int i = 0; i < place_count; i++){
    std::cin >> places[i];
  }

  std::sort(std::begin(places), std::end(places));

  int count_best = 0, distance_best = std::numeric_limits<int>::max(), last = 0;
  std::vector<int> results;

  for(int i = 0; i < place_count; i++) {
    while(places[i] - places[last] > 200) {
      last++;
    }

    const int count_current = i-last+1;
    const int range = places[i]-places[last];
    const int distance_current = (range+1)/2;

    const auto add_elems = [&](){
      if (range & 1) {
        results.push_back(places[last]+distance_current-1);
        results.push_back(places[last]+distance_current);
      }  else {
        results.push_back(places[last]+distance_current);
      }
    };

    if (count_current > count_best) {
      results.clear();
      count_best = count_current;
      distance_best = distance_current;

      add_elems();
    } else if (count_current == count_best && distance_current <= distance_best) {
      if (distance_current < distance_best) {
        results.clear();
        distance_best = distance_current;
      }

      add_elems();
    } 
  }

  std::cout << count_best << " " << distance_best << std::endl;
  for(const int place : results) {
    std::cout << place << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
  return 0;
}
