# Hand - solution
In this problem it is crucial to fully understand the problem description first before attempting to solve it. Most important piece of information is that each tent **has** to be assigned to a family. This idea is important for our idea of clustering. We take some distance D and if 2 tents are closer than D they are in the same cluster and must be given to the same family. This relation is transitive (it is actually an equivalence relation) so the whole set of tents will be divided into clusters that must be assigned to the same family. If a tent could be left unassigned this would not hold.
We are given 2 queries where we operate with some distance (either given or as a result) and all edges with smaller distance will be merged (2 tents will belong to the same cluster) which implies a usage of union-find data structure. We are given an upper bound on the number of tents/vertices 9*10^4. This number is too high to proceed with taking all pairs (which is O(N^2)). Here we can utilize Delaunay triangulation and consider only edges from the triangulation. The description of the solution is divided into the following chapters:

- Tracking clusters and their sizes
- Maximum families from clusters
- First query
- Second query
- Calculating both queries at once

## Tracking clusters and their sizes
It is convenient as we proceed to know the number of cluster and their sizes. Since one family needs at most 4 tents, a cluster of size 5 or more provides the same utility as a cluster of size 4. Therefore, we can track any cluster of size of 4 or higher as size 4. We can then store the number of clusters of size 1, 2, 3, and 4 in an array (4 integers). When we merge two clusters we modify these counters accordingly.

## Maximum families from clusters
We have already explained the reasons why 1 cluster can be assigned to only 1 family. However, it is possible to assign multiple clusters to one family. Given the counters of clusters we can calculate what is the maximum possible number of families to accommodate. Fortunately we are given a constraint that the number of required tents for a single family is between 1-4. Each case requires a slightly different calculation - for 1 just sum all the counters, for 2 just sum all of them and divide clusters of one by 2 (for 3 and 4 refer to the attached code). All of these calculation area cheap and can be done in constant time.

## First query
In the first query we are given number N and are tasked to provide the maximum (squared) distance such that we are still able to accommodate N families. We can take edges from the Delaunay triangulation, sort them, and start merging the clusters starting from the smallest edge. In each step we check how many families we can still accommodate. Once we drop below N we take the squared length of the edge. This is due to the definition of the problem - non-strict inequality. The tents need to be at least S apart, so S is still fine.

## Second query
In the second query we are given number D and are tasked to provide the maximum number of families to accommodate such that tents of different families are at least D (squared) apart. We can just iterate over the edges and and merge all clusters that are less than D (squared) apart. Then we just calculate the number of families from the cluster counts.

## Calculating both queries at once
Both queries require steps that are shared between both of them, more specifically - iterating over edges and merging clusters. We could therefore do this only once and get the results for both queries during that for a small speedup. There are two version of the code. The first [solution](https://github.com/simon-hrabec/Algolab2020/blob/main/Week%2011%20-%20Hand/hand-2-queries.cpp) has the 2 queries separated, which requires more code but is easily readable. The second [solution](https://github.com/simon-hrabec/Algolab2020/blob/main/Week%2011%20-%20Hand/hand-one-loop.cpp) has just once loop but the two queries and their conditions are intertwined.

# Running time
    Test set 1 (25 pts / 4 s) - 0.013s
    Test set 2 (25 pts / 4 s) - 0.363s
    Test set 3 (25 pts / 4 s) - 0.314s
    Test set 4 (25 pts / 4 s) - 0.24s
