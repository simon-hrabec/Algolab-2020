# Return of the Jedi - solution
It is quite easy to spot that this warp network that is discussed in the description is a minimum spanning tree. And what we are asked to compute is the price of the second cheapest (possibly the same price) spanning tree. The solution is written in the following chapters:
- Calculating the MST
- Which edge to add and remove
- Calculating the max edges

## Calculating the MST
We are asked to calculate the price of the 2nd best MST. A good place to start is to actually calculate the MST and work it out from there. To get the MST, more specifically the edges that create it, we can just use the boost algorithm `kruskal_minimum_spanning_tree`.

## Which edge to add and remove
The solution for our problem can be achieved by removing one edge from the MST and adding another, different edge so that the cost of the spanning tree grows by a smallest possible value (and so that it is still a spanning tree). We can look at all the edges that are not in the spanning tree and see what is the difference between this edge and the longest edges between the two vertices (defined by the edge) using the edges of the MST.

## Calculating the max edges
This ide is pretty simple, however, we dont know what is the longest edge on the MST between any two vertices. The main part of the solution is implementing this. We can use simple DFS. We use it N times, starting at each vertex. We as we go deeper we remember the longest edge visited on that path from the starting vertex and set it into our table (for the pair starting vertex, current vertex).

## The final result
We iterate over all the edges that are not part of the MST. For each such edge we check what is the difference between the price of thius edge and the longest edge on the path between those vertices using the edges of the MST. Note that this number is guaranteed to be positive, otherwise this edge would have to be part of the MST. We take the smallest difference and add it to the price of MST, which is the desired result.

## Alternative approach
If you find the approach mentioned above a bit too complicated you can chose an alternative approach (thanks to [SeboCode](https://github.com/SeboCode/ETHZ-AlgoLab-2020) who told me about this). You can just compute the MST and then calculate additional N-1 MSTs - for each you ignore one edge of the original MST. You then use the smallest cost among the restricted MSTs. This is not only concepltually simple, but also quite simple to code and it also runs surprisingly fast.

# Running time
    Test set 1 (40 pts / 2 s) - 0.012s
    Test set 2 (40 pts / 2 s) - 0.814s
    Test set 3 (20 pts / 2 s) - 1.405s
