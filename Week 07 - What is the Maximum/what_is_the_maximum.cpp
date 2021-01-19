#include <iostream>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using IT = int;
using ET = CGAL::Gmpz;
using Program = CGAL::Quadratic_program<IT>;
using Solution = CGAL::Quadratic_program_solution<ET>;

int64_t round_up(const CGAL::Quotient<ET> &input_val) {
  double num = std::ceil(CGAL::to_double(input_val));
  
  while (num > input_val) num -= 1;
  while (num < input_val) num += 1;
  return static_cast<int64_t>(num);
}

template<typename T>
T load() {
  T val;
  std::cin >> val;
  return val;
}

const int X = 0;
const int Y = 1;
const int Z = 2;

void constraint(Program & lp, const int i, const int x, const int y, const int val) {
  lp.set_a(X, i, x);
  lp.set_a(Y, i, y);
  lp.set_b(i, val);
}

void constraint(Program & lp, const int i, const int x, const int y, const int z, const int val) {
  lp.set_a(X, i, x);
  lp.set_a(Y, i, y);
  lp.set_a(Z, i, z);
  lp.set_b(i, val);
}

int main() {
  std::ios::sync_with_stdio(false);
  while(true) {
    const int problem_type = load<int>();
    if (problem_type == 0) {
      return 0;
    }
    const int a = load<int>();
    const int b = load<int>();
    
    Program lp(CGAL::SMALLER, false, 0, false, 0); 
    if (problem_type == 1) {
      lp.set_l(X, true, 0);
      lp.set_l(Y, true, 0);
      constraint(lp, 0, 1, 1, 4);
      constraint(lp, 1, 4, 2, a*b);
      constraint(lp, 2, -1, 1, 1);
      lp.set_c(X, a);
      lp.set_c(Y, -b);
    } else {
      lp.set_u(X, true, 0);
      lp.set_u(Y, true, 0);
      lp.set_u(Z, true, 0);
      constraint(lp, 0, -1, -1, 0, 4);
      constraint(lp, 1, -4, -2, -1, a*b);
      constraint(lp, 2, 1, -1, 0, 1);
      lp.set_c(X, a);
      lp.set_c(Y, b);
      lp.set_c(Z, 1);
    }
    
    Solution s = CGAL::solve_linear_program(lp, ET());
    if (s.is_unbounded()) {
      std::cout << "unbounded" << std::endl;
    } else if (s.is_infeasible()) {
      std::cout << "no" << std::endl;
    } else {
      const auto val = (problem_type == 1) ? -round_up(s.objective_value()) : round_up(s.objective_value());
      std::cout << val << std::endl;
    }
  }
}
