
# Hiking Maps - solution
Hiking Maps is the last problem of the weekly problem set fully designated to CGAL geometry and its intricacies. It requires a little thought regarding which kernel (EPIC/EPEC) to use and then the combination of 2 subtasks - finding which maps contain which legs and then finding the shortest subsequence of maps that contain all the legs. The explanation of the solution is split into the following chapters:
- Input size
- Simple solution
- 2 pointers
- EPIC kernel without constructions

## Input size
It is important to notice at the beginning the sizes of the input. In this case we have at most 2000 map parts and 2000 points (1999 legs). It is OK to create a 2D flag array and compute for each leg the map parts that contain it. Doing so we get at most 4M entries.

## Simple solution
We are given 6 points that describe a triangle (3 times 2 points that describe a line and 3 lines describe a triangle). We construct the 3 lines and from those we get the 3 intersecting points. From those 3 points we construct the triangle. Then for each leg we ask if it is within the triangle - a leg is defined by 2 points so we check the 2 consecutive points. Knowing which leg is contained in which map parts we can do the 2 pointer scan (see next paragraph) to find the shortest map parts interval that satisfies the criteria (having all legs). For this to work we have to use EPEC kernel. For this problem not to TLE and pass within the time limits we cannot use EPEC and need a different way how to solve this problem ^^.

## 2 pointers approach
We set up an array of counters - each entry indicates how many times respective leg has been included within the interval of the map parts. Then we use another variable to remember how many legs are we missing. Then we take two pointers and if we are missing some legs we extend the interval (by moving the forward pointer) and if we have them all we try shrinking it by moving the backward pointer). We use the shortest interval among all the viable ones (having all legs included).

##  EPIC kernel without constructions
As the triangle solution requires EPEC and we would like to probably use EPIC with faster check without any constructions we need to rethink our approach. First thing to do is to look for things we are computing and we don't need. Creating the triangle requires computing the intersection points. We don't explicitly need those points. An easy way to define if a point is inside a triangle is if the point is on the "correct" side of each line (i.e. being in the semi plane that also contains the 3rd point). Such query is a predicate. 3 lines created out of the 6 points will suffice. All we need to do is make sure we identify the correct sides of the semi planes. When making the lines I use the check for `CGAL::right_turn` to swap the points and `CGAL::Line_2::has_on_negative_side` to determine whether the point is inside the half-plane. Note that the usage of `CGAL::left_turn` and `CGAL::Line_2::has_on_positive_side` is equivalent.

# Running time
    Test set 1 (20 pts / 0.400 s) - 0.083s
    Test set 2 (20 pts / 0.400 s) - 0.088s
    Test set 3 (20 pts / 0.400 s) - 0.174s
    Test set 4 (20 pts / 0.400 s) - 0.355s
    Test set 5 (20 pts / 0.400 s) - 0.226s
