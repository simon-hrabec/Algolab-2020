# Bistro - solution
In this problem we are given N points that denote the bistros and then M points (queries) for which we need to give the (squared) distance to the closest point (bistro). If only there was a data structure/algorithm that would allow us to simply obtain this value... Yep, you guess correctly - it is `CGAL::Delaunay_triangulation_2<K>` and its method `nearest_vertex`. And there is also already a function for squared distance of 2 points.

# Running time
    Test set 1 (20 pts / 0.600 s) - 0.026s
    Test set 2 (20 pts / 0.600 s) - 0.162s
    Test set 3 (20 pts / 0.600 s) - 0.141s
    Test set 4 (20 pts / 0.600 s) - 0.215s
    Test set 5 (20 pts / 0.600 s) - 0.46s
