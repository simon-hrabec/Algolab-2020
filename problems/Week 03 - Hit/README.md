# Hit - solution
This problem is a toy problem serving as an introduction to CGAL and geometry. We need to find out if a ray collides with any of the given line segments. The solution is straightforward, it is only necessary to take care of few details:
 - Input type (double/int64_t)
 - Geometric constructs
 - Kernel
 - Early termination

## Input type (double/int64_t)
The input x and y coordinates do not fit into 32bit integer (as specified in the problem description), therefore it is necessary to use bigger type. Although the input data (coordinates) are smaller than 2^51 and therefore it fits into `double` type, it should not be used. Since the values are integers it is better to use 64bit integer (`int64_t` or `long` on codeexpert) - it is faster to read.

## Geometric constructs
It is important to understand that the input ray is not a line segment, but it a line bounded from one side (its name is ray, but if you have not taken basic geometry in English you might not realize it is not a line segment). Therefore we take from the CGAL library `Ray_2` and `Segment_2`.

## Kernel
In CGAL we have multiple kernel we can use. The question for this problem is whether to use `Exact_predicates_inexact_constructions_kernel` or `Exact_predicates_exact_constructions_kernel`. We have all the input data as integer coordinates that fit into double (limit for double is 2^53 exclusive and we have limit 2^51 exclusive) and from the rays and line segments we do not create any other constructs. All we do is check for intersection (but not create the intersection point) which is only a predicate. Therefore we can use the cheapest/fastest `Exact_predicates_inexact_constructions_kernel`.

## Early termination
Once we find a hit we can stop looking for another intersection. It wont change our answer. All we need to do is just skip the input.

# Running time
    Test set 1 (40 pts / 1.000 s) - 0.001s
    Test set 2 (20 pts / 1.000 s) - 0.135s
    Test set 3 (30 pts / 1.000 s) - 0.236s
    Test set 4 (10 pts / 0.140 s) - 0.135s
