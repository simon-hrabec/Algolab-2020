# Antenna - solution
This problem (like all of week 3) is about geometry, CGAL and usage of appropriate geometrical constructs from the library. We have a set of points and want to find an antenna to cover all the points. Moreover, we want the antenna to have the smallest radius possible. In other words, we are looking for the smallest circle to include all the given points. Luckily for us, there is exactly the CGAL library has `Min_circle_2` which is exactly what we need. We just construct this circle with all the points. And since we are asked to print the minimal radius (rounded up to the next integer) and not the squared radius (which is an integer given integer coordinates) we need to use the `Exact_predicates_exact_constructions_kernel_with_sqrt` Kernel. This of course works, we submit it and get TLE for some test cases. 
- Use of multiple kernels
- Input order randomization
- Implementation notes

## Use of multiple kernels
Since the straightforward approach is too slow we need to do better (somehow - it is good to know you need to do better and not knowing how ^^). After reading the CGAL docs (or rewatching the tutorial or just checking the slides) you can notice there is something as *support set* or  *support points* - set of maximum 3 points that define the circle. We can find these 3 points using the `Exact_predicates_inexact_constructions_kernel` kernel and then create the circle from these at most 3 points using the `Exact_predicates_exact_constructions_kernel_with_sqrt` to get the squared radius to apply `CGAL::sqrt` and then do the conversion to integer (rounded up/down) using the iterative function given from the lecture (so far as I understand this is the only way to convert fractional types to the nearest smaller/bigger integer aka round up/down).

## Input order randomization
The `Min_circle_2` underlying algorithm is sensitive to the input data. Hence, it offers an option to randomize the order in which the input points are processed. If turned on the code runs faster (test case 5), but with proper implementation the solution passes even without it.

## Implementation notes
I construct the `CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt::Circle_2` in the solution code directly. This requires to have the check for 1 points (which is allowed input, but, as often happens, is not checked in the test cases). Otherwise we can just create the circle via the `Min_circle_2` for convenience:

    const SQRT_Min_circle sqrt_mc(std::begin(sqrt_points), std::end(sqrt_points), true);
    const SQRT_Traits::Circle sqrt_c = sqrt_mc.circle();

The direct construction is, of course, faster (by astonishing 9ms across all test cases).

# Running time
    Test set 1 (10 pts / 1 s) - 0.002s
    Test set 2 (10 pts / 1 s) - 0.002s
    Test set 3 (20 pts / 1 s) - 0.005s
    Test set 4 (20 pts / 1 s) - 0.095s
    Test set 5 (10 pts / 1 s) - 0.19s
    Test set 6 (10 pts / 1 s) - 0.0s
    Test set 7 (10 pts / 1 s) - 0.239s
    Test set 8 (10 pts / 1 s) - 0.24s
