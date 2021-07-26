# Octopussy - solution
Funny problem with a funny description! Unlike some graph problems there is no clear way to solve this problem and more approaches can be taken. It really depends on you whether you consider this a pros or con. The problem is discussed in the following chapters:
- A pyramid or a tree?
- First goes first
- Tick tock (counting time)

## A pyramid or a tree?
First, you want to draw an example on paper. Even though the problem talks about balls and a natural 2D way to stack balls on top of each other is to make the so called pyramid, this is not the case! If two balls next to each other do not share a ball as a base. So rather than a pyramid it is good to view this problem as a ([perfect - full and complete](https://en.wikipedia.org/wiki/Binary_tree#Types_of_binary_trees)) binary tree.

## First goes first
One possible approach is to try defusing the bombs by the order in which they explode. If we try to defuse a bomb that is not a leaf node in the tree we also have to defuse all the bombs below. However, we know that all the bombs below either have been already defused or have a trigger time after the bomb we want to defuse (hence we don't have to check their explosion time).

## Tick tock (counting time)
The previous paragraph implies the existence of a flag array - to denote if any given bomb has already been defused. To iterate over the bombs in according to their trigger time we need to sort them first. After that we go bomb by bomb and count how many minutes it will take to defuse each bomb by counting all bombs below that needs to be defused. As we count the time and increase it with every bomb we should always finish defusing before the trigger time. If not it means the bombs cannot be defused.

# Running time
    Test set 1 (20 pts / 1 s) - 0.0s
    Test set 2 (20 pts / 1 s) - 0.006s
    Test set 3 (20 pts / 1 s) - 0.015s
    Test set 4 (20 pts / 1 s) - 0.138s
