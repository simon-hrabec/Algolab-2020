# Idéfix - solution
Idéfix is truly a fun problem to solve. It has moderately difficult description, it contains geometry, requires use of multiple data structures and is not tricky in terms of coding. Moreover the solution is somehow straightforward. The problem is somehow similar to "Hand" from week 11.
- Input format
- Problem classification
- Q1 - Maximum reachable bones
- Q2 - Smallest possible radius
- Implementation notes

## Input format
An important thing to notice is that the problem description talks about radius but we are given **s=4\*r^2**, which is much more convenient. Calculating distance between 2 points requires square root, but s in the given form allows us to always work with squared distances. Since both x and y coordinates are integers the squared distance will also be an integer.

## Problem classification
The problem talks about points (trees) and their surroundings (discs) and bones and their distance to the trees. This is quite straightforward call to use `CGAL::Delaunay_triangulation_2` which allows us to find the closest point (tree) to any random point (bone). It also gives us the triangulation edges that we can use together with union-find.

## Q1 - Maximum reachable bones
The first questions we are tasked to answer is if we join the are of the disc (determined by the points and r or s) how many bones will contain the segment with the most bones. In this case we are told s (4\*r^2) and the k (number of bones) is unknown. It sounds logical to join the trees into groups that create connected area (continuous shadow) and then iterate over the bones and check if the bone falls into any of the segments and if so count the occurrences and then return the maximum.

To get the continuous segments we can use a union-find data structure (`boost::disjoint_sets_with_storage<>`) and iterate over all edges from the delunay triangulation and join the segments if the two points are sufficiently close. Then we set up counters for each segment and iterate over the bones and using `CGAL::Delaunay_triangulation_2::nearest_vertex` we get a vertex that falls into some segment and if is sufficiently close we increment the counter. The maximum of these counters is the answer we are looking for

## Q2 - Smallest possible radius
Now we know the number of bones k but we need to find s instead. For this case we are going to use union-find again. It sounds logical to take the edges and sort them, then iterate over them and join the segments until we have enough bones and return the (squared) length of the last edge required. However the catch here is that we have no way to how many bones currently are in the segments. Also, extending the radius just to include an additional bone can be enough to reach k. This asks to somehow include bones in the union-find merging process. The idea is to create and edge for each bone to its closest tree. This poses a slight issue that we now have 2 types of edges that we have to treat differently, but on the other hand we can sort them the same way just by the distance. After that we process the edges and do the following depending on the type:
- Edge between 2 trees - If the 2 trees belong to 2 different segments then join the segments and add their bone count. If the sum reaches K return the length of the current edge
- Edge from a bone to a tree - Increment the bone count of the target segment by 1. If the count reaches K return the length of the edge (squared distance from the bone to its closes tree).

## Implementation notes
The triangulation need to use vertices with indices  `CGAL::Triangulation_vertex_base_with_info_2<std::size_t,EPIC_KERNEL>` to be able to reference them when iterating over the triangulation edges or when iterating over bones and checking the closest trees.

# Running time
    Test set 1 (20 pts / 1 s) - 0.016s
    Test set 2 (20 pts / 1 s) - 0.086s
    Test set 3 (20 pts / 1 s) - 0.027s
    Test set 4 (20 pts / 1 s) - 0.262s
