# Defensive Line - solution
In my opinion this is one of the harder problems. But it really depends on what your strengths are in competitive programming. You might also find this problem rather easy. And that's how it goes with dynamic programming problems. It is few lines of code and nothing much to think about if you see how to express the solution. If not, good luck.
- Two pointers approach
- Alternative implementation

## Set of continuous non-overlapping subsequences
The problem statement is more cryptic than usual and it might be hard to deduce what exactly is required. For each attacker we are looking for a continuous subsequence (subset of defenders that stand next to each other) with sum of their strengths equal to K with additional requirement that  these subsequences cannot overlap (two attackers do not attack the same defender). This strict requirement makes it somewhat nicer - there will be at most N (number of defenders) subsequences that have this property.

## Two pointers to the rescue
The first step that might be helpful in our ultimate goal of solving this problem is to locate the valid subsequences. We can have an array and if a valid subsequence ends here we fill it with its length. To get there we use two pointers approach - move forward pointer to extend the subsequence to reach K and move the backwards pointer if we go over K. If sum is equal to K we mark it down to the array.

## The DP formulation - combining subproblems
The key part of a DP problem is to express the solution from its non-overlapping subproblems. In this case we have attackers and defenders so we will play with these. If we think about considering additional defender there can be two cases - a subsequence summing to K can end there or not. If not then adding this defender will not change anything since we cannot use him here.  But if it does we can now also consider the following case - add the length of this sequence (L) to the previously computed result with one less attacker and without the last L defenders. Note that we can easily get into a case where no assignment is possible, hence we need to handle those cases as well.

## What causes the segmentation fault?
After running the code you might end up with a "segmentation fault". In this case it is caused by too big local array that does not fit on stack. Making this array a global variable solves this problem easily (now it is not in stack but in data segment). Allocating the array dynamically is also possible but with 2D array it is easier to have a static one (with sizes that cover all inputs).

## Memory efficient approach
As common in DP problems, you often need only one element of the DP table as a result and you also operate only on the last 2 rows. Hence, it is possible to remember only the last 2 rows to save some space.

# Running time
    Test set 1        (20 pts / 0.500 s) - 0.0s
    Test set 2        (15 pts / 0.500 s) - 0.006s
    Hidden test set 2 (05 pts / 0.500 s) - 0.006s
    Test set 3        (15 pts / 0.500 s) - 0.07s
    Hidden test set 3 (05 pts / 0.500 s) - 0.07s
    Test set 4        (15 pts / 0.500 s) - 0.007s
    Hidden test set 4 (05 pts / 0.500 s) - 0.007s
    Test set 4        (15 pts / 0.500 s) - 0.08s
    Hidden test set 5 (05 pts / 0.500 s) - 0.08s
