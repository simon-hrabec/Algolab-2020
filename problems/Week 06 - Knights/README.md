# Knights- solution
Knights is a tricky problem. The problem has few edge cases that need to be adequately handled and also the description itself needs to be properly understood:
- Cave graph
- Border intersections - escape paths
- Intersection limit
- Graph duplication/doubling vertices
- Making hallways - connecting the vertices
- Should this edge capacity work?

## Cave graph
The problem talks about intersections and hallways and additionally puts constraints on both. Therefore it is natural to model this problem as a graph problem and make intersection vertices and hallways edges. At the end we will use maximum flow algorithm to compute the result.

## Border intersections - escape paths
We are trying to reach the vertices on the border of the rectangular grid. Important to notice is that the corner vertices have 2 escape paths whereas the other border vertices have only 1.

## Intersection limit
The problem describes the intersection maximum throughput C to be at most 4. If you feel baffled trying to understand how 3 and 4 would differ from 2 and you question your understanding of the problem description - don't worry, you understand it correctly. Values of C above 2 are superfluous and in terms of solution are equivalent to C equal 2.

## Graph duplication/doubling vertices
First and the most fundamental question to ask is how to implement the required imposed by C. Normally we impose maximum capacity on edges, not vertices. For this purpose we need to decompose the vertex into two vertices (lets call them type A and B) and effectively duplicate the graph. The A vertex will have all incoming edges and the B vertex will have outgoing edges. These 2 vertices will be connected by an edge which capacity will be equal to C. By this we effectively achieve a capacity constraint on vertices.

## Making hallways - connecting the vertices
Now the graph gets a bit complicated because we have twice the number of vertices and the questions is how should we connect them. The problem has undirected edges which we also decompose into 2 edges and for each 2 vertices (V1 and V2) being vertically or horizontally adjacent we create this edge pair. One edge will go from V1-B to V2-A and from V2-B to V1-A and both will have capacity 1.

## Should this edge capacity work?
You might notice that the hallway has capacity 1 but now we have 2 edges and 2 knights can take the hallway in opposite direction. However if this would be the case it is equivalent to the solution where they both do not take the edge and then continue in the path of the other knight, hence this should not pose a problem.

# Running time
    Test set 1 (40 pts / 1 s) - 0.116s
    Test set 2 (40 pts / 1 s) - 0.112s
    Test set 3 (20 pts / 1 s) - 0.116s
