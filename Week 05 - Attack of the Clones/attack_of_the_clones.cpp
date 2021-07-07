#include <iostream>
#include <vector>
#include <algorithm>

void solve(){
  int jedi_count, segment_count; std::cin >> jedi_count >> segment_count;
  const int edge_count = jedi_count*2;
  
  // Load data
  int used = 0;
  std::vector<std::pair<int64_t,int64_t>> segments(jedi_count); // to, from
  std::vector<std::pair<int, bool>> edges(jedi_count*2); // position, is_end
  for(int i = 0; i < jedi_count; i++) {
    int a,b; std::cin >> a >> b;
    a -= 1;
    b -= 1;
    segments[i].second = a;
    segments[i].first = b;
    
    edges[2*i] = {a, false};
    edges[2*i+1] = {b, true};
    
    // already count jedi that go over the end
    if (b < a) {
      used++;
    }
  }
  
  std::sort(std::begin(edges), std::end(edges));
  
  // Include jedi that start at 0
  int64_t position = 0;
  while(position < edge_count && edges[position].first == 0 && edges[position].second == false) {
    used++;
    position++;
  }
  
  // Find best start (least used)
  int best_used = used;
  int64_t best_position = 0;
  while(position < edge_count) {
    int64_t current = edges[position].first;
    while(position < edge_count && edges[position].first == current && edges[position].second == false) {
      used++;
      position++;
    }
    
    if (used < best_used) {
      best_used = used;
      best_position = current;
    }
    
    while(position < edge_count && edges[position].first == current) {
      used--;
      position++;
    }
    
    if ((position < edge_count && edges[position].first != current + 1) || (position == edge_count && current+1 < segment_count)) {
      if (used < best_used) {
        best_used = used;
        best_position = current+1;
      }
    }
  }
  
  // Find jedi present in least occupied sector
  std::vector<int64_t> possible_starts = {best_position};
  for(const auto &s : segments) {
    const int64_t from = s.second;
    const int64_t to = s.first;
    if ((from <= to && best_position >= from && best_position <= to) || (from > to && (best_position >= from || best_position <= to))) {
      possible_starts.push_back(to);
    }
    for(int64_t &elem : possible_starts) {
      if (elem == segment_count) {
        elem = 0;
      }
    }
  }

  // Run the greedy algorithm for all jedi in the least used sector
  int result = 0;
  std::vector<std::pair<int64_t,int64_t>> shifted;
  for(const int64_t elem : possible_starts) {
    shifted = segments;
    for(auto &p : shifted) {
      if (p.second > p.first) {
        p.first += segment_count;
      }
      
      if (p.second <= elem) {
        p.first += segment_count; 
        p.second += segment_count;
      }
    }
    
    std::sort(std::begin(shifted), std::end(shifted));
    int picked = 0;
    int64_t pos = elem;
    for(const auto p : shifted) {
      if (p.second > pos && p.first <= elem+segment_count) {
        pos = p.first;
        picked ++;
      }
    }
    result = std::max(result, picked);
  }
  
  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
}
