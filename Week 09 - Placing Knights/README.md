# Placing Knights
This problem is not difficult in terms of coding (unlike "Attack of the Clones"), however it does not have a straightforward solution. Therefore it is necessary to brainstorm and try different techniques/approaches. 
- Modeling the problem
- Counting collisions 
- Constructing the graph

## Modeling the problem
When thinking about how to approach the problem, one might remember that the recent topics in the course were graphs and flows, therefore it might be logical to try it first. Looking at the input dimension we see that the size of the chessboard is at most 2^6=64 and the number of fields will be 2^12=4096, which is might be feasible for some types of graphs. Another important observation to make is that knights on black fields can collide on with knights on white fields and vice versa.

## Counting collisions 
Sadly, we cannot use the flow information to count the possible number of knights to place on the board. But we could go the other way around and calculate the number of knight that cannot be placed on the board due to collisions. And then just taking the number of valid fields (no hole) and substract the collisions.

## Constructing the graph
Since we are looking for black-white collision we are going to have only edges between black fields and white fields. To decide what connect to source and target - either one will be connected to source and the other to target. We omit the fields that are not present on the board (holes). Then we create all the edges between the black and white fields. Each fields will have an edge to its 8 possible move positions. Of course we need to ignore move outside of the chessboard. Also we don't want to create the edges twice so we create it only for white fields or only for black fields.

## Implementation notes
As common with graph problems (when solving with BGL) we need to put find out how to take the fields on the board and map them to a single index. For simplicity I use graph of twice the require size, just to keep it simple with indexing. However, the the white fields are not used in the first half and the black fields are not used in the second half. This could be avoided.

# Running time
    Test set 1 (30 pts / 1 s) - 0.001s
    Test set 2 (35 pts / 1 s) - 0.088s
    Test set 3 (35 pts / 1 s) - 0.241s
