# New York - solution
This problem is more difficult due to its a bit cryptic description and the necessity to combine multiple data structures together (map and DFS stack/array). It can then be solved using DFS traversal and remembering the temperature of the last N nodes, storing the solution points and the before printing them sorting them. More details:
- Interpreting the description
- Tree traversal with DFS
- Marking viable starting nodes
- Maximum temperature difference on a path
- Printing the solution
- Implementation notes/alternatives

## Interpreting the description
We start in New York (node 0) and we are told that there are some secure critical points - nodes without any outgoing edges. Moreover, we are told that there is exactly one path from node 0 to every other node. Combining these together we get a rooted, oriented tree. And the feasible path (paths) we are looking for is somewhere within the tree going from a node to some descendant (not necessarily a leaf node).

## Tree traversal with DFS
Defining the problem like this lead to an idea to use a simple graph/tree traversal algorithm (i.e. it is worth exploring this approach as a possibility and see if it is possible to solve using such). We use DFS (since we need the path) and as we descent once we reach at least depth M (the required length of the trip) we check for the maximum temperature difference among the last M nodes and if it is smaller than the given temperature limit mark the starting node of that path. The question is whether we are able to find all the necessary data structures to support the required queries we stated we need.

## Marking viable starting nodes
When we find a suitable path, how do we get the ID of the node M level above? We could somehow get it and store it in another array, however, since one node can have multiple valid paths starting at it, there would be duplicities. Therefore it is better just to mark the node as a valid start. For such reason we will use an array that will represent the DFS call stack. For each DFS call we will add both the temperature at that node and a boolean flag representing whether the node is a valid starting node (set to `false` by default)

## Maximum temperature difference on a path
Another query we want to be able to answer is what is the maximum temperature difference for the given path. We want both cheap updates and queries. As we descend we store the temperatures of the nodes in the array/DFS call stack. As we go deeper we will be able to say what is the temperature of the node no longer included in the path. To find out what is the difference between the minimum and maximum temperature we will use map to remember occurrence count of each temperature. We update this map to contain only the temperatures on the path. More specifically we add temperature as we descend and remove the last temperature and when we finish the DFS call we remove the most recent temperature and put back the removed, previously last temperature. The maximal temperature difference is given by first element minus last element in the occurrence map.

## Printing the solution
When we are about to finish the DFS call we check if some of the calls from the successor nodes set this viable start flag. If so, we add the node ID to the result array. Before printing at the end it we sort it (as required in the description).

# Running time
    Test set 1 (20 pts / 4 s) - 0.012s
    Test set 2 (20 pts / 4 s) - 1.414s
    Test set 3 (20 pts / 4 s) - 0.004s
    Test set 4 (40 pts / 4 s) - 1.989s
