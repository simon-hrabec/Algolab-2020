# Tracking - solution
This problem is easy in implementation and also in the concept of the solution. What is difficult is to come up with the solution or idea. The easiest case is if you already know the required technique. Another way to approach this problem is to look at the constraints. K is guaranteed to be between 1 and 10 (i.e. quite small). We therefore don't need to think about a general algorithm that would solve this problem efficiently for arbitrarily large K.
- Graph layering/duplication
- Reduction to shortest path problem

## Graph layering/duplication
The idea behind this solution is to duplicate that graph and let the nodes convey information about how many rivers has already been visited. For given K we make K+1 layers (copies) of the graph. Nodes at layer i (going from 0 to K) will represent a state where we already took i paths along a river. For each layer i (except the last one) we make the edges that go along a river to point to layer i+1 instead of i (or we create both). Among all the K+1 destination cities we pick the one from the last (K+1th) layer. Going from the starting node we are guaranteed we had to pass all K+1 layers and hence took at least K paths along a river.

## Reduction to shortest path problem
The graph we constructed has a path from the source node to target node and the shortest path is the path we are asked in the problem. We modified the graph and now we can use the standard shortest paths algorithm (given non-negative edges) Dijkstra.

# Running time
    Test set 1 (30 pts / 0.600 s) - 0.002s
    Test set 2 (30 pts / 0.600 s) - 0.019s
    Test set 3 (20 pts / 1.800 s) - 0.37s
    Test set 4 (20 pts / 1.600 s) - 0.374s
