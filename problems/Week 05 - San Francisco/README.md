# San Francisco - solution
San Francisco is a pretty simple problem. The only tricky thing is to properly identify the category to which it belongs and use the right tools. Adding few tweaks can help as well.

 - Is it a graph - is it a graph problem?
 - Repeated relaxation of edges
 - DP table
 - The most embarasing bug
 - Space optimization

## Is it a graph - is it a graph problem?
The problem directly describes a graph - the problem has vertices and (directed) edges. The natural question arrises - should we use some graph algorithm to solve this problem? The problem  in the approaches going in this direction is that we do visit vertices repeatedly.

## Repeated relaxation of edges
When there is no clear choice of algorithm we might think of a simple approach - with each turn we just take each vertex and relax its edges - use it and see what the score will be. For this we would have to, however, remember also the turn, since we could propagate one value multiple times during one turn otherwise.

## DP table
Following this idea we can create a table for each vertex in one dimension and for each turn in the second dimension. As we go turn by turn we use all edges and add the value of the edge to the value from previous turn. Since we might get to a vertex from multiple edges we just pick the highest value among all. Another question is how to represent values for vertices where we cannot get during that turn in any way. One way is to use the minimum value of the used type. We are guaranted that this reprezentation of a non-value will never reach 0 given the constraints.

## The most embarasing bug
This problem has values up to 2^31 (exclusive) - which is the exactly what fits into 32 bit int, but even 2 values summed can go over that. Also the input range of the proposed score goes outside of 32 bits - hence 64 bit integers need to be used. There is nothing worse then thinking about the not working code just to find out that using `int64_t` makes it work. If you wonder it did not happen to me in this particular problem.

## Space optimization
We are always operating on only 2 rows (columns?) of the DP table at once - the current and previous turn. Hence we can only remember these 2. When we finish one turn we swap them and the old will be overriten. The only thing to watch here is that if we use `std::array` the call to `std::swap` will result in real coppies of the whole rows. Resorting to `std::vector` makes the swap a mere jugling with pointers (since we are using at least C++11 with move semantics). This saves space and potentially (i.e. I did not code it up to measure it) could also make the code run faster because the 2 rows could stay in cache with no loading/storing to the main memory.

# Running time
    Test set 1 (20 pts / 0.700 s) - 0.0s
    Test set 2 (05 pts / 0.700 s) - 0.038s
    Test set 3 (40 pts / 0.700 s) - 0.283s
