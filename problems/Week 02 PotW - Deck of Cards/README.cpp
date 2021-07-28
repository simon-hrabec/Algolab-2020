# Deck of Cards - solution
This was the first Problem of the Week - basically a practice one. This problem is quite similar to finding a continuous subsequence that sums up to N. In here, we are looking for a subsequence that sums the closest to N, which is not the same problem, but can be solved the same way.
- Two pointers approach
- Alternative implementation

## Two pointers approach
We set up two pointers - backwards and forward one that bound the subsequence we consider from both sides and we remember the sum between those two pointers. If the sum is over the target value we shrink the subsequence by advancing the backwards pointer, otherwise we extend it by advancing the forward one. If our subsequence is closer to the target than any previous one we remember the start/end and also update the best achievable sum.

## Alternative implementation
It is also possible to have a simple for loop and only have the backward pointer as additional variable this requires less code but it is a slightly less straightforward.

# Running time
    Test set 1 (30 pts / 1 s) - 0.0s
    Test set 2 (40 pts / 1 s) - 0.007s
    Test set 3 (10 pts / 1 s) - 0.124s
    Test set 4 (20 pts / 1 s) - 0.124s
