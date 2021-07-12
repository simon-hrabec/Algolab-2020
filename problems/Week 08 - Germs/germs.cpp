#include <iostream>
#include <vector>
#include <algorithm>

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

void solve(const int nr_cells) {
  const int left = load<int>();
  const int bottom = load<int>();
  const int right = load<int>();
  const int top = load<int>();

  const auto cells = loadv2dp(nr_cells);

  Triangulation t(std::begin(cells), std::end(cells));

  std::vector<double> min_distances;
  min_distances.reserve(nr_cells);

  for(auto vertex = t.finite_vertices_begin(); vertex != t.finite_vertices_end(); ++vertex){
    const double x = vertex->point().x();
    const double y = vertex->point().y();
    double die_distance = std::min({std::abs(left-x), std::abs(right-x), std::abs(top-y), std::abs(bottom-y)});

    double closest_squared_die_distance = std::numeric_limits<double>::max();
    auto vertex_c = t.incident_vertices(vertex), done(vertex_c);
    if (vertex_c != 0) {
      do {
        if (!t.is_infinite(vertex_c)) {
          closest_squared_die_distance = std::min(closest_squared_die_distance, CGAL::squared_distance(vertex->point(), vertex_c->point()));
        }
      } while (++vertex_c != done);
    }

    min_distances.push_back(std::min(die_distance-0.5, (std::sqrt(closest_squared_die_distance)-1)/2));
  }

  const int mid_point = nr_cells/2;
  std::nth_element(std::begin(min_distances), std::begin(min_distances) + mid_point, std::end(min_distances));

  const auto ceil_and_sqrt = [](const double &num){
    return std::ceil(std::sqrt(num));
  };

  const double first_to_die = ceil_and_sqrt(*std::min_element(std::begin(min_distances), std::begin(min_distances)+mid_point+1));
  const double half_dead = ceil_and_sqrt(min_distances[mid_point]);
  const double last_to_die = ceil_and_sqrt(*std::max_element(std::begin(min_distances)+mid_point, std::end(min_distances)));

  std::cout << first_to_die << " " << half_dead << " "<< last_to_die << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  while(true) {
    const int nr_cells = load<int>();
    if (nr_cells == 0) {
      return 0;
    }
    solve(nr_cells);
  }
  return 0;
}
