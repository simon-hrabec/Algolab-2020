# The Great Game - solution
This solution is quite straightforward as this problem is basically a simple DP problem with one tricky condition.
- Input properties
- Understanding the problem
- The minmax approach
- DP table
- Interpreting the result

## Input properties
We are given basically a graph where we have n vertices. Each vertex (except the last one) has at least one outgoing edge (transition) and all of them are pointing forward (hence no cycles).

## Understanding the problem
We know there are 2 meeples - red and black. If red gets to finish first Holmes win, if black Moriarty wins. What is tricky is alternating pattern of moving the meeples. The red one is always moved twice, then the black one and so on. There are few observations to make sense of it. If we look only at the black meeple it is played once by Moriarty and once by Holmes. The same we can say about the red meeple. Basically these two games (meeples) are played independently - only their turns are intertwined. We can also assume that for the red meeple Holmes will try to put it to the finish as fast as possible whereas Moriarty will try to delay it is as much as possible. The same can be said about the black one just with swapped roles. Coincidentally Holmes starts with red and Moriarty with black. Therefore we can just calculate how many turns will it take them to put the red meeple and black meeple to finish.

## The minmax approach
Each meeple is played in alternating pattern by Holmes and Moriarty, each having the opposite goal. Therefore we can use the minmax algorithm - the minimizing player will take the minimal value from the possible transitions and associated values that would be maximized by the other player. And the other way around for the maximizing player.

## DP table
We have two marbles that can start at different places, but they operate on the same board with the same transitions, hence there is no need to calculating different things for each meeple. For each position we remember 2 numbers - the number of moves if the minimizing player (Holmes with red or Moriarty with black) is playing and the maximum number of moves if the maximizing player is playing (Holmes-black, Moriarty-red). We set the base case (finish position) to 0 for both. Then we iterate backwards and for the min field take the minimum from the maximum (reachable by a transition edge) and vice versa.

## Interpreting the result
We know that each player starts with his meeple (the one that grants him victory if it reaches finish first). For both the meeples we know in how many turns they will arrive to finish (assuming that both players will play the optimal strategy). If one is smaller than the other then we know who won - but if both arrive in the same number of moves we need to check whose turn was it. There is multiple ways how to make the final if statement. For example:

    if (red <= 1 || (red)/2 < (black+1)/2) {
      std::cout << 0 << std::endl;
    } else {
      std::cout << 1 << std::endl;
    }
or

    if (red == black) {
      std::cout << (black < red) << std::endl;
    } else {
      std::cout << (red & 1 == 0) << std::endl;
    }

# Running time
    Test set 1 (25 pts / 1 s) - 0.0s
    Test set 2 (25 pts / 1 s) - 0.001s
    Test set 3 (25 pts / 1 s) - 0.035s
    Test set 4 (25 pts / 1 s) - 0.528s
