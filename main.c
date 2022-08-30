/**
 * main.c
 * 
 * Demonstrates the use of the astar type.
 * 
 * Author: Richard Gale
 * Version: 30th August, 2022
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

    // Connecting the starting node to the graph's central node.
    graph_add_edge(graph_get_node(g, 0, 0, 0), graph_get_node(g, 1, 1, 1), 1);

    // Removing an edge
    graph_remove_edge(graph_get_node(g, 1, 1, 1), graph_get_node(g, 2, 1, 1));

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

    return 0;
}
