# Attack of the Clones - solution
Attack of the Clones is an interesting problem. It resembles the quite easy problem of fitting most meetings in to someone's schedule that can be solved by a simple greedy algorithm, however it is spiced up by the circularity of the input (it wraps around).
- Greedy scheduling problem
- The catch
- Trying a case
- Which Jedi to try
- The coding challenge

## Greedy scheduling problem
This problem resembles a lot the problem where a meetings with start and end time are given and the goal is to select as many meetings without an overlap. This can be solved by sorting the meetings by the finish time and then iterating over the meetings and always picking the first possible meeting that does not cause a collision.

## The catch
The only addition to the aforementioned problem is the circularity of the input array (circle C and its segments). This implies that there is no beginning to the array where we could start.

## Trying a case
The problem has a solution that is a subset of the given Jedi (Jedi is supposedly also the plural case). If we pick a random Jedi from the subset (or since there can be multiple solution pick a Jedi from any subset solution) and then we run the greedy algorithm (with some way of resolving the circularity) till we came back to the first Jedi we get a valid solution.

## Which Jedi to try
In the problem there is stated (definitely not by accident) that there is a segment that is covered by at most 10 Jedi knights. Knowing this we look for a segment that is occupied by the least Jedi (or by at most 10) and then we try all the Jedi in this segment as the starting Jedi for the greedy algorithm.

## The coding challenge
The most difficult part of this problem is to code everything up. To deal with the circular array it is either required to make the algorithm work with the jump from some number back to 0/roll over or it is possible to disconnect the array somewhere and move the elements before the place of disconnection back to the end. I used the later approach. 

# Running time
    Test set 1 (30 pts / 1 s) - 0.005s
    Test set 2 (30 pts / 1 s) - 0.407s
    Test set 3 (40 pts / 1 s) - 0.483s
