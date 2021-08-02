#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using traits = boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS>;
using graph = boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::directedS,
  boost::no_property,
  boost::property<boost::edge_capacity_t, int,
    boost::property<boost::edge_residual_capacity_t, int,
      boost::property<boost::edge_reverse_t, traits::edge_descriptor>
    >
  >
>;

class edge_adder {
  graph &g;

public:
  explicit edge_adder(graph &g) : g(g) {}

  void add_edge(int from, int to, int capacity) {
    auto c_map = boost::get(boost::edge_capacity, g);
    auto r_map = boost::get(boost::edge_reverse, g);
    const auto e = boost::add_edge(from, to, g).first;
    const auto rev_e = boost::add_edge(to, from, g).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

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
  edge_adder adder(g);

  const vertex_desc source = boost::add_vertex(g);
  const vertex_desc target = boost::add_vertex(g);

  const auto get_idx = [y_size](const int x, const int y){
    return x*y_size+y;
  };

  int empty = 0;

  for(int i = 0; i < x_size; i++) {
    for(int j = 0; j < y_size; j++) {
      const int idx = get_idx(i, j);
      if (fields[idx] == '.') {
        empty++;

        if ((i+j) & 1) {
          adder.add_edge(source, idx, 1);
        } else {
          adder.add_edge(idx, target, 1);
        }

        const int left = get_idx(i-1, j);
        const int top = get_idx(i, j-1);

        if (i && fields[left] == '.') {
          if ((i+j) & 1) {
            adder.add_edge(idx, left, 1);
          } else {
            adder.add_edge(left, idx, 1);
          }
        }
        if (j && fields[top] == '.') {
          if ((i+j) & 1) {
            adder.add_edge(idx, top, 1);
          } else {
            adder.add_edge(top, idx, 1);
          }
        }
      }
    }
  }

  if (empty & 1) {
    std::cout << "no" << std::endl;
    return;
  }

  const int flow = boost::push_relabel_max_flow(g, source, target);
  const std::string result = (flow == empty/2 ? "yes" : "no");
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
