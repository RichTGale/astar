/**
 * node.c
 * 
 * Data structure and function definitions for a weighted graph node.
 * 
 * Author: Richard Gale
 * Version: 30th August, 2022 
 */

#include "node.h"

/**
 * The data contained within the node data-structure.
 */
struct node_data {
    array edges;    // The edges of the node's neighbour's.
    node* came_from; // A reference to the node preceeding this node on the path.
    uint8_t x;  // x coordinate.
    uint8_t y;  // y coordinate.
    uint8_t z;  // z coordinate.
    uint64_t f;  // Estimated total cost of path after going through this node.
    uint64_t g;  // Cost of the path from start node to this node.
};

/**
 * Initialises the node at the provided reference.
 */
void node_init(node* n_ref, uint8_t x, uint8_t y, uint8_t z)
{
    *n_ref = (node) malloc(sizeof(struct node_data));
    array_init(&(*n_ref)->edges);
    (*n_ref)->came_from = NULL;
    (*n_ref)->x = x;
    (*n_ref)->y = y;
    (*n_ref)->z = z;
    (*n_ref)->f = UINT64_MAX;
    (*n_ref)->g = UINT64_MAX;
}

/**
 * Initialises the node's edges.
 */
void node_init_edges(node* n_ref, array neighbours)
{
    node* neighbour;    // The neighbour the edge belongs to.
    edge* edges;    // The array of edges
    uint8_t x;  // x coordinate of the neighbour.
    uint8_t y;  // y coordinate of the neighbour.
    uint8_t z;  // z coordinate of the neighbour.
    uint64_t e; // The index of the current edge.
    
    // Allocating memory for all the edges.
    edges = (edge*) malloc(array_size(neighbours) * sizeof(edge));

    // Initialising and adding the edge to the node provided
    // to this function.
    for (e = 0; e < array_size(neighbours); e++)
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
    uint64_t e; // The index of the current edge.

    // Freeing the edges.
    for (e = 0; e < array_size((*n_ref)->edges); e++)
    {
        edge_free(array_get_data((*n_ref)->edges, e));
    }
    array_free(&(*n_ref)->edges);

    // Freeing the node.
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
uint8_t node_get_x(node n)
{
    return n->x;
}

/**
 * Returns the y coordinate of the provided node.
 */
uint8_t node_get_y(node n)
{
    return n->y;
}

/**
 * Returns the z coordinate of the provided node.
 */
uint8_t node_get_z(node n)
{
    return n->z;
}

/**
 * Returns the estimated total cost of a path if
 * the path goes through the provided node.
 */
uint64_t node_get_f(node n)
{
    return n->f;
}

/**
 * Returns the cost of a path from its start to the provided node.
 */
uint64_t node_get_g(node n)
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
void node_set_f(node* n, uint64_t f)
{
    (*n)->f = f;
}

/**
 * Sets the cost of a path from the path's starting point to
 * the node at the provided reference.
 */
void node_set_g(node* n, uint64_t g)
{
    (*n)->g = g;
}

/**
 * Prints the node.
 */
void node_print(node n)
{
    printf("{ node: x:%d, y:%d, z:%d, f:%" PRIu64 ", g:%" PRIu64 " }", 
            n->x, n->y, n->z, n->f, n->g);
}
