#include <iostream>
#include <vector>
#include <limits>
#include <queue>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

using K = CGAL::Exact_predicates_inexact_constructions_kernel;

using Index = std::size_t;
using Vb = CGAL::Triangulation_vertex_base_2<K>;
using Fb = CGAL::Triangulation_face_base_with_info_2<double, K>;
using Tds = CGAL::Triangulation_data_structure_2<Vb, Fb>;
using Triangulation = CGAL::Delaunay_triangulation_2<K, Tds>;

using Point = K::Point_2;

using v2dp = std::vector<Point>;
using tiil = std::tuple<int, int, double>;
using v3iil = std::vector<tiil>;
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
    int a, b;
    std::cin >> a >> b;
    v.emplace_back(a, b);
  }
  return v;
}

v3iil loadv3iil(const int count) {
  v3iil v;
  v.reserve(count);
  for(int i = 0; i < count; i++) {
    int a, b;
    double c;
    std::cin >> a >> b >> c;
    v.emplace_back(a, b, c);
  }
  return v;
}

void fill_triangulation(Triangulation & t) {
  std::priority_queue<std::pair<double, Triangulation::Face_handle>> q;

  for(auto f = t.all_faces_begin(); f != t.all_faces_end(); ++f) {
    if (t.is_infinite(f)) {
      q.emplace(std::numeric_limits<long>::max(), f);
    }
    f->info() = 0;
  }

  while(!q.empty()) {
    auto p = q.top(); q.pop();
    const auto cost = p.first;
    auto handle = p.second;
    if (handle->info() >= cost) {
      continue;
    }
    handle->info() = cost;
    for(int i = 0; i < 3; i++) {
      const auto neighbor = handle->neighbor(i);
      if (t.is_infinite(neighbor) || neighbor->info() != 0) {
        continue;
      }
      const auto& v1 = handle->vertex((i+1)%3)->point();
      const auto& v2 = handle->vertex((i+2)%3)->point();
      const double min_cost = std::min(CGAL::squared_distance(v1, v2), cost);
      q.emplace(min_cost, neighbor);
    }
  }
}

void solve(const int point_count) {
  const auto points = loadv2dp(point_count);
  const int query_count = load<int>();
  const auto query_points = loadv3iil(query_count);

  Triangulation t(std::begin(points), std::end(points));
  fill_triangulation(t);

  // Check if we can move disc out of the face
  for(const auto &qp : query_points) {
    Point p(std::get<0>(qp), std::get<1>(qp));
    const double allowed_s_distance = std::get<2>(qp);

    if (CGAL::squared_distance(t.nearest_vertex(p)->point(), p) < allowed_s_distance) {
      std::cout << 'n';
      continue;
    }

    const double min_edge_len = 4*allowed_s_distance;
    const bool valid = t.locate(p)->info() >= min_edge_len;
    std::cout << "ny"[valid];
  }

  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  while(true) {
    const int point_count = load<int>();
    if (point_count == 0) {
      return 0;
    }
    solve(point_count);
  }
}
