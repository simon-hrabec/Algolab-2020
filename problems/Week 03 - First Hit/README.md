# First Hit - solution
This problem is a slight modification of the *Hit* problem (read it first as this explanation omits things already stated in *Hit*). Instead of stating whether the ray hits any obstacles we are asked to provide the point of first collision. The solution to this problem is not fundamentally different, however few new insights are required. The main idea is to iterate over all obstacles and as we detect a collision shorten the ray (to a line segment) and proceed further. At the end we get the shortest segment limited by the earliest collision.

a toy problem serving as an introduction to CGAL and geometry. We need to find out if a ray collides with any of the given line segments. The solution is straightforward, it is only necessary to take care of few details:
 - Kernel
 - Segments collisions
 - Worst case avoidance

## Kernel
We again need to decide whether to use  `Exact_predicates_inexact_constructions_kernel` or `Exact_predicates_exact_constructions_kernel`. In this case we are creating new line segments and we are then asked to provide point of intersection (rather then yes or no), therefore `Exact_predicates_exact_constructions_kernel` is the kernel of choice.

## Segments collisions
It is simpler (and cheaper) to look for collision of two segments. Hence I find the first collision of the ray and a segment and then proceed with checking of collision of 2 segments. No need to check for the distance of the point from the ray start etc.

## Worst case avoidance
Implementing the solution given the information above will not be sufficient to get the full points. Good idea here is to think about what is going on and if there is a worst case that could be hindering our computation. It is cheaper to check if there is an intersection (predicate) rather than constructing the intersection point (construct). The worst case is if all segments are in the ray and are ordered from the furthers to the closest. In this case we have to update our line segment N times. In this case we can reach out to data randomization to avoid the worst case (on average, all of this is probabilistic). The expected number of collisions in randomly sorted segments is O(log n).

# Running time
    Test set 1 (15 pts / 1.000 s) - 0.006s
    Test set 2 (15 pts / 1.000 s) - 0.051s
    Test set 3 (15 pts / 1.000 s) - 0.064s
    Test set 4 (15 pts / 1.000 s) - 0.05s
    Test set 5 (10 pts / 1.000 s) - 0.18s
    Test set 6 (10 pts / 1.000 s) - 0.06s
    Test set 7 (10 pts / 1.000 s) - 0.05s
    Test set 8 (10 pts / 0.200 s) - 0.05s
