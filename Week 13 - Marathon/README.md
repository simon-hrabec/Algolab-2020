# Marathon - solution
This problem is clearly a graph problem. It can be solved by max flow min cost algorithms in some way. The shown solution includes the following steps/techniques:

- Dijkstra call to find the shortest path
- Construction of the flow graph
- Calling max-flow-min-cost
- Binary search

## Dijkstra call to find the shortest path
From the problem description we know the marathon runners will take the shortest (one of it) path from start to finish, therefore a good start is to find the length of the shortest path. We could also find this by using the max-flow-min-cost algorithm by allowing capacity 1 and then checking the cost, however Dijkstra call is cheaper. The only thing we pay is more code and 2x graph definition (which is quite verbose for Boost Graph Library). 

## Construction of the flow graph
We take all the given edges and create 2 directed edges for each undirected edge with the specified capacity and cost being the length. Additionally we add one more edge to the start vertex with 0 cost and capacity we want to try out (see the next point).

## Calling max-flow-min-cost
We now know the length of the shortest path from start to finish. Each 1 distance unit ran should result in cost 1. Therefore if N runners run K km race the cost should be N*K if they all chose the optimal route (any). However, if the cost is higher it means some runner had to chose a longer path and hence N is not achievable.

## Binary search
Having a way to check if the city can accommodate N runners we just do a binary search to find the highest possible value. There are several variations of binary search with small differences in the update rule. In this specific case we have two options:
1. `Cost == Expected cost` - This is a possible result. We discard all smaller instances and set `low=mid`.
2. `Cost > Expected cost` - This N is impossible and so are all bigger N so we set `high=mid-1`.

Last thing to be careful in binary search implementation is to avoid an infinite loop. If we have last 2 elements `mid` will be set to either `high` or `low`. Since we update `low=mid` we need to make sure to have `mid` equal to `high` in case there are last 2 elements in the range. `(low+high+1)/2` Simple +1 and integer division will do the work, no need for floating numbers and rounding/ceiling.

# Additional notes
I tried using lambdas with wide capture heavily in this code. The graphs could be encapsulated into separate classes but using the lambda approach you can read the whole code from line 0 without jumping up and down (위아레) and still avoid code reuse. Also, I do not recreate the graph but only rewrite the capacity values, which is the only part that change.
