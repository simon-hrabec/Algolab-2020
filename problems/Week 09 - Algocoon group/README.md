# Algocoon group
As well as other problems for this week this one is about graphs and paths/flows. Algocoon is extremely easy in terms of coding, but it compensates for it by requiring deliberate though about the approach to take.
- Modeling the problem
- Counting collisions 
- Constructing the graph

## Min-cut and flows
The problem talks about figures and limbs between them. We are looking for a price of the cheapest cut - note that the problem does not ask for the cut itself. If we knew the division of the two sets (one is figures for me, second for my friend) of the figures then we could pick any pair of figures - each from one set - and the maximum flow between them would be the minimal achievable cutting cost. Note that the maximum flow is not symmetric - the maximum flow between figures A and B does not necessarily equals the one between B and A. Therefore we might assume that both should be checked.

## Finding the proper pair
In the last paragraph I described the idea that we need to find 2 figures that belong to different sets. Since we know both sets are non-empty we can fix one figure and check the max-flows to all other figures. Besides that we also need to check the max-flow in the other directions. We are guaranteed that at least one figure will be in the other set.  This requires 2\*(n-1) calls to the max-flow function.

## Small improvement
Actually it is possible to do even better (not my idea - I read it only from the official solution and I haven't thought about that since even the slower one was passing quite comfortably). The idea is to put the figures in a circle and always check the neighboring figures (in one direction). By this we are guaranteed to find the division. A proof could be written down as follows:

If there exist an optimal division between the 2 sets we are guaranteed to iterate over A-B figures and also B-A figures (A-B meaning the first/source figure is from the first set and the second/target belongs to the second set).

# Running time - slower 2n solution
    Test set 1 (10 pts / 3 s) - 1.203s
    Test set 2 (10 pts / 3 s) - 1.049s
    Test set 3 (20 pts / 3 s) - 0.07s
    Test set 4 (30 pts / 3 s) - 1.159s
    Test set 5 (30 pts / 3 s) - 0.911s

# Running time - faster n solution
    Test set 1 (10 pts / 3 s) - 0.652s
    Test set 2 (10 pts / 3 s) - 0.6s
    Test set 3 (20 pts / 3 s) - 0.04s
    Test set 4 (30 pts / 3 s) - 0.628s
    Test set 5 (30 pts / 3 s) - 0.459s
