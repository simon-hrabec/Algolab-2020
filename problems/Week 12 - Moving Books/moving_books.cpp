#include <iostream>
#include <vector>
#include <algorithm>

using vi = std::vector<int>;

template <typename T>
T load(){
  T val;
  std::cin >> val;
  return val;
}

template<typename T, typename C = std::greater<typename T::value_type>>
T loadv_sorted(const int count) {
  T v(count);
  for(int i = 0; i < count; i++) {
    std::cin >> v[i];
  }
  std::sort(std::begin(v), std::end(v), C());
  return v;
}

void solve() {
  const auto nr_friends = load<int>();
  const auto nr_boxes = load<int>();

  const auto friends = loadv_sorted<vi>(nr_friends);
  const auto boxes = loadv_sorted<vi>(nr_boxes);

  if(friends[0] < boxes[0]) {
    std::cout << "impossible" << std::endl;
    return;
  }

  int low = (nr_boxes-1)/nr_friends+1, high = nr_boxes;
  while(low < high) {
    const int mid = (low+high)/2;
    const int friends_used = (nr_boxes-1)/mid+1;

    bool can_carry = true;
    for(int i = 0; i < friends_used; i++) {
      if (friends[i] < boxes[i*mid]) {
        can_carry = false;
        break;
      }
    }

    if(can_carry) {
      high = mid;
    } else {
      low = mid+1;
    }
  }

  std::cout << low*3-1 << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T;
  std::cin >> T;
  while(T--) {
    solve();
  }
  return 0;
}
