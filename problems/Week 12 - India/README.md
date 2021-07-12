# India - solution
The problem describes a graph problem (cities as vertices and elephants as edges). Moreover it talk about number of elephants and their cost which is basically a capacity and cost. Therefore it is natural to expect a max flow min cost will solve this problem... and it does... somehow. However, the question asked is not how many suitcases can we transport or given N suitcases what is the price. It goes backwards - given a budget how many suitcases can we transport.
We can always "try send" N suitcases by connecting the starting vertex to source by edge with capacity N and cost 0 and calling the max-flow-min-cost algorithm. Sending more suitcases always result in higher price therefore we can perform binary search on the price by doing a binary search on capacity N. More details include:

- Graph construction
- Binary search
- Small tweaks

## Graph construction
The original graph can be used. Connection with N elephants and cost C translate to edge with capacity N and cost C. The only additional thing is 1 other edge to limit the total flow/capacity. It can be added before starting city or after the finish city.

## Binary search

If the cost is high than the budget we can discard this solution and all above (more suitcases). Otherwise we found a potential candidate solution and we discard all solutions below (fewer suitcases).

## Small tweaks
We can count the capacity of outgoing edges from the starting city and the capacity of incoming edges to the finish city. Their minimum is the upper bound for the solution and `high` can be set to it.
The bottleneck of the network/graph can also be elsewhere. Therefore when we get `flow < mid` we cap `high` by `flow`. Both of these small optimizations can reduce the number of iterations needed for the binary search to terminate.

# Running time
    Test set 1 (25 pts / 4 s) - 0.143s
    Test set 2 (25 pts / 4 s) - 0.369s
    Test set 3 (25 pts / 4 s) - 0.214s
    Test set 4 (25 pts / 4 s) - 0.327s
