#include <iostream>
#include <queue>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

using K = CGAL::Exact_predicates_inexact_constructions_kernel;
using Point = K::Point_2;
using v2dp = std::vector<Point>;

using Vb = CGAL::Triangulation_vertex_base_with_info_2<bool, K>;
using Fb = CGAL::Triangulation_face_base_2<K>;
using Tds = CGAL::Triangulation_data_structure_2<Vb, Fb>;
using Triangulation = CGAL::Delaunay_triangulation_2<K, Tds>;

Point loadpoint(){
  int a, b;
  std::cin >> a >> b;
  return Point{a, b};
}

v2dp loadv2dp(const int count) {
  v2dp v;
  v.reserve(count);
  for(int i = 0; i < count; i++) {
    v.push_back(loadpoint());
  }
  return v;
}

template <typename T>
T load() {
  T val;
  std::cin >> val;
  return val;
}

const int max_connected_component_size(const v2dp& planets, const int used_planets_beginning, const double squared_max_range) {
  Triangulation t(std::begin(planets)+used_planets_beginning, std::end(planets));
  for(auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v){
    v->info() = false;
  }
  
  int max_component_size = 0;
  // Run from BFS from every unvisited node
  for(auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v){
    int component_size = 0;
    std::queue<Triangulation::Vertex_handle> q;
    q.push(v);
    
    while(!q.empty()) {
      const auto current_vertex = q.front();
      q.pop();
      if(!current_vertex->info()) {
        component_size++;
        current_vertex->info() = true;
        Triangulation::Vertex_circulator c = t.incident_vertices(current_vertex);
        do {
          if (!t.is_infinite(c) && CGAL::squared_distance(current_vertex->point(), c->point()) <= squared_max_range){
            q.push(c);
          }
        } while (++c != t.incident_vertices(current_vertex));
      }
    }
    max_component_size = std::max(max_component_size, component_size);
  }
  
  return max_component_size;
}

void solve() {
  const int nr_planets = load<int>();
  const double range = load<double>();
  const double squared_range = range*range;
  const auto planets = loadv2dp(nr_planets);
  
  if (nr_planets <= 3) {
    std::cout << 1 << std::endl;
    return;
  }
  
  int best_result = 0;
  int low = 2, high = nr_planets/2;
  while (low <= high) {
    const int mid = (low+high)/2;
    const int max_component_size = max_connected_component_size(planets, mid, squared_range);

    if (mid == max_component_size) {
      best_result = mid;
      break;
    }
    if (mid < max_component_size) {
      best_result = std::max(best_result, mid);
      low = mid+1;
      high = std::min(high, max_component_size);
    } else {
      best_result = std::max(best_result, max_component_size);
      low = std::max(low, max_component_size);
      high = mid-1;
    }
  }
  
  std::cout << best_result << std::endl;
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
