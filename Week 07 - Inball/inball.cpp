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

void solve(const int line_count, const int dimension_count) {
  const int radius_id = dimension_count;
  Program lp(CGAL::SMALLER, false, 0, false, 0); 

  for(int i = 0; i < line_count; i++) {
    int quad_sum = 0;
    for(int j = 0; j < dimension_count; j++) {
      const int a_val = load<int>();
      quad_sum += a_val * a_val;
      lp.set_a(j, i, a_val);
    }
    const int sqrt_quad_sum = std::sqrt(quad_sum);
    lp.set_a(radius_id, i, sqrt_quad_sum);

    const int b_val = load<int>();
    lp.set_b(i, b_val);
  }

  lp.set_l(radius_id, true, 0);
  lp.set_c(radius_id, -1);

  Solution s = CGAL::solve_linear_program(lp, ET());

  if (s.is_unbounded()) {
    std::cout << "inf" << std::endl;  
  } else if (s.is_infeasible()) {
    std::cout << "none" << std::endl;  
  } else {
    std::cout << round_down(-s.objective_value()) << std::endl;
  }
}

int main() {
  while(true) {
    const int n = load<int>();
    if (n == 0) {
      return 0;
    }
    const int d = load<int>();
    solve(n, d);
  }
}
