#include <array>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

using K = CGAL::Exact_predicates_exact_constructions_kernel;
using Traits = CGAL::Min_circle_2_traits_2<K>;
using Min_circle = CGAL::Min_circle_2<Traits>;
using Point = K::Point_2;

const std::array<Point, 5> points = {{{5, 6}, {1, 3}, {4, 2}, {6, 1}, {3, 3}}};

// Pass true for randomization of the order of the points
const Min_circle mc(std::begin(points), std::end(points), true);
for(auto iter = mc.support_points_begin(); iter != mc.support_points_end(); ++iter) {
  std::cout << *iter << std::endl;
}

const Traits::Circle &c = mc.circle();
std::cout << c.center() << std::endl;
std::cout << c.squared_radius() << std::endl;
