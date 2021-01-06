# What is the Maximum - solution
This is the toy/introductory problem for linear programming. All we need to do is understand the CGAL interface for LP, set the equations and then check what is the result (value, unbounded, infeasible).

If the running was a concern in this problem we could avoid reinitializing the `CGAL::Quadratic_program<int>` with all its equations and keep two instances of the linear program and for each test case only change the parts that differ with the input - one right side of an inequality and the objective.

# Running time
    Test set 1 (50 pts / 0.100 s) - 0.0s
    Test set 2 (50 pts / 0.100 s) - 0.0s
