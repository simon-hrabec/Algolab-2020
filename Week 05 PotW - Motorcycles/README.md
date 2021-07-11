# Motorcycles - solution
This problem is not difficult in terms of implementation (code) usage of data structures of algorithms. However, it requires some insights. In these problem explanations I do not try to name and explain all possible solutions and list them ordered by implementation difficulty and running speed. Primarily because I often do not think about the really basic solutions (e.g. the O(N^2) comparing all pairs in this case) and given the time constraints I always try to make the optimal solution, since often there is no connection between the naïve and optimal solution.
Generally advisable approach to solving these problems is to solve some instances of the problem by hand and then get an idea how to make efficient algorithm or get some insight about the problem. After that the is just one edge case (breaking ties).
 - Correct types
 - Basic properties of a solution
 - Solution by 2 linear iterations
 - The edge case

## Correct types
 The input coordinates fit into 64bit integer (faster than loading to `double`). Later I explain how I work with slopes. It is calculated as `(y_direction-y_start)/x_direction`. We could use `double`, but due to finite precision and rounding this will fail. Therefore, `CGAL::Gmpq` (the unlimited precision fraction) is required to use.

## Basic properties of a solution
When drawing the problem we quickly figure out that when two motorcycles (lines) meet, the one that goes forward (survives) is the one with smaller angle deviation from the x axis. Also we find out that the solution looks like [sun rays coming from a sun in a kid drawing](https://www.google.com/search?q=sun%20rays%20lines&tbm=isch) - if you cover one half of the picture. Looking at the lines by their starting point at the y axis we see that their slope is decreasing as we go down. Another way to look at this is if we have a line what other lines this single line discards? It is important to figure out if a line should discard some other line and it is discarded before that, the other line will be discarded anyway. A diagonal line discard every line above with slope smaller than 0 and lines below with slope above 0. This is the ultimate line that always survives. If line has positive slope S, it will discard all line above with slope smaller than -S. In some way we might get the feel that looking for the straightest lines might be a good approach and then find what lines do they discard.

## Solution by 2 linear iterations
The solution I used first sorts the lines by their y coordinate origin. They I create a flag array to mark which lines are discarded. Then I do 2 iterations over all the lines - one from top to bottom and the other way around. In both iterations I keep the straightest edge (with slope closes to 0) and discard (set the flag to `false`) edges that collide with it and have a bigger slope. If a line has smaller slope I take this one and proceed further.
The 2 iterations from both sides are necessary to correctly discard all edges with collisions to an edge with a smaller slope.

## The edge case
There is a small catch (of course). If there are 2 lines with slope S and -S the line with positive slope S (starting at smaller y coordinate) will survive. Therefore the 2 for loops needs to have slightly different conditions.

# Running time
    Test set 1 (20 pts / 4 s) - 0.014s
    Test set 2 (20 pts / 4 s) - 0.044s
    Test set 3 (20 pts / 4 s) - 0.157s
    Test set 4 (20 pts / 4 s) - 0.17s
