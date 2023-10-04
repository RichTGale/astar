/**
 * main.c
 * 
 * Demonstrates the use of the astar type.
 * 
 * Author: Richard Gale
 * Version: 1.0.0
 */

#include <stdio.h>

#include "array.h"
#include "node.h"
#include "graph.h"
#include "astar.h"

int main(int argc, char* argv[])
{
    astar as;   // The astar.
    graph g;    // The graph.

    // Initialising and printing the graph.
    graph_init(&g, 3, 3, 3, MANHATTAN);
    graph_print(g);

    // Initialising the astar.
    astar_init(&as, &g);

    // Finding the shortest path.
    printf("Searching for the shortest path...\n");
    astar_search(&as, graph_get_node(g, 0, 0, 0), graph_get_node(g, 2, 2, 2));

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

    // Exiting the program
    return 0;
}
