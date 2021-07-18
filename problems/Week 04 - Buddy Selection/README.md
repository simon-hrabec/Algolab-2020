# Buddy Selection - solution
Buddy Selection is a graph problem. Students are nodes/vertices and an edge between two students means there is enough common interests.
- Approach
- Input size
- Number of common characteristics
- Maximum viable number of characteristics

## Approach
We need to first compute the shared characteristics (count) for all pairs. Then if this number is "big enough" there will be an edge in the graph between the 2 students. After that we call the `boost::edmonds_maximum_cardinality_matching` algorithm that calculates the maximum matching. If this matching includes all the students then the chosen number of characteristics is viable.

##  Input size
We have at most 400 students. This is small enough that we can easily iterate over all pairs of students. Even when multiplied by additional 100 (maximum number of characteristics per student) the number is still small enough.

## Number of common characteristics
Rather than iterating over pair of students and then computing the shared characteristics count, we iterate first over characteristics. For each characteristic we we loop over all pairs of students having this trait and increment a counter in a 2D array.

## Maximum viable number of characteristics
It is possible to fully determine the maximum number of characteristics that still allows full matching. For this we can simply use binary search and alter the number that sets if the number of characteristics is sufficient to warrant an edge between the two students. However this is not necessary - we dont need to know the exact number. We only need to know if there is viable matching for bigger number of characteristics than proposed. We can just check for N+1 characteristics.

# Running time
    Test set 1 (30 pts / 2 s) - 0.022s
    Test set 2 (40 pts / 2 s) - 0.013s
    Test set 3 (20 pts / 2 s) - 0.073s
    bordercases (10 pts / 2 s) - 0.027s
