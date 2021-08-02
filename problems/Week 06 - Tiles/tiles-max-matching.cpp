#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using graph = boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::undirectedS
>;
using vertex_desc = boost::graph_traits<graph>::vertex_descriptor;

using vc = std::vector<char>;

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

void solve() {
  const int y_size = load<int>();
  const int x_size = load<int>();
  const int total_size = x_size * y_size;

  const auto fields = loadv<vc>(total_size);

  graph g(total_size);

  const auto get_idx = [y_size](const int x, const int y){
    return x*y_size+y;
  };

  int empty = 0;

  for(int i = 0; i < x_size; i++) {
    for(int j = 0; j < y_size; j++) {
      const int idx = get_idx(i, j);
      if (fields[idx] == '.') {
        empty++;

        const int left = get_idx(i-1, j);
        const int top = get_idx(i, j-1);

        if (i && fields[left] == '.') {
          boost::add_edge(idx, left, g);
        }
        if (j && fields[top] == '.') {
          boost::add_edge(idx, top, g);
        }
      }
    }
  }

  if (empty & 1) {
    std::cout << "no" << std::endl;
    return;
  }

  std::vector<vertex_desc> domino(total_size);
  boost::edmonds_maximum_cardinality_matching(g, &domino[0]);
  const int pairs = static_cast<int>(boost::matching_size(g, &domino[0]));
  const std::string result = (pairs == empty/2 ? "yes" : "no");
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
