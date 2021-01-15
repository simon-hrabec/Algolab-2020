#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

using IT = int;
using ET = CGAL::Gmpz;

using Program = CGAL::Quadratic_program<IT>;
using Solution = CGAL::Quadratic_program_solution<ET>;

using K = CGAL::Exact_predicates_inexact_constructions_kernel;
using Point = K::Point_2;

using Index = std::size_t;
using Vb = CGAL::Triangulation_vertex_base_with_info_2<Index, K>;
using Fb = CGAL::Triangulation_face_base_2<K>;
using Tds = CGAL::Triangulation_data_structure_2<Vb, Fb>;
using Triangulation = CGAL::Delaunay_triangulation_2<K, Tds>;

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

Point loadpoint(){
  int a, b;
  std::cin >> a >> b;
  return Point{a, b};
}

void solve() {
  const auto fee = load<int>();
  const auto q1 = load<int>();
  const auto q2 = load<int>();
  const auto q3 = load<int>();
  const auto agent_count = load<int>();
  const auto gang_count = load<int>();
  
  std::vector<std::pair<Point, Index>> gang_locations(gang_count);
  std::vector<std::tuple<int, int, int>> gangs_leakage(gang_count);
  
  for(int i = 0; i < gang_count; i++){
    gang_locations[i].first = loadpoint();
    gang_locations[i].second = i;
    std::cin >> std::get<0>(gangs_leakage[i]) >> std::get<1>(gangs_leakage[i]) >> std::get<2>(gangs_leakage[i]);
  }
  
  Triangulation t(std::begin(gang_locations), std::end(gang_locations));
  
  Program lp(CGAL::LARGER, true, 0, true, 24);
  lp.set_b(0, q1);
  lp.set_b(1, q2);
  lp.set_b(2, q3);
  
  std::unordered_map<int,int> gang_to_cheapest_agent_wage;
  
  for(int i = 0; i < agent_count; i++){
    const int gang_idx = t.nearest_vertex(loadpoint())->info();
    const int wage = load<int>();
    const auto it = gang_to_cheapest_agent_wage.find(gang_idx);
    if (it == std::end(gang_to_cheapest_agent_wage)) {
      gang_to_cheapest_agent_wage.emplace_hint(it, gang_idx, wage);
    } else {
      it->second = std::min(it->second, wage);
    }
  }
  
  int variable_index = 0;
  for(const auto &[gang_idx, wage] : gang_to_cheapest_agent_wage) {
    const auto [leak1, leak2, leak3] = gangs_leakage[gang_idx];
    lp.set_a(variable_index, 0, leak1);
    lp.set_a(variable_index, 1, leak2);
    lp.set_a(variable_index, 2, leak3);
    
    lp.set_c(variable_index, wage);
    
    variable_index++;
  }
  
  Solution solution = CGAL::solve_linear_program(lp, ET());
  std::cout << "LH"[solution.is_infeasible() || round_down(solution.objective_value() > fee)] << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T;
  std::cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
