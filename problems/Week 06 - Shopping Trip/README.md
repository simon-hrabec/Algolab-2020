# Shopping Trip - solution
Shopping Trip is a graph problem - even the problem statement talks explicitly about edges and vertices. It requires very little thinking and even less coding.
- Understanding the problem
- Reduction to a basic graph algorithm

## Understanding the problem
We need to visit all shops and then return back home (to drop off things). It is said we can use the same streets on a single trip and there is no reason to use other streets on the way back. Since we use the same streets we don't need to think about the way back and only consider the way to the stores.

## Reduction to a basic graph algorithm
We want to know if there are exclusive (no edge is shared) paths from source to every store. If we connect all the stores to another vertex (target/sink) and run the maximum flow algorithm we can simply compare the flow to the number of stores to see if the proposition of unique path to each shop is reachable.

# Running time
    Test set 1 (40 pts / 1 s) - 0.0s
    Test set 2 (40 pts / 1 s) - 0.007s
    Test set 3 (20 pts / 1 s) - 0.057s
