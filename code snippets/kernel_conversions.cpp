#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

sqrt_points.emplace_back(static_cast<int64_t>(CGAL::exact(iter->x())), static_cast<int64_t>(CGAL::exact(iter->y())));