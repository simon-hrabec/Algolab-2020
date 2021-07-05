# Inball - solution
If you dislike problems related to geometry or linear programming then this is the problem for you ^^. Despite this scary statement there is nothing too complicated about this problem. We are given nice guarantees (the norm being an integer) when thinking about the solution it is easy to verify it does what it should and also a triangle and circle is easy to visualize.
- Provided solution
- Finding point inside triangle
- Maximizing the sphere radius

## Provided solution
Inball is one of the problems that has reference solution with full explanation (ETH/Algolab Moodle). Since there is math involved and 2D geometry this explanation (textual only) cannot compete with the reference one with pictures and LaTeX equations and therefore (not only) due to the format limitations is inferior. However if you are not an ETH student and do not have access then I hope this can shed some light on how to approach it.

## Finding point inside triangle
We are given several equations in n-dimensional space that define (possibly empty) subspace. It is therefore natural to formulate this problem using LP. A good way to start with this problem is to set the equations and check if the specified space is empty (the cases with expected output "none").

## Maximizing the sphere radius
We are given N lines (D-1 dimensional planes to be exact). Good initial observation is that fitting the ball with radius R into the cave is equivalent to shifting the planes (restricting the half spaces) by R and having non-empty cave. We could use binary search to find this value. But we are using LP, which is made to optimize parameters of linear programs. Therefore we can just introduce an additional parameter to each equation that we will substract and we will try to maximize this number. However a problem arises - we need to scale the number we substract from each equation differently. An easy example - having `X+Y<1` and `2X+2Y<2` constitutes the same condition. Here comes back the initial statement that the norm of the an integer. Also the example is quite useful with the line `3 4 12` representing the equation `3X+4X<12`.  It is 12 units far from the origin, but 12/5, where 5 is the norm (square root of the sums of squares). Therefore the norm is the proper scaling factor. It can also be interpreted as the length of the normal vector.

# Running time
    Test set 1 (35 pts / 2 s) - 0.011s
    Test set 2 (35 pts / 2 s) - 0.101s
    Test set 3 (30 pts / 2 s) - 0.863s
