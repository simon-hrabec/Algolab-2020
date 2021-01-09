# Punch - solution
I good way to start with any problem is to look at the limits for the input. Here we are told that there is at most 100 distinct drinks and 10'000 people (which is equal to required liters). Since these 2 numbers are quite small we could consider solving this problem with DP (consider meaning take it as a hypothesis and research if we can describe a recursive relation for this problem). Dynamic programming problems are special that for some people they are extremely easy but some people find them hard because they cannot find the proper way how to express the DP. After having the idea the implementation is always easy. Lets break the solution into the following:
- Solution criteria
- Size of the DP table
- Expressing the recursive relation
- Base case

## Solution criteria
In the solution we are looking for a combination of the available drinks to have at least N liters and offering the lowest price. In case of a tie there is a second criterion to optimize - the number of drinks used. Hence we have to remember both in the minimal price and the maximum number of drinks for that price.

## Size of the DP table
We have at most 100 drinks and at most 10'000 people (liters), therefore the DP table will have at most 1'000'000 (aka 10^6) entries, which is completely fine, since we do a single calculation for each entry.

## Expressing the recursive relation
We can define **DP[i][j]** as the solution for problem while being restricted to only **i** drinks and trying to get **j** liters. We define the relation such that `DP[i][j] = best(DP[i-1][j], DP[i][j-volume[i]])`. In the first case we just dont use the ith drink. In second we take one piece of it and and refer to a simpler (requiring fewer liters) problem (that we solved before). Actually `j-volume[i]` can be negative, in which case we just take 0 (sometimes the optimal solution might have excess volume). By `best` I define a function that takes smaller price and in case of a tie takes the price and higher number of drinks.

## Base case
Before iterating over the DP table and filling it we need to set the base cases. For each entry we need to remember minimum price, maximum drinks (for that price) and it is also convenient to remember a boolean flag if we used the ith drink or not. Therefore we set `DP[0][?]` we set `(INF, 0, false)`  since it is not possible to get any non-zero amount of liters using 0 drinks. By INF we can use the maximum integer type - `std::numeric_limits<int64_t>::max()`. For `DP[?][0]` (including `DP[0][0]`) we set `(0, 0, false)` - we get 0 liters of the drink for free.

# Running time
    Test set 1 (50 pts / 2 s) - 0.002s
    Test set 2 (50 pts / 2 s) - 0.181s
