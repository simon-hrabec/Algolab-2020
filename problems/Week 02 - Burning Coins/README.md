# Burning Coins - solution
The quintessential dynamic programming problem. Filling the the DP table with 2 cases is all what is needed.
- The base case
- DP table
- Minimax

## The base case
When dealing with DP problems we need to derive the subproblem relation and the base case. For our problem the base case is 1 coin. However we need to differentiate if this last coin will be picked by you or the friend - and then set the value to the price of the coin or zero respectively.

## DP table
We create a 2D table where i-jth element will be the maximum reachable (guaranteed) amount for the subproblem when only coins between i and j are left. Note that half (roughly) of the table will not be used.

## Minimax
We iterate over all subproblems - first we process subproblems with 1 coins, then all with 2 coins etc. We need to differentiate the case when we pick and when the friend picks. We can find this by checking for the last bit (odd/even). Based on that we either do minimum of the 2 subproblems (your friend's turn) or the maximum of the 2 subproblems + the value of the taken coin (our turn).
    
# Running time
    Test set 1 (30 pts / 2 s) - 0.0s
    Test set 2 (40 pts / 2 s) - 0.004s
    Test set 3 (30 pts / 2 s) - 0.093s
