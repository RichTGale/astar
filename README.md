# astar
An implementation of the A* (A Star) algorithm in C.

## Some Background:
The A* search algorithm finds the path through a weighted graph that is the shortest or lowest-cost path. A weighted graph is a map made up of various locations that may or may not be connected to one or multiple other locations within the graph. A weight, also known as a cost, is associated with connections betweeen graph locations. This connection is often referred to as an edge and it represents a distance between the two locations. A graph’s locations are typically called nodes or graph-nodes. A path in a graph has a starting node and an ending or goal node. A path may or may not go through multiple nodes before reaching its goal node, depending on whether the starting node and the goal node are connected by an edge. 

At its core, the A* algorithm minimises $f(n) = g(n) + h(n)$ where $g(n)$ is the combined cost of each edge on the path from the starting node to node $n$, and $h(n)$ is an estimate of the minimum total cost for a path to go from node $n$ to the goal node. $f(n)$ then is a value associated with node $n$ that is an estimation of the performance of the path should it go through it, with regard to the path being the lowest-cost path.
