#include <iostream>
#include <vector>

#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

using Kernel = CGAL::Exact_predicates_inexact_constructions_kernel;
using Traits = CGAL::Min_circle_2_traits_2<Kernel>;
using Min_circle = CGAL::Min_circle_2<Traits>;
using Point = Kernel::Point_2;

using SQRT_Kernel = CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt;
using SQRT_Point = SQRT_Kernel::Point_2;
using SQRT_Circle = SQRT_Kernel::Circle_2;

template <typename T>
int64_t round_up(const T &input_val) {
  double num = std::ceil(CGAL::to_double(input_val));

  while (num > input_val) num -= 1;
  while (num < input_val) num += 1;
  return static_cast<int64_t>(num);
}

void solve(const int nr_points){
  std::vector<Point> points;
  points.reserve(nr_points);

  for(int i = 0; i < nr_points; i++) {
    int64_t x,y; std::cin >> x >> y;
    points.emplace_back(x,y);
  }

  if(nr_points == 1) {
    std::cout << 0 << std::endl;
    return;
  }

  const Min_circle mc(std::begin(points), std::end(points), true);

  std::vector<SQRT_Point> sqrt_points;
  for(auto iter = mc.support_points_begin(); iter != mc.support_points_end(); ++iter) {
    sqrt_points.emplace_back(iter->x(), iter->y());
  }

  SQRT_Circle circle = (sqrt_points.size() == 3 ?
    SQRT_Circle(sqrt_points[0], sqrt_points[1], sqrt_points[2]) :
    SQRT_Circle(sqrt_points[0], sqrt_points[1]));

  std::cout << round_up(CGAL::sqrt(circle.squared_radius())) << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  while(true) {
    int nr_points;
    std::cin >> nr_points;
    if (nr_points == 0) {
      break;
    }
    solve(nr_points);
  }
  return 0;
}
