# Important Bridges - solution
Week 4 is the week of BGL. This is one of the problems to make people more familiar with BGL and its various parts. Even though this problem could be coded from scratch it is expected to take advantage of BGL and its algorithms.
- Biconnected components
- Counting edges
- Implementation notes

## Biconnected components
In the first presentation about BGL there is a list of useful algorithms at the end. You might examine all of them and when looking at the biconnected components you might stumble upon the following picture on the respective [wikipedia page](https://en.wikipedia.org/wiki/Biconnected_component).
![enter image description here](https://upload.wikimedia.org/wikipedia/commons/thumb/6/66/Graph-Biconnected-Components.svg/220px-Graph-Biconnected-Components.svg.png)
Here you might get the idea that the important bridge (in graph terminology it is simply bridge or cut-edge) is an edge that creates a single biconnected component. By other words each biconnected component that contains only one edge is (its only edge) the important bridge.

## Counting edges
Now it only takes to transform the idea into concrete implementation. We need to iterate over edges and see to what component do they belong and increment the respective counter. Then we can iterate again and store only the edges in components of size 1. It is also required to sort them first before printing.

## Implementation notes
My implementation is quite straightforward, but it raises the question whether it is necessary to iterate over all the edges twice. It is not. We could store the information about the edge as we find a new component and invalidate the component once we find another edge. Also a hashmap (`std::unordered_map`) might not be necessary.

# Running time
    Test set 1 (40 pts / 2 s) - 0.005s
    Test set 2 (40 pts / 2 s) - 0.409s
    Test set 3 (20 pts / 2 s) - 0.0s
