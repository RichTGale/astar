/**
 * main.c
 * 
 * Demonstrates the use of the astar type.
 * 
 * Author: Richard Gale
 * Version: 17th August, 2022
 */

#include <stdio.h>
#include <stdlib.h> // Testing

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
    
    // TODO: Add procedures to the array type so that it is a lot
    // easier to create muiltidimensional arrays, then modify
    // graph_init() so that it takes that custom array data type so
    // we can assert that the defined dimensions of the graph are the
    // same as the dimentions of the array of weights.
    //
    // At the moment it is easy to pass a weight array to
    // graph_init() that has different dimensions to what the graph gets
    // given, and it isn't currently possible to check the dimensions
    // of the array within graph_init() with the weight array as it currently
    // is, as far as I know.

    // Initialising and printing the graph.
    graph_init(&g, 3, 3, 3, weights, MANHATTAN);
    graph_print(g);

    // Initialising the astar.
    astar_init(&as, &g);

    // Finding the shortest path.
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
