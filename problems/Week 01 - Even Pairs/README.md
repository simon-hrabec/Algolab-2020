# Even Pairs - solution
First week is just practice round that does not contain any complicated problems, it does not require any libraries (CGAL/Boost) nor fancy algorithms. Only few lines of code.
- Prefix sums oddness/evenness
- Combining the prefix sums

## Prefix sums oddness/evenness
If we are not looking for O(N^2) solution (which generally we are not) then we need to do something smarter than simply go over all the pairs. For this we can calculate how many prefix sums are even and odd. We can achieve this simply by having a sum, adding to a it and checking for the last bit and count as we go along.

## Combining the prefix sums
Similarly to how we can get sum of any subsequence using the regular prefix sum here we can use the knowledge of evenness. If we have one sum from 1 to j and another from 1 to i (where i>j) we can deduce the evenness of the sum from i to j by evenness of the two sums. If both are even then the sum will also be even. If both are odd the sum will be even. We just need to compute how many i, j pairs are there to have this criteria. For this we use the (N\*N-1)/2 formula. We need to apply it to both the count of even and odd prefix sums. Besides that we also need to to account for sequences long 1 element that are even (even numbers).

The final formula is therefore:
`(even*(even-1))/2 + (odd*(odd-1))/2 + even`

# Running time
    Test set 1 (40 pts / 0.400 s) - 0.0s
    Test set 2 (40 pts / 0.400 s) - 0.004s
    Test set 3 (20 pts / 0.400 s) - 0.027s
