# Beach Bars - solution
Beach bars is not very hard, but it has some edge cases so it is important to be go over the example cases on paper on be thoughtful.
- Two pointers
- Improving solution
- Odd edge case

## Two pointers
We are given a set of places (parasols). These lay on a line (1D) and we are interested in distance between them. To find a suitable place for a bar we are interested in a window of 200 meters. Hence, it is logical to sort the places and then iterate over them with some kind of sliding window/two pointers. As we move the forward pointer se check what is the distance between the backward pointer (distance between the places they point to). If it is more than 200 we shift the backward one until it is. By this we can easily all the sequences of places that are permissible but cannot be extended on either side.

## Improving solution
We have 2 things we are optimizing for - the number of places (maximizing) and then the distance/range (minimizing). Hence we check and if the number of places is bigger we remember this one and throw away previous results. If the distance/range is smaller we do the same. If the number of places and range is the same we add this to our set of possible solutions.

## Odd edge case
What the problem asks for is not the ranges themselves but the bar locations that are in the middle of those ranges. Similarly to medians, with odd numbers this gets tricky. We are told that the coordinate of the bar can be only integer, therefore if we have odd range there are 2 places in the middle to consider and we need to add both.

# Running time
    Test set 1 (20 pts / 1 s) - 0.001s
    Test set 2 (20 pts / 1 s) - 0.002s
    Test set 3 (60 pts / 1 s) - 0.376s
