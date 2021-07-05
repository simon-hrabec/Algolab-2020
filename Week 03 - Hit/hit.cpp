#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using Kernel = CGAL::Exact_predicates_inexact_constructions_kernel;
using Point = Kernel::Point_2;
using Segment = Kernel::Segment_2;
using Ray = Kernel::Ray_2;

Point load_point(){
  int64_t a, b;
  std::cin >> a >> b;
  return Point{a, b};
}

void skip_input(const int count) {
  for(int i = 0; i < count*4; i++) {
    int64_t num; std::cin >> num;
  }
}

void solve(int nr_obstacles){
  const Point ray_start = load_point(), ray_end = load_point();
  Ray ray(ray_start, ray_end);
  bool hit = false;

  while(nr_obstacles--) {
    const Point obstacle_from = load_point(), obstacle_to = load_point();
    Segment obstacle(obstacle_from, obstacle_to);

    if (CGAL::do_intersect(ray, obstacle)) {
      hit = true;
      break;
    }
  }

  skip_input(nr_obstacles);
  std::cout << (hit ? "yes" : "no") << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  while(true) {
    int nr_obstacles; std::cin >> nr_obstacles;
    if (nr_obstacles == 0) {
      return 0;
    }
    solve(nr_obstacles);
  }
  return 0;
}
