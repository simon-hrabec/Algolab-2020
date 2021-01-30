#include <iostream>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using IT = int;
using ET = CGAL::Gmpz;
using Program = CGAL::Quadratic_program<IT>;
using Solution = CGAL::Quadratic_program_solution<ET>;

int64_t round_down(const CGAL::Quotient<ET> &input_val)
{
  double num = std::floor(CGAL::to_double(input_val));
  while (num > input_val) num -= 1;
  while (num+1 <= input_val) num += 1;
  return static_cast<int64_t>(num);
}

template<typename T>
T load() {
  T val;
  std::cin >> val;
  return val;
}

void solve() {
  const int boat_count = load<int>();
  const int sailor_count = load<int>();
  const int pair_count = load<int>();

  Program lp(CGAL::SMALLER, false, 0, false, 0);
  const int sailor_offset = boat_count;

  for(int i = 0; i < pair_count; i++) {
    const int from_boat = load<int>();
    const int to_sailor = load<int>();
    const int factor = load<int>();

    const int boat_equation = from_boat;
    const int sailor_equation = to_sailor + sailor_offset;

    lp.set_a(i, boat_equation, 1);
    lp.set_a(i, sailor_equation, 1);
    lp.set_c(i, -factor);
  }

  for(int i = 0; i < boat_count; i++) {
    lp.set_b(i, 1);
  }

  for(int i = 0; i < sailor_count; i++) {
    lp.set_b(i+sailor_offset, 1);
  }

  for(int i = 0; i < pair_count; i++) {
    lp.set_l(i, true, 0);
    lp.set_u(i, true, 1);
  }

  Solution s = CGAL::solve_linear_program(lp, ET());
  std::cout << round_down(-s.objective_value()) << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
}
