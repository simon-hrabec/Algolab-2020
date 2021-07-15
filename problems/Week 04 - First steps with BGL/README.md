# First steps with BGL
This is a BGL toy problem. It requires no algorithm problem solving, only straightforward usage of BGL. We need to tell the cost of minimum spanning tree and the distance from node 0 to the furthest node. For the first we can call `boost::kruskal_minimum_spanning_tree` and simply iterate over the edges and sum the costs. For the second we run `boost::dijkstra_shortest_paths` - which calculates distance to all nodes - and then just look for the maximum value in the distance map.

# Running time
    graphs_easy (30 pts / 1 s) - 0.0s
    graphs_medium (70 pts / 1 s) - 0.045s
