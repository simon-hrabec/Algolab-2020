#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using IT = int64_t;
using ET = CGAL::Gmpz;

using Program = CGAL::Quadratic_program<IT>;
using Solution = CGAL::Quadratic_program_solution<ET>;

// ------ chose one depending on the problem formulation - <= or >= -----------
// parameters: type, use finite lower bound, lower bound, use finite upper bound, upper bound
Program lp(CGAL::SMALLER, false, 0, false, 0);
Program lp(CGAL::LARGER, false, 0, false, 0);
// ----------------------------------

// ---------- The following represents the example linear program ------------
// Minimize 13A - 14B + 15C
// 4A + 5B + 6C <= 11
// 7A + 8B + 9C <= 22
// B >= -7
// C <= 15

// objective function
lp.set_c(0, 13);
lp.set_c(1, -14);
lp.set_c(2, 15);

// innequalities
lp.set_a(0, 0, 4);
lp.set_a(1, 0, 5);
lp.set_a(2, 0, 6);
lp.set_b(0, 11);

lp.set_a(0, 1, 7);
lp.set_a(1, 1, 8);
lp.set_a(2, 1, 9);
lp.set_b(1, 22);

// separate lower/upper bounds on individual variables
lp.set_l(1, true, -7);
lp.set_u(2, true, 15);

// --------- Chose by default -------------
Solution s = CGAL::solve_linear_program(lp, ET());
// --------- Chose if the previous is not working  -------------
CGAL::Quadratic_program_options options;
options.set_pricing_strategy(CGAL::QP_BLAND);
Solution s = CGAL::solve_linear_program(lp, ET(), options);
// -------------------------

std::cout << s << std::endl;

if (s.is_infeasible()) {
	// given equations cannot be satisfied
} else if (s.is_unbounded()) {
	// arbitrarily good solution exist
} else { // s.is_optimal()
	// just one optimal solution exist
	std::cout << s.objective_value() << std::endl;
}
