# Casino Royale - solution
This is a graph problem. Easy on the coding side but quite difficult in terms of crafting up the solution. It includes flows and the solution can be gained by computing max-flow-min-cost. Further focus is dedicated to the two available algorithms within BGL - `push_relabel_max_flow` in combination with `cycle_canceling` and the faster but more  restrictive (as the name suggest - only nonnegative weights) `boost::successive_shortest_path_nonnegative_weights` algorithm - and how to get rid of negative weights.
- Problem input size
- Unit of flow
- Modeling the problem
- Nonnegative weights

## Problem input size
We are concerned with number of train stops, number of missions, train capacity and mission priority. All of them are quite small - at most 300, 10'000, 100 and 127 respectively. This is important to note because it will affect how we can model the problem. If the number of stations was orders of magnitude bigger than the number of missions the approach described in below would not work.

## Unit of flow
The problem asks about maximal achievable sum of priorities. Note that this does not say anything about the number of missions taken - we do not necessarily want to maximize thus number. Therefore it does not make sense to model one mission as a unit of flow. Instead, we can take a a spot on the train as a unit of flow. When using the max-flow-min-cost algorithm the algorithm prioritizes flow and only then tries to minimize cost. Therefore we will design the problem in a way that the flow will be always equal to the train capacity and the cost will correspond to the sum of the priorities.

##  Modeling the problem
The first issue to spot is that max-flow-min-cost minimizes the cost (sum of priorities in our case) but we want the opposite - to maximize. The easy way to get around this is to work with negative cost and then negate the final result. We create a vertex for each station and we connect the source to the first station by edge with capacity equal to the train capacity - this will serve as a cap that will not allow the flow to go higher. Then we connect all adjacent stations with an edge that has the same capacity as the train capacity and zero cost. This represent the unused capacity on the train. Then we create an edge for each mission (between its starting and final station). It has capacity 1 (one agent) and cost equal to its negated priority. Now we always get flow equal to the train capacity and the minimum cost will be equal to the negation of the highest achievable sum of priorities. Note that it is OK to create a vertex and  an edge for each station since we only have at most 300 of them.

## Nonnegative weights
It is desirable to use the faster algorithm - `boost::successive_shortest_path_nonnegative_weights`. However, for this we need to get rid of the negative edges. One way to do this is to add something sufficiently big to all edges so that there will be no negative edge and also it will not change the result. We know that a mission minimum length is 1 and maximum priority 128 - If we had a mission that takes only 1 stop and previously had cost -128, we would need to increase it by 128 to get to zero. In order not to change result of the algorithm we need to add the same value to each "unit of distance" - if an edge spans of over multiple stations its price needs to be increased proportionally to its length. We increase price of each mission edge by 128\*(number of stations of which this mission span - 1) and each default edge by 128 (since they only connect adjacent stations). However now we need to also interpret the result (cost) differently. Each "capacity" travels over all the stations and cost 128 per each. Therefore the cost will be the difference to the theoretical minimal cost - which is 128\*(stations-1)\*capacity.

# Running time
    Test set 1 (30 pts / 5 s) - 0.013s
    Test set 2 (30 pts / 5 s) - 0.93s
    Test set 3 (40 pts / 5 s) - 0.895s
