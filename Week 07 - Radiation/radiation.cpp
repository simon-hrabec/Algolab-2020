#include <iostream>
#include <vector>
#include <array>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using IT = CGAL::Gmpz;
using ET = CGAL::Gmpz;
using Program = CGAL::Quadratic_program<IT>;
using Solution = CGAL::Quadratic_program_solution<ET>;

template<typename T>
T load() {
  T val;
  std::cin >> val;
  return val;
}

std::array<std::array<int, 3>, 50> cells;
std::array<std::array<std::array<CGAL::Gmpz, 3>, 31>, 50> powers;

void solve() {
  const int healthy_count = load<int>();
  const int tumor_count = load<int>();
  const int cells_total = healthy_count + tumor_count;

  for(int i = 0; i < cells_total; i++) {
    std::cin >> cells[i][0];
    std::cin >> cells[i][1];
    std::cin >> cells[i][2];
  }

  int solution = -1;
  CGAL::Quadratic_program_options options;
  options.set_pricing_strategy(CGAL::QP_BLAND);
  Program lp(CGAL::SMALLER, false, 0, false, 0);
  lp.set_l(0, true, 0);
  lp.set_c(0, -1);

  for(int degree = 0; degree <= 30; degree++) {
    for(int i = 0; i < cells_total; i++) {
      const int coef = (i < healthy_count) ? 1 : -1;
      const int x = cells[i][0];
      const int y = cells[i][1];
      const int z = cells[i][2];
      if (degree == 0) {
        powers[i][0][0] = 1;
        powers[i][0][1] = 1;
        powers[i][0][2] = 1;
      } else {
        powers[i][degree][0] = powers[i][degree-1][0] * x;
        powers[i][degree][1] = powers[i][degree-1][1] * y;
        powers[i][degree][2] = powers[i][degree-1][2] * z;
      }

      int param_id = 1;
      for(int a = 0; a <= degree; a++) {
        for(int b = 0; b <= degree-a; b++) {
          for(int c = 0; c <= degree-b-a; c++) {
            lp.set_a(param_id++, i, coef * powers[i][a][0] * powers[i][b][1] * powers[i][c][2]);
          }
        }
      }
      lp.set_a(0, i, 1);
    }

    Solution s = CGAL::solve_linear_program(lp, ET(), options);
    if (s.is_unbounded()) {
      solution = degree;
      break;
    }
  }

  if (solution == -1) {
    std::cout << "Impossible!" << std::endl;
  } else {
    std::cout << solution << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
  return 0;
}
