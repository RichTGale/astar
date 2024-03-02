/**
 * main.c
 * 
 * This file demonstrates the use of the astar type.
 * 
 * Astar version: 1.0.0
 * File version: 1.0.1
 * Author: Richard Gale
 */

#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "node.h"
#include "graph.h"
#include "astar.h"

int main(int argc, char* argv[])
{
    astar as;       /* The astar. */
    graph g;        /* The graph. */
    node* start;    /* The start node. */
    node* goal;     /* The goal node. */
    array path;     /* The shortest path. */
    node n;         /* The current node on the path. */

    /* Initialise and print the graph. */
    graph_init(&g, 10, 10, 10, MANHATTAN);
    graph_print(g);

    /* Set the start and goal nodes. */
    start = graph_get_node(g, 0, 0, 0);
    goal  = graph_get_node(g, 9, 9, 9);

    /* Initialise the astar. */
    astar_init(&as, &g);

    /* Finding the shortest path. */
    printf("Searching for the shortest path...\n");
    astar_search(&as, start, goal);

    /* Get the shortest path. */
    path = astar_get_path(as);

    /* Print the nodes that make up the shortest path. */
    printf("SHORTEST PATH:\n");
    for (int i = 0; i < array_size(path); i++)
    {
        n = *((node*) array_get_data(path, i)); /* Get the current node. */
        node_print(n);                          /* Print the current node. */
        printf("\n");
    }

    /* Destroy Structures. */
    astar_free(&as);
    graph_free(&g);

    /* Exit the program */
    exit(EXIT_SUCCESS);
}
