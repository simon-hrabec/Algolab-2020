#include <iostream>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using IT = int;
using ET = CGAL::Gmpz;
using Program = CGAL::Quadratic_program<IT>;
using Solution = CGAL::Quadratic_program_solution<ET>;

int64_t round_down(const CGAL::Quotient<ET> &input_val) {
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

void solve(const int nutrient_count, const int food_count) {
  Program lp(CGAL::SMALLER, false, 0, false, 0); 
  
  for(int i = 0; i < nutrient_count; i++) {
    const int min = load<int>();
    const int max = load<int>();

    lp.set_b(2*i, -min);
    lp.set_b(2*i+1, max);
  }
  
  for(int i = 0; i < food_count; i++) {
    const int price = load<int>();;

    lp.set_c(i, price);
    lp.set_l(i, true, 0);

    for(int j = 0; j < nutrient_count; j++) {
      const int content = load<int>();;
      
      lp.set_a(i, 2*j, -content);
      lp.set_a(i, 2*j+1, content);
    }
  }

  Solution s = CGAL::solve_linear_program(lp, ET());
  if (s.is_infeasible()) {
    std::cout << "No such diet." << std::endl;
  } else {
    std::cout << round_down(s.objective_value()) << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  while (true) {
    const int nutrient_count = load<int>();
    const int food_count = load<int>();
    if (nutrient_count == 0 && food_count == 0) {
      break;
    }
    solve(nutrient_count, food_count);
  }
}
