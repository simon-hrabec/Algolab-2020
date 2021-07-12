#include <iostream>
#include <vector>
#include <array>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

using Kernel = CGAL::Exact_predicates_exact_constructions_kernel;
using Point = Kernel::Point_2;
using Line = Kernel::Line_2;
using Triangle = Kernel::Triangle_2;

void solve(){
  int point_count, map_count; std::cin >> point_count >> map_count;
  const int leg_count = point_count - 1;

  std::vector<Point> points(point_count);
  for(int i = 0; i < point_count; i++) {
    int x, y; std:: cin >> x >> y;
    points[i] = Point(x, y);
  }

  std::array<std::array<bool, 2000>, 2000> map_has_leg = {};

  for(int i = 0; i < map_count; i++) {
    int ax1, ay1, ax2, ay2, bx1, by1, bx2, by2, cx1, cy1, cx2, cy2;
    std::cin >> ax1 >> ay1 >> ax2 >> ay2 >> bx1 >> by1 >> bx2 >> by2 >> cx1 >> cy1 >> cx2 >> cy2;
    Point a1(ax1, ay1), a2(ax2, ay2);
    Point b1(bx1, by1), b2(bx2, by2);
    Point c1(cx1, cy1), c2(cx2, cy2);

    Line l1 = Line(a1, a2);
    Line l2 = Line(b1, b2);
    Line l3 = Line(c1, c2);

    const auto intersection_object1 = CGAL::intersection(l1, l2);
    const auto intersection_object2 = CGAL::intersection(l2, l3);
    const auto intersection_object3 = CGAL::intersection(l3, l1);

    const Point p1 = *boost::get<Point>(&*intersection_object1);
    const Point p2 = *boost::get<Point>(&*intersection_object2);
    const Point p3 = *boost::get<Point>(&*intersection_object3);

    Triangle t(p1, p2, p3);

    for(int j = 0; j < leg_count; j++) {
      map_has_leg[i][j] = !t.has_on_unbounded_side(points[j]) && !t.has_on_unbounded_side(points[j+1]);
    }
  }

  int shortest = std::numeric_limits<int>::max();
  int legs_missing = leg_count;
  std::array<int, 2000> legs_present = {};

  // from inclusive, to exclusive
  int from = 0, to = 0;

  while(true) {
    if (legs_missing == 0) {
      for(int i = 0; i < leg_count; i++) {
        if (map_has_leg[from][i] && --legs_present[i] == 0) {
          legs_missing++;
        }
      }
      from++;
    } else {
      if (to == map_count) {
        break;
      }

      for(int i = 0; i < leg_count; i++) {
        if (map_has_leg[to][i] && ++legs_present[i] == 1) {
          legs_missing--;
        }
      }
      to++;
    }

    if (legs_missing == 0) {
      shortest = std::min(shortest, to-from);
    }
  }

  std::cout << shortest << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
  return 0;
}
