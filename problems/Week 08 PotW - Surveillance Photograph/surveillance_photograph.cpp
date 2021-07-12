#include <iostream>
#include <vector>
#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using vi = std::vector<int>;
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
T loadv(const int count) {
  T v(count);
  for(int i = 0; i < count; i++) {
    std::cin >> v[i];
  }
  return v;
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

void solve(){
  const auto intersection_count = load<int>();
  const auto street_count = load<int>();
  const auto station_count = load<int>();
  const auto photo_count = load<int>();

  const auto stations = loadv<vi>(station_count);
  const auto photos = loadv<vi>(photo_count);
  const auto streets = loadvp<vpii>(street_count);

  graph g(2*intersection_count);
  edge_adder adder(g);
  const vertex_desc source = boost::add_vertex(g);
  const vertex_desc target = boost::add_vertex(g);
  const int offset = intersection_count;

  // Edges from source
  // Street to photo
  // Picking photo - transitioning to a new graph
  // Streets from photo to station (1 policeman only)
  // Edges to target

  for(const auto station : stations) adder.add_edge(source, station, 1);
  for(const auto street : streets) adder.add_edge(street.first, street.second, station_count);
  for(const auto photo : photos) adder.add_edge(photo, photo+offset, 1);
  for(const auto street : streets) adder.add_edge(street.first+offset, street.second+offset, 1);
  for(const auto station : stations) adder.add_edge(station+offset, target, 1);

  const int result = boost::push_relabel_max_flow(g, source, target);

  std::cout << result << std::endl;
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
