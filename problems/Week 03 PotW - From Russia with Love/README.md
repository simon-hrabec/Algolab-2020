# From Russia with Love - solution
This problem is a slight modification/upgrade of the Burning coins problem. It features the similar approach, however it has multiple players hence that part will need some special attention. Besides that is also quite straightforward.

 - Dynamic programming to the rescue
 - DP table
 - Whose turn is it
 - Modulo optimization

## Dynamic programming to the rescue
This problem is a clear dynamic programming problem. In each step we can make 2 decisions - if we took all possible paths we would get exponential complexity. However we have a lot of overlapping subproblems, hence DP is a right tool. We can decide for both top-down and bottom-up approaches. The top-down implementation with recrusive calls and cache is easier to code but in the case where we need to fill out the whole DP table the bottom up approach is more efficient.

## DP table
We can have at most 1000 coins. In this case we can create 2D table (1M entries) which will have a result for all the subproblem. On i-j position will be result for a problem having only coins i to j. Note that (roughly) half of the table will be empty/unused since we are interested only for i <= j.

## Whose turn is it
When filling the DP table we have to differentiate between our turns and other peoples' turns. For our turn we are trying to maximize the gains. Otherwise we have to be conservative and assume people are going to chose the worse option for us - as stated in the problem, they are not necessarily maximizing their gains.

## Modulo optimization
In general computing modulos is not cheap and can lead to a small slowdown. In here we can always check whose turn it is using the modulo formula. Or it is also possible to avoid the modulos altogether. We can have a flag (bool) array that indicates whether is the player\'s turn or other peoples' turn. We just initialize all to false and then run a for loop to mark our turns.

# Running time
    Test set 1  (20 pts / 0.700 s) - 0.003s
    Test set 1h (05 pts / 0.700 s) - 0.003s
    Test set 2  (40 pts / 0.700 s) - 0.006s
    Test set 2h (10 pts / 0.700 s) - 0.006s
    Test set 3  (20 pts / 0.700 s) - 0.009s
    Test set 3h (05 pts / 0.700 s) - 0.009s
