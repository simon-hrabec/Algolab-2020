# The Iron Islands - solution
This problem is rather easy. After initial analysis and breaking the problem into 2 subcases it is just a little bit of quite straightforward coding using quite well know concepts. The explanation of the solution is split into the following chapters:
- Viable cases
- Single waterway
- Combining 2 waterways

## Viable cases
The description is a bit lengthy, but it basically says that the graph is a set of n lines (waterways) joined by one vertex into a star shaped graph and a solution is any path on which the nodes sum to the given number (number of man). Important thing to notice is that the number of required men is always a positive number. An easy way to handle this problem is to identify that the solutions are of 2 types. Either the solution lies within on waterway (possible including the middle/shared node) or it combined out 2 waterways or their parts.

## Single waterway
We are looking for (all) continuous subarrays on the waterway array that sum to the giver number. Since all entries are positive integers we can use the 2 pointers approach. One pointer to indicate the start of the subarray and the second for its end. When the sum of the subarray is smaller than the given number we move the start pointer to include more elements and enlarge the sum. If we reach the given number (or go over it) we shrink the array by moving the end pointer and consequently reduce the sum. By this we find all continuous subarrays which sum to the given number. We remember the shortest length of all such subarrays.

## Combining 2 waterways
The second case is that we combine 2 waterways - more specifically their parts that start in the middle (to get the V shaped path). Instead of trying all the pairs of island on different waterways we use a hashmap and remember all previously seen parts of waterways - more specifically for the number of men required to conquer the part of the waterway we remember the maximum possible number of islands. We take waterways one by one - start with the middle node and then include more nodes from the waterway. With each additionally added node we do a lookup for the complement to the current sum and we remember the maximum possible number of islands to conquer. After processing each waterway (we can also terminate when the sum reaches the given number) we add the entries into the hashmap.

# Running time
    Test set 1 (20 pts / 2 s) - 0.437s
    Test set 2 (20 pts / 2 s) - 0.495s
    Test set 3 (20 pts / 2 s) - 0.525s
