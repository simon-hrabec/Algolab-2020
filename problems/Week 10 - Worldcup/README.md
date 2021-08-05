# Worldcup - solution
This problem has multiple layers and requires quite a lot of coding. Also, the problem description is a bit tricky - you need to also read the input restrictions to get all the information (I often skipped those since I was always solving the full problem).
- Two pointers approach
- Alternative implementation

## Identifying problem type
Well, how do we solve this problem? There are few keys points that tells us how to solve this problem. We are trying to maximize the profit. The profit is composed from various beers delivered to various stadiums. These do not need to be integers. And we also have constraints on the alcohol content delivered to one stadium (which can be combined by multiple beers). This smells quite like linear programming.

## Setting up the equations
Before we start setting up the equations and its coefficients it is important to make clear what will be the variables on the left side. In our case we will have separate variable for each warehouse-stadium pair. This will denote how much beer has been delivered. Then we set up the following equations:
- For each stadium we set up 3 equations. Two will be to make sure the demand equals the supply (two to make effectively make = by <= and >= using the original and negated version of the equation). And the third one will limit the total alcohol volume sold in that given stadium.
- For each warehouse we set up a single equation - the beer delivered from this warehouse cannot go over its maximum supply.

## Determining the profit
We are given the profit data for each warehouse-stadium pair. However we still need to modify these profits by the number of contour lines the path between these two crosses. We have at most 200 warehouses and 20 stadiums. But we might be given up to 1'000'000 contour lines.  We are also told that each line crosses a contour line at most once. This implies that either the line does not touch the contour circle at all, is completely inside it or either of it is inside and the other is outside. We can never have the contour circle between the two. You might expect this to be the full description, but you also need to read the restriction on each testcase. For the last case it is written that there is at most 100 contour lines that have any object inside them. This reduces the number of contour lines to work with (after identifying them) 4 orders of magnitude.

## Choosing the contour lines
We know only a few contour lines have inside any object. We can reach to Delaunay triangulation for help. We construct the triangulation for the union of warehouses and stadiums and then we iterate over all contour lines and we check for the closest point to it. If it is sufficiently close (to be inside the circle) we can use it, otherwise we can discard that contour line.

## Alternative approach
I managed to get faster running time when not using Delaunay triangulation but rather by sorting the circles by one coordinate and then checking only the subset for each stadium/warehouse. I also have one implementation where I use index to an array to get the number of bit of the indexed number. No speedup obtained by using this but it might interesting to check.

# Running time - Delaunay triangulation
    Test set 1 (25 pts / 4 s) - 0.094s
    Test set 2 (25 pts / 4 s) - 0.241s
    Test set 3 (25 pts / 4 s) - 0.257s
    Test set 4 (25 pts / 4 s) - 2.19s
    
# Running time - Sorting + binary search
    Test set 1 (25 pts / 4 s) - 0.095s
    Test set 2 (25 pts / 4 s) - 0.243s
    Test set 3 (25 pts / 4 s) - 0.259s
    Test set 4 (25 pts / 4 s) - 1.59s
    
# Running time - Sorting + binary search + bitmasks
    Test set 1 (25 pts / 4 s) - 0.095s
    Test set 2 (25 pts / 4 s) - 0.243s
    Test set 3 (25 pts / 4 s) - 0.259s
    Test set 4 (25 pts / 4 s) - 1.588s
