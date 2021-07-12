# Radiation - solution
After the *Diet* toy problem this is the first problem to really test the understanding of linear programming and how to solve LP problems using the CGAL library. The approach to this problem is suggested in the lecture notes. Here we extend the problem from 2D to 3D. The problem consist of properly setting the equations using CGAL, efficiently computing (caching) the powers, iterating over all the combinations, and trying a degree one by one. Detailed explanation:
- Constructing the equations
- Why binary search is a bad idea
- Caching the powers
- Interpreting the result
- Possible improvements/ideas

## Constructing the equations
For each cell we create an equation that needs to be satisfied. The terms of equations are all possible combinations of products of the coordinates so that each term is product of at most N (denoting the degree) coordinates. 3 nested for loops are an easy way to get all of these.

## Why binary search is a bad idea
We are looking for a degree between 0 and 30 (inclusive) therefore it is natural to consider binary search. If the degree is 30 we would have to check 31 checks for each degree. However this needs to be put under scrutiny if the checks differ in size/time required to perform. In this case the number of variables in the equations grow cubically and moreover we are working with `CGAL::Gmpz` - an infinite precision integer - which is a type that does not provide basic operations such as addition and multiplication in constant time since the numbers stored are represented by multiple (arbitrarily big) or 32bit integers (or 64bit integer or bytes, I am not sure how exactly it is implemented). Therefore it is better (at least for the given test data) to proceed degree by degree starting at 0.

## Caching the powers
To construct the equations we need to have certain powers of the x, y, and z components of the cell locations. Since we are going to reuse all of the calculated powers for degree N in equations for degree N+1 it makes sense to store these values and do not recompute them. It also make sense to calculate these powers on the fly rather than all at once since if a solution degree N exist all N+1th and further powers would not ever be used.

## Interpreting the result
The LP is set to maximize the minimal distance of all the cells from 0 (healthy cells being in negative space, tumor cells positive). If we are given a solution and we multiply it by some number we also increase the minimum distance. Hence we can assume that sufficient degree will yield a solution that is unbounded. Therefore the first degree with unbounded solution is the result we are looking for.
Also, we want to separate the points, having value 0 in a place of a cell (healthy/tumor) is not admissible, but LP not designed to work with strict inequalities, so we need to account for that.

## Possible improvements/ideas
We store only powers of a single x, y, or z components. However we could store also the product of the powers of individual components. Also it seems not necessary to recreate the `CGAL::Quadratic_program<CGAL::Gmpz>` instance since we are always reusing all the previous components from in the equations from the check of a lower degree. Adding the missing terms should be sufficient.
Another idea is to use `double` instead of `CGAL::Gmpz` as the input type, which works for all test cases but I believe it does not work in general and passes only due to lacking test cases (it is quite common that some incorrect things pass because the test cases are not handcrafted to catch all possible minor issues).
# Running time
    Test set easy (20 pts / 2.500 s) - 0.225s
    Test set hard1 (20 pts / 2.500 s) - 1.837s
    Test set hard2 (20 pts / 2.500 s) - 2.202s
    Test set large (20 pts / 2.500 s) - 0.625s
    Test set small (20 pts / 2.500 s) - 0.224s
