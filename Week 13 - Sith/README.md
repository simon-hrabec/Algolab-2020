# Sith - solution
This problem might look complicated at first but it falls into the category of problems that can be easily solved by binary search and verification rather than crafting the optimal solution. The shown solution includes the following steps/techniques:

- Binary search
- Delaunay triangulation for graph construction
- BFS (or DFS) to find connected component on a graph
- Avoiding SQRT by comparing squares

## Binary search
The main idea in this problem is to use binary search on the value K. In each step we omit the first K planets/vertices from the solution and look for a connected component in the graph or more specifically C - the size of the biggest connected component. We can make few observations:
1. With increasing K the resulting graph is getting smaller and hence C is decreasing (not necessarily in every step)
2. Given K and calculating C the result for this setting is min(K,C). We are therefore balancing these 2 values.
3. The initial upper bound (the "high" index) can be set to N/2. C cannot be bigger than N-K. This might not seem important as this would save 1 step in the binary search, but but in each verification step we are given graphs with different size, therefore we want to avoid checking for big values. Theoretically this can speed up the whole computation 2x.

The only thing to do is for given K and calculated C specify the update rules for "high" and "low". We have only 3 options:
1. K == C - We found the result/optimal value. Decreasing K would decrease the result (since it is min(C,K)) and increasing K is also of no avail as it could only decrease C.
2. K < C - We can increase K to potentially better result. We can also cap upper bound (for K) to C since making it bigger would give no benefit.
3. K > C - We can decrease K to potentially better result. We also know that K cannot be smaller than C since decreasing K to C would make C to be same or grow, therefore going with K even lower would lead to no gain.

## Delaunay triangulation for graph construction

In this problem we are not given the graph explicitly (edges are not specified), instead we are given only the vertices (their 2D positions) and distance R such that two vertices are connected if their distance is not bigger than R. One approach is to iterate over all pairs of vertices to find all edges, however, this is not necessary since we do not all edges - we are looking for connected components. We can use/construct Delaunay triangulation which is guaranteed to contain the EMST (Euclidean minimum spanning tree) check all potential edges and ignore those with length > R.

## BFS (or DFS) to find connected component on a graph
Having the edges of the graph we can find the biggest connected component by running DFS/BFS and marking visited vertices. Since we are operating with CGAL Triangulation we do not access vertices by integer index but access them via an iterator and vertex_handle. Instead of making bool array we can attach the bool to the vertices using `CGAL::Triangulation_vertex_base_with_info_2<bool, K>`.

## Avoiding SQRT by comparing squares
When checking if potential edges from the Delaunay triangulation do exist (have length smaller than R) we do not need to compute sqrt((x1-x2)^2 + (y1-y2)^2) ?? R. Instead we can use the squares (x1-x2)^2 + (y1-y2)^2 ?? R^2 to avoid the square root which is slow and can lead to rounding errors. Since all input coordinates are integers and are smaller than 2^24 we know the squares are not bigger than 2^48 which still fits into the range of double or 64bit integer.

# Additional ides
The binary search could be altered. Instead of starting in the middle (with potentially big number) we could check for values in the sequence 2, 4, 8, 16, 32... and once we find upper bound process with regular binary search (reducing interval rather than expanding it). If the result is small (e.g. R is small and the biggest connected component in the whole graph has size 3) we could finish quickly. The biggest difference is that checking for small values is cheap whereas checking for large values is expensive and hence if can be avoided it can lead to speedup. This approach can lead to increase in total check but has potential to reduce the overall work.

# Running time
    Test set 1 (25 pts / 2 s) - 0.047s
    Test set 2 (25 pts / 2 s) - 0.143s
    Test set 3 (25 pts / 2 s) - 0.422s
    Test set 4 (25 pts / 2 s) - 1.105s
