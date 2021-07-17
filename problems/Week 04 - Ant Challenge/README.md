# Ant Challenge - solution
Yet another easy problem to solve with a little bit of coding and BGL exploration and combination of few algorithms.
- Specie's networks
- Unified network
- Result
- Implementation notes

##  Species' networks
We are given a graph and a set of species. Each species has its own costs for all the edges. Each species has a network that is a spanning-tree and is not defined explicitly. The description defines it as a minimum spanning-tree if you run the Kruskal algorithm from a specific node (species specific). By this we get the network (subset of the edges) of each species

## Unified network
We are asked to give the best result if the species collaborate - we can merge all the networks together - pick the cheapest edge among all the costs (if the respective network includes the edge). If none network includes the edge we remove it from the graph completely.

## Result
To get the final answer we just run `boost::dijkstra_shortest_paths` on the unified network graph.

## Implementation notes
I use `std::unordered_map<uint64_t, uint32_t>` where the key is merged to and from index. It maps this merged key to an index in the edge array. I need to use this when I iterate over the minimum spanning-tree edges.

# Running time
    Test set 1 (20 pts / 1 s) - 0.007s
    Test set 2 (20 pts / 1 s) - 0.022s
    Test set 3 (20 pts / 1 s) - 0.037s
    Test set 4 (40 pts / 1 s) - 0.116s
