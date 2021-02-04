# Marathon - solution
This problem is clearly a graph problem. It can be approached in 2 ways (or perhaps more) - we can either apply max-flow-min-cost or use quite elegants and simple solution with max-flow (Thanks Jeniffer for telling me). The shown solution includes the following steps/techniques:

- Dijkstra call to find the shortest path
- Restricting the graph
- Calling max-flow
- Alternative approach

## Dijkstra call to find the shortest path
From the problem description we know the marathon runners will take the shortest (one of it) path from start to finish, therefore a good start is to find the length of the shortest path. Note that by this we find the distance and we might be also able to find one of the paths, however there might be multiple (exponentially many) paths of the minimal/optimal length.

## Restricting the graph
The main idea to this solution is that the runners (in order to achieve the minimal legth) will run only on the shortest paths. Hence, we can remove (set capacity 0) to paths that are not on these paths. The smart way to find those edges is to run dijsktra one more time - in this case from finish. For each edge, we can then say what is the distance from start to starting vertex of the edge and from the ending vertex of the edge to finish (since the graph is undirected). Putting the pieces together - if the edge length + distance from start + distance from finish equals the optimal distance then this edge is on some shortest path and should be preserved. Otherwise it can be eliminated (capacity set to 0).

## Calling max-flow
Having the graph transformed in the described manner the result can then be computed via a simple `boost::push_relabel_max_flow` call. The result can be therefore obtained by 2 calls to dijsktra, iterating over the edges and a single call to max-flow, which all considerably fast.

## Alternative approach
Another way (quite suboptimal, slower - yet interesting to mention) to obtain the result is to use dijkstra to calculate the length of the shortest path and then use the max-flow-min-cost with binary search to find what is the maxium of people to run without using a longer path. We need to use one edge at the start to set the flow and then in each iteration of the binary search compare the cost with the expected cost, which is `flow * min_distance`. It can be interesting for practice of max-flow-min-cost problems to code this up, but keep in mind this problem has much faster and shorter solution. You can also just inspect the code as in this case I tried using lambdas with wide capture heavily in this code. The graphs could be encapsulated into separate classes but using the lambda approach you can read the whole code from line 0 without jumping up and down (위아레) and still avoid code reuse. Also, I do not recreate the graph but only rewrite the capacity values, which is the only part that change.

# Running time
    Test set 1 (25 pts / 1 s) - 0.024s
    Test set 2 (25 pts / 1 s) - 0.029s
    Test set 3 (25 pts / 1 s) - 0.01s
    Test set 4 (25 pts / 1 s) - 0.032s
