# Germs - solution
This problem has rather simple description (unlike other problems). We have N bacteria and each of them die at some point. We are interested to know when the first bacterium dies, when half of them died and when the last bacterium died. We can determine time of death of each bacterium and then find those number (by some kind of sorting/ordering). Each bacterium dies if it either touches the boundary or when it touches another (the closest) bacteria. We don't need to iterate over all edges - we can use Delaunay triangulation as it is guaranteed to contain the smallest edge for each vertex. There are few more notes:
- Determining death time of a bacterium
- Interpreting the distance correctly (SQRT) and these +-1 details...
- Avoid sorting

## Determining death time of a bacterium
As discussed above the death of a bacterium is determined by the minimal distance over distances to borders and the closest cell. Minimum distance implies time of death. Distances to borders can be simply calculated using the X and Y components - `std::abs(left-x)`, `std::abs(right-x)`, `std::abs(top-y)`, and `std::abs(bottom-y)`. On of the neighbors in the triangulation is the closest, so taking the minimum over all distances will suffice - `CGAL::squared_distance(vertex->point(), vertex_c->point()`.

## Interpreting data correctly (SQRT) and these +-1 details
The devil is in the detail. Especially in those small details where you have to add or substract more or less randomly looking 1. We are told that the bacteria have size 1/2 and that it is growing quadratically (its radius, not its area, it would grow quartically. And yes, I had to Google that word). This requires two additional steps.
1. Doing SQRT over the final distance to get the time of growth (life)
2. For the boundary check substract 0.5 (actually if you don't do this the solution will pass as well, since it is missing a testcase checking this ^^) and for the bacteria distance substract 1 and divide it by 2 (since both bacteria are growing towards each other). It is hard to nail this on a first try, therefore it is advisable to write down few test example test cases that will check these +-1 or /2 works correctly - e.g. 2 bacteria with distances 24, 25, 50 and 51.

## Avoid sorting
This might seem counterintuitive - why should I avoid sorting if I need the middle element in the sorted array? One optimization technique is look at the work  being done and think about the work that's not being required. Do I need the first half sorted? Do I need the second half sorted? No. I only need the mid-point. And there happens to be an easier way to find the median - the lazy quicksort aka `nth_element` in C++. It locates the Nth element (given by the ordering in the data) and puts it on Nth place and leave elements smaller to left and bigger to right (but does not sort them). We can use this and then only find the minimum in the bottom half and maximum in the upper half (and to be precise in they are not halves since their size can differ by one and they are still missing the median element. But honestly who cares? Well, if I did not write it here and you would bother enough to write me an email you would have my respect. But now since you are reading it here you wont write the email. But if I did not write it here you would think I did less of me. So I guess I will never know...).

# Running time
    Test set 1 (25 pts / 0.600 s) - 0.002s
    Test set 2 (25 pts / 0.600  s) - 0.052s
    Test set 3 (25 pts / 0.600  s) - 0.191s
    Test set 4 (25 pts / 0.600  s) - 0.169s
