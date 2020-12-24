# Evolution - solution
This problem requires a lot of data structures, out of order computation of the queries, and DFS on the graph. There is no clear approach. There is a lot of options but most them under scrutiny show degradation to N^2 worst case. The shown solution includes the following steps/techniques:

- Translation of names to indices
- Modeling the problem
- Building the graph
- Storage of queries
- Binary search execution of query
- Construction of the binary search array
- Storage of results

## Translation of names to indices
In this problem we are given names of the species, not integer indices. The easiest way to start with solving this problem is to forget about any string names and operate fully only with integer indices. We can do this by a translation table (hashmap - `std::unordered_map<string, int>`) and array of strings to be able to do to inverse operation - get name from index. As we get the names we insert them into the hashmap and the array.

## Modeling the problem
We are basically given a rooted tree with unspecified shape (it can be a degenerative form of just a sequential list or it can be a tree with most of the nodes being leaves). Therefore building a compete array of predecessors (for binary search) for each leave can be in worst case O(N^2) and doing a simple traversal for each query can be also O(Q*N). The trick is to to indeed construct an array of predecessors for each node for binary search, but not all at once, but construct it iteratively during a graph traversal and "run" the queries at the same time.

## Building the graph
In this case we stick with directed graph pointing from parent to children. We use adjacency list to be able to easily run DFS.

## Storage of queries
Rather than doing first all precomputation and then executing all queries we store the queries first. For each node we store all its queries for later use.

## Binary search execution of query (idea)
Assume we have some node and its queries. We also have all of its processors (their age) stored and sorted in an array. We can then do binary search for all the queries to get the result in a logarithmic time.

## Construction of the binary search array
The main question in this problem is how to avoid building the array multiple times. The answer is to build it iteratively. Traverse the graph using DFS and construct this array as we go. As we go deeper we add elements to the array and when we finish we again remove them (basically have the DFS call stack to correspond to the binary search array). By this we add total N elements to the array over time and do N DFS iterations. Each query is then performed by a fast (O(log n)) binary search.

## Storage of results
Since we stored all the queries and execute/calculate them in different order (as we traverse the tree using DFS) we also need to store the results. Once we calculate all of them we print them in the right order.

# Additional ideas
DFS is performed using implicit call stack. Should the graph be a sequential list with big depth we could run out of stack memory and have stack overflow. Using explicig stack would mitigate this problem.

# Running time
    Test set 1 (30 pts / 2 s) - 0.01s
    Test set 2 (70 pts / 2 s) - 0.458s
