# Surveillance Photograph - solution
This is a pretty problem. In the description we are told about a network of one way streets and asked to provide the maximum number of photographs possible to be delivered with certain conditions met. This is a clear description of a graph and a flow problem. However, the condition to use a street at most once when coming back to the station makes it a bit tricky. The trick to use here is a simple graph duplication. We consider the way to the photograph and back independently.

Solution explanation:
- Duplicating the graph
- Edges in the graph
- Max flow

## Duplicating the graph
After thinking about the problem for a while we see we are having two parts of the problem - the first is a policeman reaching the photograph. Here we have no restriction on how many times the path can be used. However, on the way back (to some station, not necessarly the same one) it can be used only once. Hence, we create the graph twice, one instance of the graph for each subproblem.

## Edges in the graph
Having twice the vertices it is now important to correctly decide what edges to build. First we consider the edges representing streets. In the first part of the graph we can give them infinite capacity (pseudo infinity - number of police stations will in this case suffice). In the later case we set capacity only to 1 (only a single policeman can use it). We also need a source wertex connected to all police stations in the first graph (capacity 1) and sink/target vertex and having all police stations connected from the second part to it (also capacity 1). Now we need to think how to connect the two parts. The transition happens when a policeman (or a policewoman?) takes the photograph. Hence, we create an edge of capacity 1 for each photograph node from the first part to the second part.

## Max flow
After constructing the graph in this manner the maximum flow in the graph is equal to the maximum number of photographs that can be captured with the conditions that only 1 policeman will end up at a police station and the streets taken back to a station will be used just once. Hence, a call to a max flow algorithm `boost::push_relabel_max_flow` will give us the result.

# Running time
    Test set 1 (40 pts / 1.500 s) - 0.155s
    Test set 2 (40 pts / 1.500 s) - 0.247s
