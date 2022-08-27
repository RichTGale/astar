/**
 * graph.c
 * 
 * Data-structure and procedure declarations for
 * a three-dimensional weighted graph. 
 *
 * Author: Richard Gale
 * Version: 28th August, 2022
 */

#include "graph.h"

#define INVALID_COORDINATE_ERROR 1

/**
 * The data contained within the graph data-structure.
 */
struct graph_data {
    node*** nodes;      // The nodes that make up the graph.
    uint16_t x_size;    // The size of the x axis.
    uint16_t y_size;    // The size of the y axis.
    uint16_t z_size;    // The size of the z axis.

    // The way in which a graph-node will be considered a 
    // neighbour of another graph-node.
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
 * Returns true if the relationship between the provided offsets is
 * consistent with that of manhattan neighbours.
 */
bool manhattan_relationship(int8_t xoffset, int8_t yoffset, 
                                                            int8_t zoffset)
{
    bool is_manhattan; // Whether the relationship is manhattan.

    if ((xoffset == 0 && yoffset == 0 && zoffset == 1) ||
        (xoffset == 0 && yoffset == 1 && zoffset == 0) ||
        (xoffset == 1 && yoffset == 0 && zoffset == 0))
    {
        is_manhattan = true; // The relationship is manhattan.
    }

    return is_manhattan;
}

/**
 * Returns true if the relationship between the provided offsets is
 * consistent with that of diagonal neighbours.
 */
bool diagonal_relationship(int8_t xoffset, int8_t yoffset, int8_t zoffset)
{
    bool is_diagonal; // Whether the relationship is diagonal.

    if ((manhattan_relationship(xoffset, yoffset, zoffset)) ||
        ((xoffset == 1 && yoffset == 1 && zoffset != 0) ||
         (xoffset == 1 && yoffset == 0 && zoffset != 1) ||
         (xoffset == 0 && yoffset == 1 && zoffset != 1)))
    {
        is_diagonal = DIAGONAL; // There is a diagonal relationship.
    }

    return is_diagonal;
}

bool graph_init_node_edges(graph* g_ref, node* n_ref)
{
    array neighbours;   // The neighbouring nodes of the provided node.
    node* neighbour;    // A node neighbouring the provided node.
    int8_t xoffset;     // X axis coordinate offset.
    int8_t yoffset;     // Y axis coordinate offset.
    int8_t zoffset;     // Z axis coordinate offset.
    int32_t xcoord;     // The neighbour's x coordinate.
    int32_t ycoord;     // The neighbour's y coordinate.
    int32_t zcoord;     // The neighbour's z coordinate.

    // Preparing the array of neighbours for use.
    array_init(&neighbours);

    // Collecting the neighbours of the provided node.
    for (xoffset = -1; xoffset <= 1; xoffset++)
    {
        for (yoffset = -1; yoffset <= 1; yoffset++)
        {
            for (zoffset = -1; zoffset <= 1; zoffset++)
            {
                if ((*g_ref)->g_style == MANHATTAN &&
                    manhattan_relationship(xoffset, yoffset, zoffset))
                {
                    // Determining whether these coordinates are valid
                    // graph coordinates
                    xcoord = (int32_t) node_get_x(*n_ref) + (int32_t) xoffset;
                    ycoord = (int32_t) node_get_y(*n_ref) + (int32_t) yoffset;
                    zcoord = (int32_t) node_get_z(*n_ref) + (int32_t) zoffset;
                    if (graph_valid_coord(*g_ref, xcoord, ycoord, zcoord))
                    {
                        // Adding this neighbour to the array of neighbours.
                        neighbour = graph_get_node(*g_ref, (uint16_t) xcoord, 
                                        (uint16_t) ycoord, (uint16_t) zcoord);
                        array_push_back(&neighbours, neighbour); 
                    }
                }
                else if ((*g_ref)->g_style == DIAGONAL &&
                    diagonal_relationship(xoffset, yoffset, zoffset))
                {
                    // Determining whether these coordinates are valid
                    // graph coordinates
                    xcoord = (int32_t) node_get_x(*n_ref) + (int32_t) xoffset;
                    ycoord = (int32_t) node_get_y(*n_ref) + (int32_t) yoffset;
                    zcoord = (int32_t) node_get_z(*n_ref) + (int32_t) zoffset;
                    if (graph_valid_coord(*g_ref, xcoord, ycoord, zcoord))
                    {
                        // Adding this neighbour to the array of neighbours.
                        neighbour = graph_get_node(*g_ref, (uint16_t) xcoord, 
                                        (uint16_t) ycoord, (uint16_t) zcoord);
                        array_push_back(&neighbours, neighbour); 
                    }
                }
            }
        }
    }

    // Initialising the edges of the neighbours for the node
    // that was provided to this function.
    node_init_edges(n_ref, neighbours);

    // Freeing the array of neighbours.
    array_free(&neighbours);
}

/**
 * Initialises the graph's nodes. 
 */
void graph_init_nodes(graph* g_ref)
{
    uint16_t x; // Current x coordinate
    uint16_t y; // Current y coordinate
    uint16_t z; // Current z coordinate

    // Allocating memory to the x axis.
    (*g_ref)->nodes = (node***) malloc((*g_ref)->x_size * sizeof(node**));
    for (x = 0; x < (*g_ref)->x_size; x++)
    {
        // Allocating memory to the y axis.
        (*g_ref)->nodes[x] = (node**) malloc((*g_ref)->y_size * sizeof(node*));
        for (y = 0; y < (*g_ref)->y_size; y++)
        {
            // Allocating memory to the z axis.
            (*g_ref)->nodes[x][y] = 
                (node*) malloc((*g_ref)->z_size * sizeof(node));
            for (z = 0; z < (*g_ref)->z_size; z++)
            {
                // Initialising the node at coordinate {x,y,z}
                node_init(&(*g_ref)->nodes[x][y][z], x, y, z);
            }
        }
    }

    // Creating the edges of the nodes' neighbours.
    for (x = 0; x < (*g_ref)->x_size; x++)
    {
        for (y = 0; y < (*g_ref)->y_size; y++)
        {
            for (z = 0; z < (*g_ref)->z_size; z++)
            {
                // Initialising the manhattan style edges of the 
                // node at the coordinates {x,y,z}.
                graph_init_node_edges(g_ref, &(*g_ref)->nodes[x][y][z]);
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
    // Allocating memory for the graph
    *g_ref = (graph) malloc(sizeof(struct graph_data));

    // Storing the graph dimensions
    (*g_ref)->x_size = x_size;
    (*g_ref)->y_size = y_size;
    (*g_ref)->z_size = z_size;

    // Setting the way in which graph-nodes will be considered
    // neighbours of other graph-nodes
    (*g_ref)->g_style = g_style;

    graph_init_nodes(g_ref);
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
 * Returns the graph's graph_style.
 */
enum graph_styles graph_get_style(graph g)
{
    return g->g_style;
}

/**
 * Adds a connection from one graph node to another, considering 
 * it as a neighbour.
 * Note, this creates a one-way connection.
 */
void  graph_add_edge(node* from_ref, node* to_ref, uint8_t weight)
{
    node_add_edge(from_ref, to_ref, weight);
}

/**
 * Disconnects one graph node from another, stopping
 * them from considered neighbours.
 * Note, this is a one-way disconnection.
 */
void graph_remove_edge(node* from_ref, node* to_ref) 
{
    node_remove_edge(from_ref, to_ref);
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