# Fleetrace - solution
In this problem we have boats, sailor and connection between them having a different (spectacle) coefficient. Also it is important to notice that the constraints are quite small - 500 for both both boats and sailors and 5'000 for the pairings (rather than 250'000). The nature of the problem and the constraints indicate that this could be a flow problem or perhaps a linear programming task. The solution is discussed in the following chapters:
- Sailors and spectacle sum
- Trick 1 - Use all boats
- Trick 2 - Avoiding negative edges
- Could we use LP?

## Sailors and spectacle sum
We are told in the problem sheet that the task is not to maximize the number of sailors but the spectacle coefficient sum. It is not hard to derive an emaple where the number of sailors/boats will in the race will be maximized but will be suboptimal in terms of the specatcle sum.

## Trick 1 - Use all boats
When se use the max-flow-min-cost we cannot minimize cost for unkown flow. However if we know the flow we can use something like an edge from source that will limit/cap the maximum flow and then we can ask about the cost. In here we can modify the problem that we always work with maximum possible flow. For each boat we add also an edge to sink with spectacle coefficient 0.

## Trick 2 - Avoiding negative edges
It is quite common problem in max-flow-min-cost assignments to avoid negative egdes. When we want to maximize the cost a simple way is to negate the costs of the edges and then work with negative edges. This is quite simple trick but it forces us to use the slower `boost::cycle_canceling`. The common trick is to somehow convert the negative edges to positive numbers. In this case we have a constraint that the spectacle coefficients will be at most 50. Hence, we set price of each edge to be `50 - spectacle_coefficient` and the result will be calculated as `50 * nr_boats - cost`. In this case we operate only with positive numbers and we can use the faster `boost::successive_shortest_path_nonnegative_weights`.

## Could we use LP?
Surprisingly this problem can also be formulated as a linear program. It might not be clear why it can be since we need have binary choice whether to pick boat/sailor but in LP it could pick a fraction of a boat-sailor pair. However the optimal solution will have coefficient 1 or 0 for each  boat-sailor pair or it will have equivalent spectacle coefficient sum as a solution that would use the pairs with just 1 or 0. However LP is considerably slower in this case and won't pass in the required time limits. However feel free to read the [code](fleetrace_lp_slow.cpp).

# Running time
    Test set 1 (20 pts / 5 s) - 0.024s
    Test set 2 (20 pts / 5 s) - 0.01s
    Test set 3 (20 pts / 5 s) - 1.045s
    Test set 4 (20 pts / 5 s) - 1.045s
