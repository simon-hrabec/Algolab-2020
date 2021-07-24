#include <iostream>
#include <iomanip>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using K = CGAL::Exact_predicates_inexact_constructions_kernel;
using Triangulation = CGAL::Delaunay_triangulation_2<K>;
using Point = K::Point_2;

using v2dp = std::vector<Point>;
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

void solve(const int restaurant_count) {
  const auto restaurants = loadv2dp(restaurant_count);
  const int location_count = load<int>();
  const auto locations = loadv2dp(location_count);
  
  Triangulation t(std::begin(restaurants), std::end(restaurants));
  for(const auto p : locations) {
    std::cout << std::fixed << std::setprecision(0) << CGAL::squared_distance(p, t.nearest_vertex(p)->point()) << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  while(true) {
    const int restaurant_count = load<int>();
    if (restaurant_count == 0) {
      return 0;
    }
    solve(restaurant_count);
  }
}
