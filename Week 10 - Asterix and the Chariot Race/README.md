# Asterix and the Chariot Race - solution
This problem has quite cryptic description - so dont get discouraged. The important information is that there are N cities and N-1 stages (edges). We start at city 0 Modicia and each city is reachable from Modicia. This implies that we are indeed operating with a rooted tree. Some hard problems can be computed efficiently on trees - this should give us hope. This problem might be confued with the minimum vertex cover, however in this problem we are not trying cover edegs, but verticies. For each vertex we need at least 1 neighbouring vertex to be chosen. The solution is written in the following chapters:

- Recursive relation
- 3 possible states
- DFS and value comination
- The final result

## Recursive relation
Problems with trees can sometimes be forumalted recursively as the subproblems are subtrees and independent of each other. In this case we could decide to pick the root or not and based on that see the solution of subtrees. If we picked the root then the roots of the direct subtrees does not have to be picked (but can). If the root is not picked then at least one of the direct descendants needs to be picked. This it not as trivial as it seemed to be. Perhaps it is possible do it the other way around. Propagate some information up and make the decisions there.

## 3 possible states
The trick to this solution lies in realising we need to define 3 states for a node and its subtree.
1. First is the (optimal) solution for this subtree if the root of this subtree is picked. We might find it useful to have some direct descendant to be picked if the current node has expensive value and it would be better if not picked.
2. Second it the solution in which the subtree has a root that is not picked, but is covered by some of its direct descendants. In this case it cannot provide cover for the current node but on the other hand it also does not require it. Hence we could consider a case when all direct descendants are covered and the current node might be cover by its parent.
3. Third is the solution if the current node is not covered. We need to consider this case as well because if the parent should be picked then it would makde this node acutally covered. 

These are the 3 values of the optimal solutions for the subproblems that we need to move upwards in the tree and then combine them.

## DFS and value comination
We run DFS to propagate the values from the bottom of the tree upwards. We now assume to have the values for the 3 defines states. Now we need to figure out how to combine them to calculate the 3 values for the current node.
1. The selected state is quite simple. We take the price of the node and add the not-covered cost for all the subtrees (which is supposed to be the cheapest one).
2. The covered state is a bit tricky. We need to either use the selected value (it might be still the cheapest) or we need to pick covered options for all the subtrees except for one, which needs to be picked. We need to pick the one that has the smallest difference between selected and covered.
3. The not-covered state is quite simple too. We just take all children to be covered and do not select the current node. It is also important to note that it might be actually cheaper to cover the node than leave it not-covered and if it is the case we should return minimum of these two.

## The final result
We get 3 values for the root. We might be tempted to pick the selected value, but the covered is enough. It is sufficient to fulfil the problem statement (all nodes covered, including 0 city) and it might be cheaper.

# Running time
    Test set 1 (25 pts / 4 s) - 0.174s
    Test set 2 (25 pts / 4 s) - 0.189s
    Test set 3 (25 pts / 4 s) - 0.19s
    Test set 4 (25 pts / 4 s) - 2.934s
