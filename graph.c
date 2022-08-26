/**
 * graph.c
 * 
 * Data-structure and procedure declarations for
 * a three-dimensional weighted graph. 
 *
 * Author: Richard Gale
 * Version: 26th August, 2022
 */

#include "graph.h"

#define INVALID_COORDINATE_ERROR 1

/**
 * The data contained within the graph data-structure.
 */
struct graph_data {
    node*** nodes;  
    uint16_t x_size;
    uint16_t y_size;
    uint16_t z_size;
    enum graph_styles g_style;
};

/**
 * Returns true if the provided coordinates are within 
 * the bounds of the dimentions of the graph.
 */
bool graph_valid_coord(graph g, int32_t x , int32_t y , int32_t z)
{
    bool is_valid_coord = false;

    if (x >= 0 && x < (int32_t) g->x_size &&
        y >= 0 && y < (int32_t) g->y_size &&
        z >= 0 && z < (int32_t) g->z_size)
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
node* graph_get_node(graph g, uint16_t x, uint16_t y, uint16_t z)
{
    node* n;    // The node at the provided coordinates.

    if (graph_valid_coord(g, (int32_t) x, (int32_t) y, (int32_t) z))
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
 * Adds the provided node's neighbouring nodes to the provided array.
 */
void graph_neighbours(graph* g, node* node, array* neighbours)
{
    int32_t xcoord; // The neighbour's x coordinate.
    int32_t ycoord; // The neighbour's y coordinate.
    int32_t zcoord; // The neighbour's z coordinate.
    int8_t i;       // Coordinate offset
    int8_t x;       // X axis coordinate offset.
    int8_t y;       // Y axis coordinate offset.
    int8_t z;       // Z axis coordinate offset.
    edge* e_ref;    // The edge seperating the node and neighbour

    // Storing manhattan style neighbours.
    if ((*g)->g_style == MANHATTAN)
    {
        for (i = -1; i <= 1; i++)
        {
            xcoord = (int32_t) node_get_x(*node) + (int32_t) i;
            ycoord = (int32_t) node_get_y(*node) + (int32_t) i;
            zcoord = (int32_t) node_get_z(*node) + (int32_t) i;
            
            // X axis neighbours.
            if (graph_valid_coord(*g, xcoord, (int32_t) node_get_y(*node), (int32_t) node_get_z(*node)) &&
                node != graph_get_node(*g, (uint16_t) xcoord, node_get_y(*node), node_get_z(*node)))
            {
                // Adding a valid x axis neighbour.
                edge_init(&e_ref, graph_get_node(*g, (uint16_t) xcoord, node_get_y(*node), node_get_z(*node)), 1);
                array_push_back(neighbours, e_ref);
            }
            // Y axis neighbours.
            if (graph_valid_coord(*g, (int32_t) node_get_x(*node), ycoord, (int32_t) node_get_z(*node)) &&
                node != graph_get_node(*g, node_get_x(*node), (uint16_t) ycoord, node_get_z(*node)))
            {
                // Adding a valid y axis neighbour.
                edge_init(&e_ref, graph_get_node(*g, node_get_x(*node), (uint16_t) ycoord, node_get_z(*node)), 1);
                array_push_back(neighbours, e_ref);
            }
            // Z axis neighbours.
            if (graph_valid_coord(*g, (int32_t) node_get_x(*node), (int32_t) node_get_y(*node), zcoord) &&
                node != graph_get_node(*g, node_get_x(*node), node_get_y(*node), (uint16_t) zcoord))
            {
                // Adding a valid z axis neighbour.
                edge_init(&e_ref, graph_get_node(*g, node_get_x(*node), node_get_y(*node), (uint16_t) zcoord), 1);
                array_push_back(neighbours, e_ref);
            }
        }
    } 
    // Storing diagonal style neighbours
    else if ((*g)->g_style == DIAGONAL)
    {
        for (x = -1; x <= 1; x++)
        {
            xcoord = (int32_t) node_get_x(*node) + (int32_t) x;
            for (y = -1; y <= 1; y++)
            {
                ycoord = (int32_t) node_get_y(*node) + (int32_t) y;
                for (z = -1; z <= 1; z++)
                {
                    zcoord = (int32_t) node_get_z(*node) + (int32_t) z;
                    if (graph_valid_coord(*g, xcoord, ycoord, zcoord) &&
                        node != graph_get_node(*g, (uint16_t) xcoord, (uint16_t) ycoord, (uint16_t) zcoord))
                    {
                        // Adding a valid neighbour.
                        edge_init(&e_ref, graph_get_node(*g, (uint16_t) xcoord, (uint16_t) ycoord, (uint16_t) zcoord), 1);
                        array_push_back(neighbours, e_ref);
                    }
                }
            }
        }
    } 
}

/**
 * Initialises the graph.
 */
void graph_init(graph* g_ref, 
                uint16_t x_size, 
                uint16_t y_size, 
                uint16_t z_size, 
                enum graph_styles g_style)
{
    uint16_t x; // Current x coordinate
    uint16_t y; // Current y coordinate
    uint16_t z; // Current z coordinate
    

    // Allocating memory for the graph
    *g_ref = (graph) malloc(sizeof(struct graph_data));
    
    // Initialising graph nodes
    (*g_ref)->nodes = (node***) malloc(x_size * sizeof(node**));
    for (x = 0; x < x_size; x++)
    {
        (*g_ref)->nodes[x] = (node**) malloc(y_size * sizeof(node*));
        for (y = 0; y < y_size; y++)
        {
            (*g_ref)->nodes[x][y] = (node*) malloc(z_size * sizeof(node));
            for (z = 0; z < z_size; z++)
            {
                node_init(&(*g_ref)->nodes[x][y][z], 
                            x, 
                            y, 
                            z);
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

    // Initialising graph nodes
    for (x = 0; x < x_size; x++)
    {
        for (y = 0; y < y_size; y++)
        {
            for (z = 0; z < z_size; z++)
            {
                graph_neighbours(g_ref, 
                                    &(*g_ref)->nodes[x][y][z], 
                                    node_get_edges(&(*g_ref)->nodes[x][y][z]));
            }
        }
    }
}

/**
 * Frees the memory allocated to the graph.
 */
void graph_free(graph* g_ref)
{
    uint16_t x; // Current x coordinate
    uint16_t y; // Current y coordinate
    uint16_t z; // Current z coordinate

    // Freeing the nodes
    for (x = 0; x < (*g_ref)->x_size; x++)
    {
        for (y = 0; y < (*g_ref)->y_size; y++)
        {
            for (z = 0; z < (*g_ref)->z_size; z++)
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
 * Adds a connection from one graph node to another, considering 
 * it as a neighbour.
 * Note, this creates a one-way connection.
 */
void  graph_connect_node(node* node_a, node* node_b, uint8_t weight)
{
    node_add_edge(node_a, node_b, weight);
}

/**
 * Disconnects one graph node from another, stopping
 * them from considered neighbours.
 * Note, this is a one-way disconnection.
 */
void graph_disconnect_node(node* node_a, node* node_b) 
{
    node_remove_edge(node_a, node_b);
}


/**
 * Returns the graph's graph_style.
 */
enum graph_styles graph_get_style(graph g)
{
    return g->g_style;
}

/**
 * Prints the graph.
 */
void graph_print(graph g)
{
    uint16_t x; // Current x coordinate
    uint16_t y; // Current y coordinate
    uint16_t z; // Current z coordinate

    printf("Graph:\n{\n");
    for (x = 0; x < g->x_size; x++)
    {
        printf("\t{\n");
        for (y = 0; y < g->y_size; y++)
        {
            printf("\t\t{\n");
            for (z = 0; z < g->z_size; z++)
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