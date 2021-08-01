#include <iostream>
#include <array>
#include <tuple>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/QP_functions.h>

using IT = int;
using ET = CGAL::Gmpz;

using Program = CGAL::Quadratic_program<IT>;
using Solution = CGAL::Quadratic_program_solution<ET>;

using K = CGAL::Exact_predicates_inexact_constructions_kernel;
using Triangulation = CGAL::Delaunay_triangulation_2<K>;
using Point = K::Point_2;

int64_t round_down(const CGAL::Quotient<ET> &input_val)
{
  double num = std::floor(CGAL::to_double(input_val));
  while (num > input_val) num -= 1;
  while (num+1 <= input_val) num += 1;
  return static_cast<int64_t>(num);
}

template <typename T>
T load(){
  T val;
  std::cin >> val;
  return val;
}

bool is_inside_circle(const Point &p1, const Point &p2, const double squared_radius) {
  return CGAL::squared_distance(p1, p2) < squared_radius;
}

std::array<std::array<int, 200>, 200> profits;
std::array<std::tuple<Point, int, int>, 200> warehouses; // point, supply, alcohol
std::array<std::tuple<Point, int, int>, 20> stadiums; // point, demand, alcohol_limit
std::array<std::tuple<Point, double>, 1'000'000> circles; // point, squared_radius
std::array<std::tuple<Point, double>, 1000> used_circles;
std::array<bool, 100> stadium_inside_circle;

void solve(){
  const int warehouse_count = load<int>();
  const int stadium_count = load<int>();
  const int circle_count = load<int>();

  // Delivery equations (2*stadiums)
  // Max alcohol equations (1*stadiums)
  // Max supply equations (1*warehouses)
  const int delivery_equations_offset = 0;
  const int max_alcohol_equations_offset = 2*stadium_count;
  const int max_supply_equations_offset = max_alcohol_equations_offset + stadium_count;

  // Load data
  for(int i = 0; i < warehouse_count; i++) {
    const double x = load<double>();
    const double y = load<double>();
    const int supply = load<int>();
    const int alcohol_percentage = load<int>();
    warehouses[i] = {{x, y}, supply, alcohol_percentage};
  }

  for(int i = 0; i < stadium_count; i++) {
    const double x = load<double>();
    const double y = load<double>();
    const int demand = load<int>();
    const int alcohol_limit = load<int>();
    stadiums[i] = {{x, y}, demand, alcohol_limit};
  }

  for(int i = 0; i < warehouse_count; i++) {
    for(int j = 0; j < stadium_count; j++) {
      const int profit = load<int>();
      profits[i][j] = profit*100;
    }
  }

  for(int i = 0; i < circle_count; i++) {
    const double x = load<double>();
    const double y = load<double>();
    const double radius = load<double>();
    circles[i] = {{x, y}, radius*radius};
  }

  Program lp(CGAL::SMALLER, true, 0, false, 0);
  const auto get_variable_idx = [stadium_count](const int warehouse, const int stadium){
    return stadium + stadium_count * warehouse;
  };

  // Set up LP equations (delivered beer + max alcohol content)
  for(int i = 0; i < stadium_count; i++) {
    const int stadium_demand = std::get<1>(stadiums[i]);
    const int stadium_alcohol_limit = 100 * std::get<2>(stadiums[i]);
    for(int j = 0; j < warehouse_count; j++) {
      const int beer_alcohol_content = std::get<2>(warehouses[j]);
      const int idx = get_variable_idx(j,i);

      lp.set_a(idx, delivery_equations_offset+2*i, 1);
      lp.set_a(idx, delivery_equations_offset+2*i+1, -1);

      lp.set_a(idx, max_alcohol_equations_offset+i, beer_alcohol_content);
    }
    lp.set_b(delivery_equations_offset+2*i, stadium_demand);
    lp.set_b(delivery_equations_offset+2*i+1, -stadium_demand);

    lp.set_b(max_alcohol_equations_offset+i, stadium_alcohol_limit);
  }

  // Set up LP equations (warehouse supply)
  for(int i = 0; i < warehouse_count; i++) {
    const int warehouse_supply = std::get<1>(warehouses[i]);
    for(int j = 0; j < stadium_count; j++) {
      const int idx = get_variable_idx(i,j);

      lp.set_a(idx, max_supply_equations_offset+i, 1);
    }

    lp.set_b(max_supply_equations_offset+i, warehouse_supply);
  }

  // Merge stadiums and warehouses
  std::vector<Point> all_elements;
  all_elements.reserve(warehouse_count + stadium_count);
  for(int i = 0; i < warehouse_count; i++) {
    all_elements.push_back(std::get<0>(warehouses[i]));
  }
  for(int i = 0; i < stadium_count; i++) {
    all_elements.push_back(std::get<0>(stadiums[i]));
  }

  Triangulation t(std::begin(all_elements), std::end(all_elements));
  int used_circle_count = 0;

  // Find which circles are used
  for(int i = 0; i < circle_count; i++) {
    const auto &[point, squared_radius] = circles[i];
    if (is_inside_circle(point, t.nearest_vertex(point)->point(), squared_radius)) {
      used_circles[used_circle_count++] = {point, squared_radius};
    }
  }

  // Modify profits by crossed circles
  for(int i = 0; i < stadium_count; i++) {
    for(int k = 0; k < used_circle_count; k++) {
      stadium_inside_circle[k] = is_inside_circle(std::get<0>(stadiums[i]), std::get<0>(used_circles[k]), std::get<1>(used_circles[k]));
    }
    for(int j = 0; j < warehouse_count; j++) {
      for(int k = 0; k < used_circle_count; k++) {
        const bool warehouse_inside_circle = is_inside_circle(std::get<0>(warehouses[j]), std::get<0>(used_circles[k]), std::get<1>(used_circles[k]));

        if (stadium_inside_circle[k] != warehouse_inside_circle) {
          profits[j][i] -= 1;
        }
      }
    }
  }

  // Set the objective function
  for(int i = 0; i < warehouse_count; i++) {
    for(int j = 0; j < stadium_count; j++) {
      const int idx = get_variable_idx(i,j);
      lp.set_c(idx, -profits[i][j]);
    }
  }

  Solution solution = CGAL::solve_linear_program(lp, ET());

  if (solution.is_infeasible()) {
    std::cout << "RIOT!" << std::endl;
  } else {
    std::cout << round_down(-solution.objective_value()/100) << std::endl;
  }
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
  return 0;
}
