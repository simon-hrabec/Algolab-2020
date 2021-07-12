# Fighting Pits of Meereen - solution
This problem feels hard. It does not fall into any special category and there is no special insight or pattern to be discovered (if there is please let me know). However it is useful to rember some bit trickery (actually nothing [fancy](https://graphics.stanford.edu/~seander/bithacks.html), only shifting and bit and/or).

Solution explanation:
- Observations and bounds
- Iterative solution
- State representation
- Implementation
- Theoretical bit lowerbound

## Observations and bounds
Some of the constraints are quite small. The memory of the audience is at most 3 and there is at most 4 types of fighters. However there is at most 5000 figthers. We can work out something from this info. First, we cannot assign all figthers to just one entrance. The penalization based on the difference grows exponentially. Since the maximum bonus given in a round is 3000 (if the memory equals 3 and we have 3 different figthers) the difference between number of figthers sent to south and north (souther and northern entrance) can never be bigger than 11 since 2\^11 is 2048 and 2\^12 is 4096 which is bigger than 3000. Note that if the bonus is just 1000 (due to all figthers being the same type) we could have even tighter bound for the difference. Another observation to make is that it is enough to remember only M-1 fighters for each entrance. For M equals 3 it makes 4 figthers (since we need remember both entrances separately) of at most 5 types (when including the "no figther" option).

## Iterative solution
Since we are making a binary decision an idea how to proceed is to do a recursion with branching at every point. However, the input has length in thousands, hence this is not applicable. Moreover, we could make different choices but at some point have a state with the same conditions - same difference between north and south, same (M-1) history for both entrances. Therefore we could proceed with suboptimal results unnecessarily. Hence an interative approach appears to be applicable (can this be called DP?). We define a state to be the history of both entrances, the difference and the score. In each step we process one figther and look at all the admisible states so far and for each we try send the fighter to both north and south. It is possible we reach the same state in one step - therefore we consider only the best score for the state.

## State representation
It seems useful to use a `std::unordered_map` in this problem (state to score). For it we need a keys that are hashable. A simple trick is to map all the information into a single integer with some bit operations. In this case we have to remember 4 numbers with range 5 (0-4). Number of 5 options can be represented by 3 bits. The difference has range 23 (-11 to 11). This fits into 5 bits. In total this makes 4\*3+5=17 bits, which is well below 32. Hence we can even do some more convenient (byte) allignment. 2 bytes will be for the difference. One byte will be for each entrance - 4 bits for a figther.

## Implementation
We use twice `std::unordered_map<int,int>` - one for the current step and one for the following. In each step we take the admissible states and try sending the figther to both south and north. To calculate the round bonus we need to use the history and the difference. If the round pay-off is below zero we ignore it. We add the round bonus to the best achievable score for that state/step and put it into the second map. To update the history we need to compile the new state using several bit manimulation operations (see the code). If the same state already exists there we keep just the maximum. After we process all steps (figthers) we search the map for the biggest value - thats the result.

## Theoretical bit lowerbound
In the paragrafs above I showed that we can represent the state in 17 bits. However, we can do somehow better (spacewise). We can multiply the ranges together - 5^4\*23=14375. This fits into 14 bits. However we would need to use divisions and modulos (slow) to get each component from the number and multiplication and addition to compose it. And saving space is in this case quite irrelevant.

# Running time
    Test set 1 (25 pts / 2 s) - 0.004s
    Test set 2 (25 pts / 2 s) - 0.008s
    Test set 3 (25 pts / 2 s) - 0.016s
    Test set 4 (25 pts / 2 s) - 0.132s
