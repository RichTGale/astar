/**
 * graph.c
 * 
 * Data-structure and procedure declarations for
 * a three-dimensional graph or map. Typically used
 * within a search algorithm.
 *
 * Author: Richard Gale
 * Version: 17th August, 2022
 */

#include "graph.h"

#define INVALID_COORDINATE_ERROR 1

/**
 * The data contained within the graph data-structure.
 */
struct graph_data {
    node*** nodes;
    enum graph_styles g_style;
    int x_size;
    int y_size;
    int z_size;
};

/**
 * Initialises the graph.
 */
void graph_init(graph* g_ref, 
                int x_size, int y_size, int z_size, 
                int* weights,
                enum graph_styles g_style)
{
    // Allocating memory for the graph
    *g_ref = (graph) malloc(sizeof(struct graph_data));
    
    // Initialising graph nodes
    (*g_ref)->nodes = (node***) malloc(x_size * sizeof(node**));
    for (int x = 0; x < x_size; x++)
    {
        (*g_ref)->nodes[x] = (node**) malloc(y_size * sizeof(node*));
        for (int y = 0; y < y_size; y++)
        {
            (*g_ref)->nodes[x][y] = (node*) malloc(z_size * sizeof(node));
            for (int z = 0; z < z_size; z++)
            {
                node_init(&(*g_ref)->nodes[x][y][z], 
                            x, 
                            y, 
                            z, 
                            weights[(x * y_size + y) * z_size + z]);
            }
        }
    }

    // Storing the graph dimensions
    (*g_ref)->x_size = x_size;
    (*g_ref)->y_size = y_size;
    (*g_ref)->z_size = z_size;

    // Setting the way in which graph-nodes will be considered
    // neighbours of other graph-nodes
    (*g_ref)->g_style = g_style;
}

/**
 * Frees the memory allocated to the graph.
 */
void graph_free(graph* g_ref)
{
    // Freeing the nodes
    for (int x = 0; x < (*g_ref)->x_size; x++)
    {
        for (int y = 0; y < (*g_ref)->y_size; y++)
        {
            for (int z = 0; z < (*g_ref)->z_size; z++)
            {
                node_free(&(*g_ref)->nodes[x][y][z]);
            }
            free((*g_ref)->nodes[x][y]);
        }
        free((*g_ref)->nodes[x]);
    }
    free((*g_ref)->nodes);

    // Freeing the graph
    free(*g_ref);
}

/**
 * Returns true if the provided coordinates are within 
 * the bounds of the dimentions of the graph.
 */
bool graph_valid_coord(graph g, int x , int y , int z)
{
    bool is_valid_coord = false;

    if (x >= 0 && x < g->x_size &&
        y >= 0 && y < g->y_size &&
        z >= 0 && z < g->z_size)
    {
        // The provided coordinates are withn the bounds 
        // of the dimensions graph.
        is_valid_coord = true;
    }
    return is_valid_coord;
}

/**
 * Returns a reference to the node in the graph at 
 * the provided x, y, z coordinates.
 */
node* graph_get_node(graph g, int x, int y, int z)
{
    node* n;    // The node at the provided coordinates.

    if (graph_valid_coord(g, x, y, z))
    {
        // The provided coordinates are valid so we can
        // proceed to getting the node.
        n = &(g->nodes[x][y][z]);
    }
    else
    {
        // The provided coordinates are not valid coordinates
        // so we're going to print an error message and exit.
        printf("\nERROR: In function graph_get_node(): "
                "Invalid node coordinates: { %d, %d, %d }!\n", x, y, z);
        exit(INVALID_COORDINATE_ERROR);
    }

    // Returning the node reference
    return n;
}

/**
 * Returns the graph's graph_style.
 */
enum graph_styles graph_get_style(graph g)
{
    return g->g_style;
}

/**
 * Adds the provided node's neighbouring nodes to the provided array.
 */
void graph_neighbours(graph* g, node* node, array* neighbours)
{
    int xcoord; // The neighbour's x coordinate.
    int ycoord; // The neighbour's y coordinate.
    int zcoord; // The neighbour's z coordinate.

    // Storing manhattan style neighbours.
    if ((*g)->g_style == MANHATTAN)
    {
        for (int i = -1; i <= 1; i++)
        {
            xcoord = node_get_x(*node) + i;
            ycoord = node_get_y(*node) + i;
            zcoord = node_get_z(*node) + i;
            
            // X axis neighbours.
            if (graph_valid_coord(*g, xcoord, node_get_y(*node), node_get_z(*node)) &&
                node != graph_get_node(*g, xcoord, node_get_y(*node), node_get_z(*node)))
            {
                array_push_back(neighbours, 
                                graph_get_node(*g, xcoord, node_get_y(*node), node_get_z(*node)));
            }
            // Y axis neighbours.
            if (graph_valid_coord(*g, node_get_x(*node), ycoord, node_get_z(*node)) &&
                node != graph_get_node(*g, node_get_x(*node), ycoord, node_get_z(*node)))
            {
                array_push_back(neighbours, 
                                graph_get_node(*g, node_get_x(*node), ycoord, node_get_z(*node)));
            }
            // Z axis neighbours.
            if (graph_valid_coord(*g, node_get_x(*node), node_get_y(*node), zcoord) &&
                node != graph_get_node(*g, node_get_x(*node), node_get_y(*node), zcoord))
            {
                array_push_back(neighbours, 
                                graph_get_node(*g, node_get_x(*node), node_get_y(*node), zcoord));
            }
        }
    } 
    // Storing diagonal style neighbours
    else if ((*g)->g_style == DIAGONAL)
    {
        for (int x = -1; x <= 1; x++)
        {
            xcoord = node_get_x(*node) + x;
            for (int y = -1; y <= 1; y++)
            {
                ycoord = node_get_y(*node) + y;
                for (int z = -1; z <= 1; z++)
                {
                    zcoord = node_get_z(*node) + z;
                    if (graph_valid_coord(*g, xcoord, ycoord, zcoord) &&
                        node != graph_get_node(*g, xcoord, ycoord, zcoord))
                    {
                        // Adding the neighbouring node to the array
                        array_push_back(neighbours, 
                                        graph_get_node(*g, xcoord, ycoord, zcoord));
                    }
                }
            }
        }
    } 
}

/**
 * Prints the graph.
 */
void graph_print(graph g)
{
    printf("Graph:\n{\n");
    for (int x = 0; x < g->x_size; x++)
    {
        printf("\t{\n");
        for (int y = 0; y < g->y_size; y++)
        {
            printf("\t\t{\n");
            for (int z = 0; z < g->z_size; z++)
            {
                // Printing the current node.
                printf("\t\t\t");
                node_print(g->nodes[x][y][z]);
                if (z < g->z_size - 1)
                {
                    printf(",");
                }
                printf("\n");
            }
            printf("\t\t}");
            if (y < g->y_size - 1)
            {
                printf(",");
            }
            printf("\n");
        }
        printf("\t}");
        if (x < g->x_size - 1)
        {
            printf(",");
        }
        printf("\n");
    }
    printf("}\n");
}