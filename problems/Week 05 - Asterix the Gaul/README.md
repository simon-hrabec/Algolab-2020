# Asterix the Gaul - solution
This problem is hard. And by hard I mean it is not easy to get 100% and also that this problem in nature is not tractable. It is NP-hard and there given the constraints 2^50 for time and distance we cannot use any polynomial algorithm and best we can do is some kind of exponential solution. I include 2 version of the code. One is rather simple (although could be made even simpler and slower) and second uses the technique Split & List to achieve full score. The problem is discussed in the following chapters:

- Iterating over possible subsets of moves
- Calculating solution
- Caching best distance for #moves
- Split & List

## Iterating over possible subsets of moves
As mentioned above this problem is NP-Hard. Therefore we need to try (almost) all possible subsets. Each subset needs to have `time-sum < time-given`. One elegant way is to have an integer where each bit represents one item. Since this problem has exponential solution most we would not be able to compute a solution for problem with more than 64 items anyway, hence we can use either 32 or 64bit integer (for this problem 32 is enough). All we do is increment the number and then add elements to our subset if the respective bit is set to 1. The only ugly thing is the need to iterate over the integer bits or use some of the [bit magic tricks](https://graphics.stanford.edu/~seander/bithacks.html) to get the last bit.
Another approach is to use DFS (we can argue if this is actually DFS since we are not searching over a graph but rather over a theoretical state space). In each step we consider one item and branch into 2 cases - we take it or we dont. This is also an easy and elegant way to iterate over all subset. Moreover, it is possible to sort the moves by time and once the remaining time is smaller than the time required for a move we know it will be also for all the following moves and therefore we can cut off that branch.

## Calculating solution
Given only time and distance this problem could be solved by copy-pasting a knapsack solution from the internet. Therefore there is the slight addition of potions. For each subset we know number of moves used, remaining distance and remaining time. The time is irrelevant at this point (only needs to be positive). We then do a search (could be a binary search) in the potion array to determine how many potions are required to reach Panoramix using this specific subset of moves. It is possible the number is 0 (remaining distance is 0 or negative) or that Panoramix cannot be reached.
We then save the best possible (minimum over required potions) result and print it (or *Panoramix captured*).

## Caching best distance for #moves
It is possible to note that if we have remaining distance 10 using 5 moves and another case having remaining distance 15 using 5 moves the later is suboptimal and can be discarded. Hence, we can create an array representing smallest distance achievable using N moves. After we fill this array (iterating over all subset) we do the binary search only for each element in this array (which is at most 30) to save some time.

## Split & List
The first simple DFS code solution does not pass the 4th test set. The solution is to use the Split & List technique. Splitting the moves into 2 parts, computing all subset for but parts and them combining these. I then sort the data (for efficient lookups) and remove suboptimal entries (6 remaining distance with 4 remaining time is suboptimal to 5 distance and 4 time). I consider solutions using different number of moves separately. For each entry in the first half I do I lookup (using binary search) in the second half (in each array containing N moves). By this I fill again the array with best distance for number of moves and proceed the same way as in the simple DFS solution.

## Possible improvements
We could do the binary search at the end only in the part of the potion array that could improve the solution. However, this improvement is insignificant and will not bring a measurable speedup (<1ms).
Another possible speedup is to reduce the number of parameters for the DFS call. Since all these parameters will be copied to a new call stack frame. Specifically `max_move` and `arr` does not change for all the subcalls in the call tree. Therefore these 2 parameters could be made a global variables and set properly before each of the 2 calls. By this we could save few milliseconds (also irrelevant).

# Running time
    Test set 1 (20 pts / 4 s) - 0.003s
    Test set 2 (20 pts / 4 s) - 0.003s
    Test set 3 (20 pts / 4 s) - 0.412s
    Test set 4 (40 pts / 4 s) - 0.541s
