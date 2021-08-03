# Tiles - solution
Can the pattern be filed with dominoes (2:1 shaped rectangles)? Problem with very simple description and also quite simple solution. Actually I present 2 solutions, that are both viable.
- Maximum matching
- Maximum flow
- Simple optimization/check

## Maximum matching
All we need to do is create a graph with vertex for each empty (`.`) or blocked (`x`) position. Then we create an edge between all vertically and horizontally adjacent empty positions. On this graph we then call  `boost::edmonds_maximum_cardinality_matching` and check if we get the expected number of pairs (empty/2).

## Maximum flow
An alternative approach is to model this problem as a flow problem. It is useful to bring the idea/concept/picture of a chess board where each tile is either black or white. Despite the layout being a different shape we can still this idea here. We make the black tiles connected to the source and white tiles connected to the target/sink. The resulting flow from calling `boost::push_relabel_max_flow` should then be equal to half of the empty places.

## Simple optimization/check
Both `boost::edmonds_maximum_cardinality_matching` and `boost::push_relabel_max_flow` have generally worse than liner running time complexity. If we first count the number of empty positions and it is not even we know for sure the given layout cannot tiled and we can skip the call to the respective algorithm.

# Running time - maximum matching
    Test set 1 (40 pts / 0.200 s) - 0.0s
    Test set 2 (30 pts / 0.200 s) - 0.005s
    Test set 3 (20 pts / 0.200 s) - 0.022s
    Test set 4 (10 pts / 0.200 s) - 0.003s
    
# Running time - maximum flow
    Test set 1 (40 pts / 0.200 s) - 0.001s
    Test set 2 (30 pts / 0.200 s) - 0.013s
    Test set 3 (20 pts / 0.200 s) - 0.052s
    Test set 4 (10 pts / 0.200 s) - 0.005s
