#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using traits = boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> ;
using graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> ;

using vertex_desc = boost::graph_traits<graph>::vertex_descriptor;

class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

template<typename T>
T load(){
  T val;
  std::cin >> val;
  return val;
}

void solve() {
  const int board_size = load<int>();
  const int field_count = board_size*board_size;
  const int outgoing_offset = field_count;
  
  graph G(2*field_count);  
  edge_adder adder(G);
  const vertex_desc source = boost::add_vertex(G);
  const vertex_desc target = boost::add_vertex(G);
  
  const auto add_if_in_range = [board_size, outgoing_offset, &adder](const int from_idx, const int to_x, const int to_y){
    if (to_x >= 0 && to_x < board_size && to_y >= 0 && to_y < board_size) {
      adder.add_edge(from_idx, to_x*board_size + to_y + outgoing_offset, 1);
    }
  };
  
  int valid_field_count = 0;
  
  for (int i = 0; i < board_size; i++){
    for (int j = 0; j < board_size; j++){
      const int field_idx = i*board_size + j;
      const bool black_field = (i+j) & 1;
      
      const bool present = load<bool>();
      valid_field_count += present;
      
      if (present) {
        if (black_field) {
          adder.add_edge(source, field_idx, 1);
        } else {
          adder.add_edge(field_idx+outgoing_offset, target, 1);
        }
      }
      
      if (black_field) {
        add_if_in_range(field_idx, i-1, j-2);
        add_if_in_range(field_idx, i-2, j-1);
        add_if_in_range(field_idx, i-1, j+2);
        add_if_in_range(field_idx, i-2, j+1);
        add_if_in_range(field_idx, i+1, j-2);
        add_if_in_range(field_idx, i+2, j-1);
        add_if_in_range(field_idx, i+1, j+2);
        add_if_in_range(field_idx, i+2, j+1);
      }
    }
  }
  
  const int flow = boost::push_relabel_max_flow(G, source, target);
  std::cout << (valid_field_count-flow) << std::endl;
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
