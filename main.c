/**
 * main.c
 * 
 * Demonstrates the use of an A* (A Star) search algorithm
 * implementation.
 * 
 * Author: Richard Gale
 * Version: 16th August, 2022
 */

#include <stdio.h>

#include "node.h"
#include "graph.h"
#include "astar.h"

int main(int argc, char* argv[])
{
    astar as;   // The astar.
    graph g;    // The graph.
    int weights[3][3][3] = {    // The weights of the nodes in the graph.
        {
            {1, 3, 3},
            {3, 3, 3},
            {3, 3, 3}
        },
        {
            {1, 3, 3},
            {3, 3, 3},
            {3, 3, 3}
        },
        {
            {1, 3, 3},
            {1, 3, 3},
            {1, 1, 1}
        }
    };

    // Initialising and printing the graph.
    graph_init(&g, 3, 3, 3, weights, MANHATTAN);
    graph_print(g);

    // Initialising the astar.
    astar_init(&as, &g);

    // Finding the shortest path.
    astar_search(&as, graph_get_node(g, 0,0,0), graph_get_node(g, 2,2,2));

    // Printing the nodes that make up the shortest path.
    printf("SHORTEST PATH:\n");
    for (int i = 0; i < array_size(astar_get_path(as)); i++)
    {
        node_print(*((node*) array_get_data(astar_get_path(as), i)));
        printf("\n");
    }

    // Freeing memory
    astar_free(&as);
    graph_free(&g);

    return 0;
}
