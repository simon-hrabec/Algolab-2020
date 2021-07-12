# Lestrade - solution
Lestrade is a problem that is not so hard in implementation, but it requires a combination of algorithms/techniques to be solved. Before creating the solution, it is useful to read the description properly. We can make several (important) conclusions. Every agent can spy on 1 gang member only. It makes no sense for a gang member to be interrogated by multiple agents. Only the cheapest agent should be used. Agents that are not the cheapest for some gang member should not be used. Gang members that are not the closest for any agent cannot be interrogated. There is fewer agents than gang members. Given the restricted conditions and input we can now formute the problem as a linear program.

Solution explanation:
- Finding the closest gang member
- Finding the cheapest agent
- LP formulation

## Finding the closest gang member
We have upper bounds 4000 on the number of agents and 90000 on the number of gang members. In this case it will be efficient to take advantage of `CGAL::Delaunay_triangulation_2` and its method `nearest_vertex`. We construct triangulation using the gang members and do the query for each agent.

## Finding the cheapest agent
As discused above it is clear that if gang member has (if any) agents for which he is the nearest gang member we should consider only the cheapest agent (agent demanding the smallest wage). For this we can use `std::unordered_map<int, int>` to remember gang member id and the smallest wage of admissible agent.

## LP formulation
We are now given a subset of agents and gang members. Each gang member can be iterrogated an arbitrary number of hours between 0-24. We want to reach our condition and strive for the cheapest price. This sounds very much like a linear program and indeed we can formulate the problem using LP. We create 3 equations (for the 3 components - where, whom, how) but for each agent we add one variable to each (and as well one variable to the optimization criteria). The right side of the equations are the required where, whom and how components. If the linear program does not have a solution or the optimal solution is bigger than the proposed fee for hiring Holmes we have to go with Holmes.

# Running time
    Test set 1 (35 pts / 1 s) - 0.292s
    Test set 2 (35 pts / 1 s) - 0.745s
    Test set 3 (30 pts / 3 s) - 2.785s
