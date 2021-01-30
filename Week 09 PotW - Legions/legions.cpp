#include <iostream>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using IT = int;
using ET = CGAL::Gmpz;
using Program = CGAL::Quadratic_program<IT>;
using Solution = CGAL::Quadratic_program_solution<ET>;

template <typename T>
int64_t round_down(const T &input_val)
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
  const auto x = load<int>();
  const auto y = load<int>();
  const auto nr_legions = load<int>();

  Program lp(CGAL::SMALLER, false, 0, false, 0);

  for(int i = 0; i < nr_legions; i++) {
    const auto a = load<int64_t>();
    const auto b = load<int64_t>();
    const auto c = load<int>();
    const auto speed = load<int>();

    const int norm = std::sqrt(a*a + b*b);
    const bool is_negative = x*a + y*b + c < 0;
    if (is_negative) {
      lp.set_a(0, i, a);
      lp.set_a(1, i, b);
      lp.set_b(i, -c);
    } else {
      lp.set_a(0, i, -a);
      lp.set_a(1, i, -b);
      lp.set_b(i, c);
    }
    lp.set_a(2, i, norm*speed);
  }

  lp.set_l(2, true, 0);
  lp.set_c(2, -1);

  Solution s = CGAL::solve_linear_program(lp, ET());

  std::cout << round_down(-s.objective_value()) << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T;
  std::cin >> T;
  while(T--) {
    solve();
  }
}
