/**
 * node.c
 * 
 * Data structure and function definitions for a weighted graph node.
 * 
 * Author: Richard Gale
 * Version: 27th August, 2022 
 */

#include "node.h"

/**
 * The data contained within the node data-structure.
 */
struct node_data {
    array edges;    // The edges of the node's neighbour's.
    node* came_from; // A reference to the node preceeding this node on the path.
    uint16_t x;  // x coordinate.
    uint16_t y;  // y coordinate.
    uint16_t z;  // z coordinate.
    uint32_t f;  // Estimated cost from start to end node after going through this node.
    uint32_t g;  // Cost from start node to this node.
};

/**
 * Initialises the node at the provided reference.
 */
void node_init(node* n_ref, uint16_t x, uint16_t y, uint16_t z)
{
    *n_ref = (node) malloc(sizeof(struct node_data));
    array_init(&(*n_ref)->edges);
    (*n_ref)->came_from = NULL;
    (*n_ref)->x = x;
    (*n_ref)->y = y;
    (*n_ref)->z = z;
    (*n_ref)->f = UINT32_MAX;
    (*n_ref)->g = UINT32_MAX;
}

/**
 * Initialises the node's edges.
 */
void node_init_edges(node* n_ref, array neighbours)
{
    node* neighbour;    // The neighbour the edge belongs to.
    edge* edges;    // The array of edges
    int x;  // x coordinate of the neighbour.
    int y;  // y coordinate of the neighbour.
    int z;  // z coordinate of the neighbour.
    
    edges = (edge*) malloc(array_size(neighbours) * sizeof(edge));

    for (uint32_t e = 0; e < array_size(neighbours); e++)
    {
        neighbour = (node*) array_get_data(neighbours, e);
        x = (*neighbour)->x;
        y = (*neighbour)->y;
        z = (*neighbour)->z;
        edge_init(&(edges[e]), x, y, z, 1);
        array_push_back(&(*n_ref)->edges, &(edges[e]));
    }
}

/**
 * Frees the memory allocated to the node at the provided reference.
 */
void node_free(node* n_ref)
{
    for (uint32_t e = 0; e < array_size((*n_ref)->edges); e++)
    {
        edge_free(array_get_data((*n_ref)->edges, e));
    }
    array_free(&(*n_ref)->edges);
    free(*n_ref);
}

/**
 * Returns a reference to the node that preceeded the
 * node at the provided reference on a path.
 */
node* node_get_came_from(node n)
{
    return n->came_from;
}

/**
 * Returns the x coordinate of the provided node.
 */
uint16_t node_get_x(node n)
{
    return n->x;
}

/**
 * Returns the y coordinate of the provided node.
 */
uint16_t node_get_y(node n)
{
    return n->y;
}

/**
 * Returns the z coordinate of the provided node.
 */
uint16_t node_get_z(node n)
{
    return n->z;
}

/**
 * Returns the estimated total cost of a path if
 * the path goes through the provided node.
 */
uint32_t node_get_f(node n)
{
    return n->f;
}

/**
 * Returns the cost of a path from its start to the provided node.
 */
uint32_t node_get_g(node n)
{
    return n->g;
}


/**
 * Returns the edges of the supplied node,
 */
array node_get_edges(node n)
{
    return n->edges;
}

/**
 * Sets the node at the provided reference as being the node 
 * preceeding the node at the provided reference on a path.
 */
void node_set_came_from(node* n, node* came_from)
{
    (*n)->came_from = came_from;
}

/**
 * Sets the estimated total cost of a path if the path were to go 
 * through the node at the provided reference.
 */
void node_set_f(node* n, uint32_t f)
{
    (*n)->f = f;
}

/**
 * Sets the cost of a path from the path's starting point to
 * the node at the provided reference.
 */
void node_set_g(node* n, uint32_t g)
{
    (*n)->g = g;
}

/**
 * Adds a connection from one graph node to another, considering 
 * it as a neighbour.
 * Note, this creates a one-way connection.
 */
void node_add_edge(node* from_ref, node* to_ref, uint8_t weight)
{
    bool already_neighbours = false;    // Whether the two provided nodes are already neighbours
    edge* e_ref;    // The edge seperating the nodes
    uint16_t x; // The x coordinate of an edge of the node we're adding an edge from.
    uint16_t y; // The y coordinate of an edge of the node we're adding an edge from.
    uint16_t z; // The z coordinate of an edge of the node we're adding an edge from.
    

    // Determining if the nodes are already neighbours.
    for (int i = 0 ; i < array_size((*from_ref)->edges); i++)
    {
        x = edge_get_x(*((edge*) array_get_data((*from_ref)->edges, i)));
        y = edge_get_y(*((edge*) array_get_data((*from_ref)->edges, i)));
        z = edge_get_z(*((edge*) array_get_data((*from_ref)->edges, i)));

        if ((*to_ref)->x == x && (*to_ref)->y == y && (*to_ref)->z == z)
        {
            already_neighbours = true;
        }
    }

    if (!already_neighbours)
    {
        // Initialising and adding the neighbour as an edge.
        e_ref = (edge*) malloc(sizeof(edge));
        edge_init(&(e_ref[0]), (*to_ref)->x, (*to_ref)->y, (*to_ref)->z, weight);
        array_push_back(&(*from_ref)->edges, &(e_ref[0]));
    }
    else
    {
        // The node was already a neighbour so we are printing a warning.
        printf("\nWARNING: In function node_add_edge(): "
            "Node at coords (%d,%d,%d) was already a neighbour of the "
            "node at coords (%d,%d,%d) and wasn't added again!\n", 
            to_ref, from_ref);
    }
}

/**
 * Removes a connection from node from another, stopping
 * them from considered neighbours.
 * Note, this is a one-way disconnection.
 */
void node_remove_edge(node* from_ref, node* to_ref)
{
    bool already_neighbours = false;    // Whether the two provided nodes are already neighbours.
    uint16_t x; // The x coordinate of an edge of the node we're removing an edge from.
    uint16_t y; // The y coordinate of an edge of the node we're removing an edge from.
    uint16_t z; // The z coordinate of an edge of the node we're removing an edge from.

    // Finding the neighbour to remove.
    for (int i = 0 ; i < array_size((*from_ref)->edges); i++)
    {
        x = edge_get_x(*((edge*) array_get_data((*from_ref)->edges, i)));
        y = edge_get_y(*((edge*) array_get_data((*from_ref)->edges, i)));
        z = edge_get_z(*((edge*) array_get_data((*from_ref)->edges, i)));

        if ((*to_ref)->x == x && (*to_ref)->y == y && (*to_ref)->z == z)
        {
            already_neighbours = true;

            // Removing the edge
            array_pop_data(&(*from_ref)->edges, i);
        }
    }

    if (!already_neighbours)
    {
        // The node wasn't a neighbour so we are printing a warning.
        printf("\nWARNING: In function node_remove_edge(): "
            "Node at coords (%d,%d,%d) wasn't a neighbour of the "
            "node at coords (%d,%d,%d) so it wasn't removed!\n", 
            to_ref, from_ref);
    }
}

/**
 * Prints the node.
 */
void node_print(node n)
{
    printf("{ node: x:%d, y:%d, z:%d, f:%ld, g:%ld }", 
            n->x, n->y, n->z, n->f, n->g);
}