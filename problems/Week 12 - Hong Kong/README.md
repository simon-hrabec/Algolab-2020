# Hong Kong - solution
The problem is quite similar to the H1N1 problem. Many ideas can be utilized here as well as code. Hong Kong is somehow an upgraded version. In H1N1 we have a circle to move out and points we need to avoid. In here the points are open discs (the inner area of a circle without the circle itself). And besides leaving the area of the convex hull (i.e. getting to a place where we can go as further as possible) here it is possible to finish between the discs given sufficiently large distance. Moreover, here we need to store the squared distances (to avoid square root operations) that do not fit into 64bits. The explanation of the solution is split into the following chapters:
- Voronoi diagram and Delaunay triangulation
- Preprocessing
- Working with squared values
- Edge lengths and circle radii
- Applying Dijkstra

## Voronoi diagram and Delaunay triangulation
In the lecture regarding proximity structures we were shown the motion planning problem (and teased with statement that we are, indeed, going to solve these problems) and told to use (somehow ^^) Delaunay triangulation, which is the dual of Voronoi diagram. The basic idea is to move using the edges of the Voronoi diagram, as these lines try to be as far from the points as possible. The questions is how do we get the Voronoi diagram to use it? Since it is the dual of the Delaunay triangulation we actually dont need it. We can think in triangles (faces) and move along the edges of the Voronoi diagram as going to neighboring triangles. In this case it is simple to check if it is possible to move from triangle to another - the bottleneck is the common edge connecting the two triangles.

## Preprocessing
The definition of the problem allows as to formulate the problem in a way that we do some preprocessing for the given trees and for each balloon we do a rather simple query. We are able for every triangle to calculate what is the biggest possible balloon that is still able to leave (i.e. leave the convex hull and reach and infinite face in the triangulation or reach a triangle which inscribed circle is big enough for the clearance). Having this information we will be able to first check if the closes tree is far enough and then locate to which triangle the point belongs (`CGAL::Delaunay_triangulation_2::locate`). Then we just compare the size of the balloon and the stored, preprocessed value.

## Edge lengths and circle radii
Unlike in the H1N1 problem we have 2 inputs - the tree radius and the balloon radius. The previously delineated idea requires calculation maximal possible value - in this case, we work with Euclidian distances, which require the square root operation. As a common technique to avoid using the SQRT kernel or rounding errors (and still the slow SQRT function) we can work only with the squared values - the only thing we gonna do with them is comparisons. The only issue is that since the input coordinates can require at least 52 bits the squared values of the distances might not fit into any primitive type (requiring more than 64 bits). Hence, `CGAL::Gmpz` is required to use (actually we could just two 64bit integers to store the result which would be definitely faster).
The values we are interested in this problem are the lengths of the edges between two triangles and the required distance for clearance. If we have trees with radius R1 and a ball with radius R2 than passing with the balloon between two trees (crossing the edge between two triangles) is possible if the edge has length at least 2\*(R1+R2) or 4\*(R1+R2)^2 if we operate in the realm of squared values. For clearance we need the balloon to sufficiently far from all the trees. The distance between the centers of the discs of both the balloon and all the trees needs to be at least 2\*(R1+R2), which is, not so coincidentally, the same value. We get this distance as the radius of the inscribed circle of the triangle.

## Applying Dijkstra
Here it is useful to apply a variation (if possible to name it like that) of Dijkstra algorithm. We take a priority queue (max elements first) and fill it with entries - for each triangle we insert its identifier (in my case I use face handles) and the size of the inscribed circle (squared). Infinite faces (faces outside of the convex hull of the points) have some sufficiently large value (pseudo infinity). We then process elements from the queue. The first element for each face is the best achievable value (hence we can ignore all subsequent entries for that face). When taking an entry from the queue besides assigning the value to the face we also expand it - we put into the queue the neighboring faces with values that's equal to minimum of the maximum achievable value and respective edge length.

## Implementation details
It is important to properly condition when to add things to the priority queue. Especially adding `neighbor->info() != 0` can lead to 2x speedup.

# Running time
    Test set 1 (30 pts / 2 s) - 1.095s
    Test set 2 (30 pts / 2 s) - 0.459s
    Test set 3 (20 pts / 2 s) - 0.81s
    Test set 4 (20 pts / 2 s) - 1.059s
