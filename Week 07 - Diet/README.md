# Diet
The main topic of week 7 was the introduction of dynamic programing and its solving with CGAL. After the toy assignment "What is the Maximum", which was basically about understanding the syntax, the Diet problem is the next problem in the progression, but still an easy and pretty straightforward one.
- Translating the problem to LP
- Minimum and maximum
- Printing/rounding

## Translating the problem to LP
We have nutrient requirements. Then we have price food and besides that the nutrient content for each food. The minimum/maximum will be the right part of the equations (`CGAL::Quadratic_program::set_b`). The price of the food will be component of the objection function  (`CGAL::Quadratic_program::set_c`). And the food contents will be the left part of the equations (`CGAL::Quadratic_program::set_a`).

## Minimum and maximum
The problem requires us to use both minimum and maximum (upper bound and lower bound). Linear programs in CGAL are defined such as `Program lp(CGAL::SMALLER, false, 0, false, 0);`. The SMALLER/BIGGER is part of the linear program instance, not an individual equation. However, there is an easy way to transform an equation to the other type - multiply it (all of its components) by -1.

## Printing/rounding
The solution of the linear program is of a type `CGAL::Quadratic_program_solution<ET>`. To convert it to an integer (the smallest integer bigger than the value) we have to use the rounding function from the lecture (also can be found in code snipets).

# Running time
    Test set 1 (35 pts / 1 s) - 0.001s
    Test set 2 (35 pts / 1 s) - 0.006s
    Test set 3 (30 pts / 1 s) - 0.07s
