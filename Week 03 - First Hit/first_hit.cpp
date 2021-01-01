#include <iostream>
#include <array>
#include <algorithm>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

using Kernel = CGAL::Exact_predicates_exact_constructions_kernel;
using Point = Kernel::Point_2;
using Segment = Kernel::Segment_2;
using Ray = Kernel::Ray_2;

int64_t round_down(const Kernel::FT &input_val)
{
  double num = std::floor(CGAL::to_double(input_val));
  while (num > input_val) num -= 1;
  while (num+1 <= input_val) num += 1;
  return static_cast<int64_t>(num);
}

template <typename INTER>
Segment shorter_segment(INTER intersection_object, Point ray_start) {
  if (const Point* intersection_point = boost::get<Point>(&*intersection_object)) {
    return Segment(ray_start, *intersection_point);
  } else if (const Segment* intersection_segment = boost::get<Segment>(&*intersection_object)) {
    const auto p1 = intersection_segment->source();
    const auto p2 = intersection_segment->target();
    return Segment(ray_start, CGAL::has_smaller_distance_to_point(ray_start, p1, p2) ? p1 : p2);
  } else {
    // should not happen
    return Segment(ray_start, ray_start);
  }
}

Point load_point(){
  int64_t a, b;
  std::cin >> a >> b;
  return Point{a, b};
}

template <typename T>
T load_geometric_object(){
  const Point p1 = load_point();
  const Point p2 = load_point();
  return T{p1, p2}; 
}

Segment coordinates_to_segment(const std::array<int64_t, 4> &coordinates) {
  return Segment({coordinates[0], coordinates[1]}, {coordinates[2], coordinates[3]});
}

void solve(const int nr_obstacles) {
  // Load input
  const Ray ray = load_geometric_object<Ray>();
  std::array<std::array<int64_t, 4>, 30'000> obstacle_coordinates;
  for(int i = 0; i < nr_obstacles; i++) {
    std::cin >> obstacle_coordinates[i][0] >> obstacle_coordinates[i][1] >> obstacle_coordinates[i][2] >> obstacle_coordinates[i][3];
  }
  std::random_shuffle(std::begin(obstacle_coordinates), std::begin(obstacle_coordinates)+nr_obstacles);
  
  // declare variables
  int iter;
  bool found = false;
  Segment ray_segment;
  
  // find first collision
  for(iter = 0; iter < nr_obstacles; iter++) {
    const Segment obstacle = coordinates_to_segment(obstacle_coordinates[iter]);
    if (CGAL::do_intersect(obstacle, ray)) {
      const auto intersection_object = CGAL::intersection(obstacle, ray);
      ray_segment = shorter_segment(intersection_object, ray.source());
      found = true;
      iter++;
      break;
    }
  }
  
  if(!found) {
    std::cout << "no" << std::endl;
    return;
  }
  
  // process other collisions
  for(;iter < nr_obstacles; iter++) {
    const Segment obstacle = coordinates_to_segment(obstacle_coordinates[iter]);
    if (CGAL::do_intersect(obstacle, ray_segment)) {
      const auto intersection_object = CGAL::intersection(obstacle, ray_segment);
      ray_segment = shorter_segment(intersection_object, ray_segment.source());
    }
  }

  std::cout << round_down(ray_segment.target().x()) << " " << round_down(ray_segment.target().y()) << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  while(true) {
    int nr_obstacles; std::cin >> nr_obstacles;
    if (nr_obstacles == 0) {
      return 0;
    }
    solve(nr_obstacles);
  }
}
