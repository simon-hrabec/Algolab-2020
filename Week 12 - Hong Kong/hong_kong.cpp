#include <iostream>
#include <vector>
#include <queue>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

using K = CGAL::Exact_predicates_exact_constructions_kernel;

using Vb = CGAL::Triangulation_vertex_base_2<K>;
using Fb = CGAL::Triangulation_face_base_with_info_2<K::FT, K>;
using Tds = CGAL::Triangulation_data_structure_2<Vb, Fb>;
using Triangulation = CGAL::Delaunay_triangulation_2<K, Tds>;
using Point = K::Point_2;

using v2dp = std::vector<Point>;
using vp2dpl = std::vector<std::pair<Point, int64_t>>;

template<typename T>
T load() {
  T val;
  std::cin >> val;
  return val;
}

v2dp loadv2dp(const int count) {
  v2dp v;
  v.reserve(count);
  for(int i = 0; i < count; i++) {
    int64_t a, b;
    std::cin >> a >> b;
    v.emplace_back(a, b);
  }
  return v;
}

vp2dpl loadvp2dpl(const int count) {
  vp2dpl v;
  v.reserve(count);
  for(int i = 0; i < count; i++) {
    int64_t a, b, c;
    std::cin >> a >> b >> c;
    v.emplace_back(Point(a, b), c);
  }
  return v;
}

const K::FT max_value = K::FT(int64_t(1)<<53) * K::FT(int64_t(1)<<53);

void fill_triangulation(Triangulation & t) {
  std::priority_queue<std::pair<K::FT, Triangulation::Face_handle>> q;
  
  for (auto f = t.all_faces_begin(); f != t.all_faces_end(); ++f) {
    if (t.is_infinite(f)) {
      q.emplace(max_value, f);
    } else {
      const K::FT face_len_squared = squared_radius(f->vertex(0)->point(), f->vertex(1)->point(), f->vertex(2)->point());
      q.emplace(face_len_squared, f);
    }
  }
  
  while(!q.empty()) {
    auto p = q.top(); q.pop();
    const auto max_len = p.first;
    auto handle = p.second;
    
    if (handle->info() != 0) {
      continue;
    }
    handle->info() = max_len;
  
    for(int i = 0; i < 3; i++) {
      const auto neighbor = handle->neighbor(i);
      if (t.is_infinite(neighbor)) {
        continue;
      }
      const auto& v1 = handle->vertex((i+1)%3)->point();
      const auto& v2 = handle->vertex((i+2)%3)->point();
      const K::FT min_cost = std::min(CGAL::squared_distance(v1, v2), max_len);
      q.emplace(min_cost, neighbor);
    }
  }
}

void solve() {
  const auto tree_count = load<int>();
  const auto balloon_count = load<int>();
  const auto tree_radius = load<int64_t>();
  
  const auto trees = loadv2dp(tree_count);
  const auto balloons = loadvp2dpl(balloon_count);
  
  Triangulation t(std::begin(trees), std::end(trees));
  fill_triangulation(t);
  
  for(const auto &[point, balloon_radius] : balloons) {
    const K::FT min_distance_from_point = K::FT(tree_radius + balloon_radius) * K::FT(tree_radius + balloon_radius);
    if (CGAL::squared_distance(t.nearest_vertex(point)->point(), point) < min_distance_from_point) {
      std::cout << 'n';
      continue;
    }
    
    const K::FT min_edge_len = 4*min_distance_from_point;
    const bool valid = t.locate(point)->info() >= min_edge_len;
    std::cout << "ny"[valid];
  }
  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T;
  std::cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
