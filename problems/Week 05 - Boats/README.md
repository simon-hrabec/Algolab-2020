# Boats - solution
Boats is a rather simple problem. Since the topic of the week 5 is greedy algorithms, it is natural to first look for a linear, greedy algorithm to solve this problem.
- Resemblance to the calendar problem
- Greedy approach
- Generalizing to a working algorithm

## Resemblance to calendar problem
The quintessential greedy problem and often the one presented as an example is the calendar/scheduling problem. Given a set of meetings, what is the maximum of meetings possible to fully attend without any overlap? For this task we need to only sort the meetings by ending time and then iterate and pick any meeting that does not overlap. The difference here is that the boats do not have a set position - they are described by a ring location (to which the boat has to be connected) and the length of the boat. Ultimatelly, the boat can be at `length+1` positions.

## Greedy approach
First vector of attack on this problem will be deriving a greedy algorithm or during this process to get an idea/proof why this cannot be done. Similarly to the calendar scheduling we order the boats by their ring location. Then we iterate over the boats. We can always pick the first boat in its leftmost position. For the second boat we do not have such guarantee. We might always pick it but not necessarily in its leftmost position. Having picked those 2 boats for the third boat we get the following 3 cases:
- We are able to also put the third boat in its leftmost position.
- The ring of the boat is already covered by the second boat, but we can pick this boat instead of the previous boat since then we will have the same number of boats used but we will cover less space which might be beneficial in the future.
- The ring of the boat is already covered by the second boat and there would be no benefit of swapping the third boat with the second one since it would reach even further.

## Generalizing to a working algorithm
As we go to 4th boat and so on we need a generalization of the approach from just 3 boats. As we iterate we pick and usable boat and if we cannot pick it we check if we can throw away the last boat and use the current one for a better outcome. This can be implemented with few if statements or `std::max`/`std::min` in various way, all doing the same thing.

# Running time
    Test set 1 (50 pts / 1.500 s) - 0.0s
    Test set 2 (50 pts / 1.500 s) - 0.009s
