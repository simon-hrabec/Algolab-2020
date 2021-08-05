# H1N1 - solution
H1n1 is the sister problem to Hong Kong. Just slightly easier. It requires the same techniques. It is suffices to use just a double (it will fit the squared distances). The problem description shares some paragraphs for that reason.
- H1N1 vs Hong Kong
- Voronoi diagram and Delaunay triangulation
- Preprocessing
- Edge lengths
- Applying Dijkstra
- Implementation details

## H1N1 vs Hong Kong
H1N1 has points (infected individuals) from which we have to keep distance at least d\^2. And given a starting coordinates we have to say if we are able to leave the infected people (i.e. go arbitrarily far, which can also be interpreted as leaving the convex hull of the points). We can view the points as discs and the individual as a point. Or the other way around - it is equivalent. Note that it is not enough to find a place that between the points and sufficiently spacious (unlike in Hong Kong)

## Voronoi diagram and Delaunay triangulation
In the lecture regarding proximity structures we were shown the motion planning problem (and teased with statement that we are, indeed, going to solve these problems) and told to use (somehow ^^) Delaunay triangulation, which is the dual of Voronoi diagram. The basic idea is to move using the edges of the Voronoi diagram, as these lines try to be as far from the points as possible. The questions is how do we get the Voronoi diagram to use it? Since it is the dual of the Delaunay triangulation we actually dont need it. We can think in triangles (faces) and move along the edges of the Voronoi diagram as going to neighboring triangles. In this case it is simple to check if it is possible to move from triangle to another - the bottleneck is the common edge connecting the two triangles.

## Preprocessing
The definition of the problem allows as to formulate the problem in a way that we do some preprocessing for the given points and for each query we do a rather simple lookup. We are able for every triangle to calculate what is the biggest possible distance to maintain from all points while moving out (i.e. leave the convex hull and reach and infinite face in the triangulation). Having this information we will be able to first check if the closest point is far enough and then locate to which triangle the coordinates belong (`CGAL::Delaunay_triangulation_2::locate`). Then we just compare the requested distance and the stored, preprocessed value.

## Edge lengths
The previously delineated idea requires calculation maximal possible value - in this case, we work with Euclidian distances, which require the square root operation. As a common technique to avoid using the SQRT kernel or rounding errors (and still the slow SQRT function) we can work only with the squared values. In this case the coordinates have at most 24 bits. The squared distance hence might have at most 48 bits. Double has mantissa with 52 bits (effectively 53), which is sufficient. The values we are interested in this problem are the lengths of the edges between two triangles. 

## Applying Dijkstra
Here it is useful to apply a variation (if possible to name it like that) of Dijkstra algorithm. We take a priority queue (max elements first) - each entry is represented by the maximum distance that can escape from that face and its identifier (in my case I use face handles). We fill the queue with all the infinite faces - the faces we can use to escape. We can comfortably use `std::numeric_limits<long>::max()`. The first element for each face is the best achievable value (hence we can ignore all subsequent entries for that face). When taking an entry from the queue besides assigning the value to the face we also expand it - we put into the queue the neighboring faces with values that's equal to minimum of the maximum achievable value and respective edge length.

## Implementation details
In this case we can condition adding a thing to the priority queue by checking if `neighbor->info() != 0`. For H1N1 this provide only a small speedup unlike in Hong Kong, where it makes approx. 2x speedup.

# Running time
    Test set 1 (20 pts / 1 s) - 0.004s
    Test set 2 (20 pts / 1 s) - 0.037s
    Test set 3 (20 pts / 1 s) - 0.264s
    Test set 4 (20 pts / 1 s) - 0.435s
    Test set 5 (20 pts / 1 s) - 0.404s
