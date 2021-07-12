# Car Sharing - solution
This problem does not have an obvious solution. First, looking at the input constraints we can notice that there is at most 10 stations, at most 100 cars for each station and at most 10K requests and the time (departure/arrival) is also limited to 100K. Some of these numbers are really small and they are also no huge collectivelly (their product fits into 64 bits).

When considering tehcniques to use the first one to come to mind is DP. However it does not seem to be possible to find any subproblem relation. Since we have nodes and edges (car usage) we could think about this problem in terms of a graph and try some flow solution. However we first need to do one of the tricks mentioned in previous problems - modify the graph. Here we have only 10 stations (which is a red/green flag). Probably we should take nodes not only as station but as station combined with time. Then we can consider unit flows as individual cars and have the payment as a cost.

Explanation structure:
- Constructing the graph
- Implemenation and optimizations
- Avoiding negative costs

## Constructing the graph
For each of the S stations we create nodes that correspond to points in tome (0 to 100000) and create an edges connecting these points. Also we create a source node and connect it to the 0 nodes and sink node which and connect all last nodes for each station to it. Then we take all the request and create edges for them as well. However, we need to think about the capacity and the price. The capacity for the default edges can be artibrarily large (pseudo infinity) and for the request edge 1. The price is a bit tricky to figure out. In this case we are going to use the max-flow-min-cost algorithm. We can set the price for the deafult edge 0 and negative for the request edges. Then we get a negative total cost which we only negative to get the result.

## Implemenation and optimizations
Looking at the constraints we can notice that we have at most 10K requests but we have 100K time points for each station. It seems that most of them could be omitted. There is few approaches to do this. Easy way is to first remember what time points are used for each station (e.g. using std::map/set for each station) and then just make the default edges between those nodes.

## Avoiding negative costs
As in the previous problems the key to solving some of the max-flow-min-cost is to find a way how to not operate with negative edges. With negative edges we are basically maximizing the cost, not minizing it. An idea to follow is to add some value to all edges to make them all positive and then substract it from the result. Not by accident we are told the payment for each trip is at most 100. Hence each time unit (lets say it is minutes) for one car can make at most 100 money. We make an edge going for N minutes to cost N\*100 in case of default edge and N\*100-payment for request edges. By this, the higher the payment the chaper the edge. Now we can calculate the minimum cost and see how much smaller it is from the total upper bound #cars\*100000\*100. This is our result and we can compute this using the `boost::successive_shortest_path_nonnegative_weights` without the need to call the slower `boost::cycle_canceling`.

# Running time
    Test set 1 (20 pts / 5 s) - 0.064s
    Test set 2 (20 pts / 5 s) - 0.001s
    Test set 3 (20 pts / 5 s) - 0.156s
    Test set 4 (20 pts / 5 s) - 0.653s
    Test set 5 (20 pts / 5 s) - 1.334s
