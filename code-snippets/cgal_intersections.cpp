#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

using K = CGAL::Exact_predicates_exact_constructions_kernel;
using Point = K::Point_2;
using Segment = K::Segment_2;
using Ray = K::Ray_2;

Ray ray;
Segment segment;

if (CGAL::do_intersect(ray, segment)) {
  const auto intersection_object = CGAL::intersection(ray, segment);
  if (const Point* intersection_point = boost::get<Point>(&*intersection_object)) {
    std::cout << "Point: " << *intersection_point << std::endl;
  } else if (const Segment* intersection_segment = boost::get<Segment>(&*intersection_object)) {
    std::cout << "Segment: " << intersection_segment->souce() << " " << intersection_segment->target() << std::endl;
  } else {
    throw std::runtime_error("strange segment intersection");
  }
}
