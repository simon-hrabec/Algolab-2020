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
using vertex_desc = boost::graph_traits<graph>::vertex_descriptor;

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

template<typename T1, typename T2>
using vp = std::vector<std::pair<T1,T2>>;
using vpii = vp<int,int>;

template<typename T>
T load() {
  T val;
  std::cin >> val;
  return val;
}

template<typename T>
T loadvp(const int count) {
  T v(count);
  for(int i = 0; i < count; i++) {
    std::cin >> v[i].first;
    std::cin >> v[i].second;
  }
  return v;
}

void solve() {
  // Load data
  const int cols = load<int>();
  const int rows = load<int>();
  const int knight_count = load<int>();
  const int maxc = load<int>();

  const auto knights = loadvp<vpii>(knight_count);

  const int room_count = cols*rows;

  // Create graph
  graph g(2*room_count);
  edge_adder adder(g);
  const vertex_desc source = boost::add_vertex(g);
  const vertex_desc target = boost::add_vertex(g);
  const int offset = room_count;

  const auto get_idx = [cols](const int c, const int r){
    return cols*r+c;
  };

  // Outgoing edges + connecting edges
  for(int i = 0; i < cols; i++) {
    for(int j = 0; j < rows; j++) {
      const int idx = get_idx(i, j);
      adder.add_edge(idx, idx+offset, maxc);

      const int pathways_out = (i == 0) + (j == 0) + (i == cols-1) + (j == rows-1);
      if (pathways_out > 0) {
        adder.add_edge(idx+offset, target, pathways_out);
      }

      if (i > 0) {
        adder.add_edge(idx+offset, idx-1, 1);
        adder.add_edge(idx+offset-1, idx, 1);
      }
      if (j > 0) {
        adder.add_edge(idx+offset, idx-cols, 1);
        adder.add_edge(idx+offset-cols, idx, 1);
      }
    }
  }

  // Incoming edges
  for(const auto &[col, row] : knights) {
    const int idx = get_idx(col, row);
    adder.add_edge(source, idx, 1);
  }

  const int result = boost::push_relabel_max_flow(g, source, target);

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
