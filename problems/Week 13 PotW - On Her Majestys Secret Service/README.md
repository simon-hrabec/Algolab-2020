# On Her Majesty\'s Secret Service - solution
This is a tricky problem. From the given toolbox (algorithms and data structures) we were provided (shown/taught) during the semester there is no algorithm that could directly compute what we want. Hence, we have to combine multiple algorithms or do some transformation first. Note also that most of the problem (80%) is limited to capacity 1. Therefore it might be a good idea to first solve the simpler version of the problem and only then to get concerned about C = 2 (or possibly even more, in case we generalize the solution). It is possible to solve this problem with multiple approaches - maximum flow, max-flow-min-cost and maximum-matching.
- Graph properties
- Shortest paths
- Assignment problem
- Higher capacity
- Possible improvements

## Graph properties
We are given a graph with vertices (places) and edges (slopes/lifts) which are either unidirectional or bidirectional - we can decompose the bidirectional ones to 2 simple directed edges. The constraints are also pretty small - we have at most 100 agents and 100 shelters. The edges have travel time but there are no constraint for capacity whatsoever - therefore a path of one agent will not interfere with paths of other agents. All what matters is the selection of the shelter for each agent.

## Shortest paths 
Being aware of the irrelevancy of the path we might decide to generate a matrix that would contain the length of the shortest path for each agent from his starting location to all the shelters (which would contain at most 10\'000 entries). For this we need to call Dijkstra A times (A = number of agents).

## Assignment problem
We are now trying to assign to each agent one shelter so that we minimize the longest used edge (where each edge has value the shortest path between the agent and shelter plus D - the time required to perform the protocol and enter the shelter). For this we do not have a direct algorithm but rather that we can do the "try and check" approach. If we chose a number N (all agents will be able to reach shelter within time N) we can only include edges that are at most N. Then we check if we are able to match all the agents to a shelter. We can then use binary search over some interval (perhaps 1 to INT_MAX or something further constrained) to search for the best achievable N.

## Higher capacity
Once we have solved the easier version of the problem the question is how to extend the solution to also include instances where shelters have capacity 2 (or possible higher). The solution might sound rather easy, but that does not necessarily mean it is easy to come up with it. There is a special set of problems that have these properties (called coffin/jewish problems - more in [PDF](https://arxiv.org/pdf/1110.1556.pdf#:~:text=These%20problems%20were%20designed%20to,from%20getting%20a%20passing%20grade.&text=These%20kinds%20of%20math%20problems,%E2%80%9Ckiller%E2%80%9D%20problems%20in%20English.)). We want to consider another slot in the shelter. For this slot the coming agent would have to wait for the previous agent to check in. The trick is to create another shelter and take all the paths to it and increase them by D. We can then prove that if two agents are coming to the same shelter (represented by 2 vertices) we could schedule them to check in in a way that they would not overlap their check-in sequence and the maximum time would still be maintained. Note that we could do the same for C > 2 - just adding more nodes representing the shelters.

## Possible improvements
There are a few things that could make the code run faster. First, we don\'t need to run Dijkstra for every agent but rather for every agent location (some agents can share the same starting location). Also we can have more agent locations than shelter locations. In this case we could build the graph the other way (inverting the direction of the edges) and run Dijkstra for each shelter location instead. Another place is the rebuilding of the graph during the binary search. In some instances we could only add few edges.
    
# Running time
    Test set 1 (20 pts / 1 s) - 0.024s
    Test set 2 (20 pts / 1 s) - 0.027s
    Test set 3 (10 pts / 1 s) - 0.048s
    Test set 4 (10 pts / 1 s) - 0.153s
    Test set 5 (15 pts / 1 s) - 0.224s
