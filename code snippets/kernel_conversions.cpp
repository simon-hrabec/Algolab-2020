#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

using EPECK = CGAL::Exact_predicates_exact_constructions_kernel;
using EPECK_SQRT = CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt;

EPECK::Point_2 first_point(10, 20);
EPECK_SQRT::Point_2 second_point(static_cast<int64_t>(CGAL::exact(first_point.x())), static_cast<int64_t>(CGAL::exact(first_point.y())));
