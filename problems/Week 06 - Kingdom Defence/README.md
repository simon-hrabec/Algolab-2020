# Kingdom Defence - solution
This problem is purely graph problem. More than programming it tests the understanding of the graph problem transformation in the second BGL tutorial.
- Flow approach

## Flow approach
We are going to solve the problem using the maximum flow algorithm. But for this to be a viable option we first need to do few modifications to the graph.

## City requirements
For each city we are given its starting soldier count and required count at the end. The difference between these 2 is the demand. It can be both positive and negative (or 0).

## Edge requirements
We cannot directly express flow requirements on edges. To express this we add the minimum demand to the source vertex and substract the demand from the target vertex. We create the edge with capacity that is the difference between the demand and maximum given capacity.

## Calculating flow
After modifying the graph we can now iterate over all cities/vertices. If the demand is positive create an edge to the sink. If it is negative create and edge to the source with negated value (so the capacity is positive). We also remember the sum of all outgoing edges (their capacities) to the sink. The resulting flow in the network should be equal to it.

# Running time
    Test set 1 (20 pts / 5 s) - 0.547s
    Test set 2 (20 pts / 5 s) - 0.396s
    Test set 3 (20 pts / 5 s) - 0.494s
    Test set 3 (20 pts / 5 s) - 0.883s
