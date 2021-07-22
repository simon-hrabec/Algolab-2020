# Real Estate Market - solution
Real Estate Market - buyers, properties (houses), bids and states to which houses fall and restriction on those. If you guess this can be solved as a graph problem you would be right. The solution is described as follows:
- Modeling the problem
- Simple solution
- Nonnegative weights

## Modeling the problem
The problem has houses and buyers. All buyers submit bids for all houses. Each buyer wants to buy at most one house. What complicates this problem is the restriction on houses in each state. To start in a straightforward fashion we can create a node for each buyer, each house and each state (and also source and target/sink). We connect the following:
- the source to each buyer - L1
- each buyer to each house (bids) - L2
- each house to its respective state - L3
- each state to target/sink - L4

## Simple solution
The idea - a flow means a house bought and the cost of the edges used for this is the price for which it has been sold. To achieve this we set L1 have capacity 1 - each buyer can buy at most 1 house. For L2 we set capacity 1 and cost equal to negated bid. For L3 we set capacity 1 (each house can be sold only once). And for L4 we set capacity that's equal to its state maximum allowed number of sold houses. Note that the only cost to edges is assigned to L2 (bids) - all other edges have zero cost and are there only for capacity purposes. Note that we used the common trick - to be able to use the Max-Flow-Min-Cost algorithm we negated the cost values so in the end we basically get Max-Flow-Max-Cost instead. However, for this we need to use the slower `boost::push_relabel_max_flow` & `boost::cycle_canceling` and we also need to negate the result (otherwise it would be negative).

## Nonnegative weights
Another trick to make the problem run faster is to get rid of the negative edges (if possible). Then we can use the faster `boost::successive_shortest_path_nonnegative_weights` algorithm. We see that there is at most 100 buyers, 100 houses and each bid is at most 100. These are fairly low numbers - it should allow us to increase all edges by some number to get into positive numbers and then substract some amount from the result to compensate for that and get the original result. In this problem the transformation is rather easy - we just increase each bid edge by 100 in order to get to nonnegative costs. Then we just add 100 for each house sold (flow in the network) and negate the rest to get the result.

## Implementation note
It sounds logical to create the edges in order L1, L2, L3 and L4. However we are given the input in different order and unless I would like to store the data in some temporary array I have to create them in different order.

# Running time
    Test set 1 (20 pts / 1 s) - 0.011s
    Test set 2 (20 pts / 1 s) - 0.018s
    Test set 3 (20 pts / 1 s) - 0.012s
    Test set 4 (20 pts / 1 s) - 0.014s
    Test set 5 (20 pts / 1 s) - 0.09s
