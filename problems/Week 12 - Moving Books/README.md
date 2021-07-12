# Moving Books - solution
This problem falls into the category of few easy problems in this course. By all problem description, solution complexity and implementation difficulty. First (good) idea is to sort both the books and the friends by weight/strength in decreasing order. If a friend can carry box B[i], he will be able to carry all boxes B[i+n] for some positive n. Moreover we can always assume that heavier box will always go to stronger friend - If we look at the sorted boxes, a continuous sequence will be carried by friend 1, another continuous sequence (possibly empty) by friend 2 and so on. There is no optimal solution where there a stronger friend would have to carry lighter box than a box of his weaker friend.
Then we need to think what are we trying to minimize - we care about the the maximum number N of boxes assigned to a single friend. Therefore we can try different values of N and then assign the N heaviest boxes to the strongest friend, following N boxes to the second strongest friend. For a case where each friend has at least N boxes this is the optimal assignment. We only need to check if this assignment is possible. For this it is enough to check if each friend can carry his/her heaviest box.
And now the last piece of the puzzle - how to come up with the right N. How? I don't know. And if I don't know I guess. What is the efficient way to guess in a problem where we are looking for the best YES answer where the interval is separated into continuous YES and NO? Binary search.
Also there is an edge case - if the strongest friend cannot carry the heaviest box this problem does not have a solution (*impossible*)

# Running time
    Test set 1 (20 pts / 0.600 s) - 0.004s
    Test set 2 (40 pts / 0.600 s) - 0.242s
    Test set 3 (40 pts / 0.600 s) - 0.438s
