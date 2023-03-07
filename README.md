# astar
An implementation of the A* (A Star) algorithm in C.

## Setup
Source files are in the $src/$ directory. You can take them and do what you like with them. Or you can install cmake and run $sh install.sh$ in a terminal from within the base directory called $astar/$, then $sh run.sh$ to see it work.

## Some Background:
The A* search algorithm finds the path through a weighted graph that is the shortest or lowest-cost path. A weighted graph is a map made up of various locations that may or may not be connected to one or multiple other locations within the graph. A weight, also known as a cost, is associated with connections between graph locations and represents a distance between the locations. This connection is often referred to as an edge. A graph’s locations are typically called nodes or graph-nodes. A path in a graph has a starting node and an ending or goal node. A path may or may not reach its goal node depending on whether or not the goal node is connected by at least an edge, or a series of nodes and edges, to the starting node. 

The A* algorithm selects the path that minimises $f(n) = g(n) + h(n)$ where $n$ is the next node on the path, $g(n)$ is the combined cost of each edge on the path from the starting node to node $n$, and $h(n)$ is an estimate of the minimum total cost for a path to go from node $n$ to the goal node. $f(n)$ then is an estimation of the total cost of the path should the path go through node $n$ and eventually reach the goal node.
