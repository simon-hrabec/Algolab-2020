#include <iostream>
#include <vector>
#include <array>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using Kernel = CGAL::Exact_predicates_inexact_constructions_kernel;
using Point = Kernel::Point_2;
using Line = Kernel::Line_2;

Line create_line(Point pl1, Point pl2, Point p) {
  if (CGAL::right_turn(pl1, pl2, p)) {
    std::swap(pl1, pl2);
  }
  return Line(pl1, pl2);
}

bool inside(const Line &l1, const Line &l2, const Line &l3, const Point &p) {
  const bool outside_triangle = l1.has_on_negative_side(p) || l2.has_on_negative_side(p) || l3.has_on_negative_side(p);
  return !outside_triangle;
}

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
    
    Line l1 = create_line(a1, a2, b1);
    Line l2 = create_line(b1, b2, c1);
    Line l3 = create_line(c1, c2, a1);
    
    for(int j = 0; j < leg_count; j++) {
      map_has_leg[i][j] = inside(l1, l2, l3, points[j]) && inside(l1, l2, l3, points[j+1]);
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
}
