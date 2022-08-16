/**
 * node.c
 * 
 * Data structure and function definitions for a graph node.
 * For use in a weighted graph typically used within a search algorithm.
 * 
 * Author: Richard Gale
 * Version: 15th August, 2022 
 */

#include "node.h"

/**
 * The data contained within the node data-structure.
 */
struct node_data {
    node* came_from; // A reference to the node preceeding this node on the path.
    int x;  // x coordinate.
    int y;  // y coordinate.
    int z;  // z coordinate.
    int g;  // Cost from start node to this node.
    int f;  // Estimated cost from start to end node after going through this node.
    int w;  // The weight or cost of this node.
};

/**
 * Initialises the node at the provided reference.
 */
void node_init(node* n_ref, int x, int y, int z, int weight)
{
    *n_ref = (node) malloc(sizeof(struct node_data));
    (*n_ref)->came_from = NULL;
    (*n_ref)->x = x;
    (*n_ref)->y = y;
    (*n_ref)->z = z;
    (*n_ref)->g = INFINITY;
    (*n_ref)->f = INFINITY;
    (*n_ref)->w = weight;
}

/**
 * Frees the memory allocated to the node at the provided reference.
 */
void node_free(node* n_ref)
{
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
int node_get_x(node n)
{
    return n->x;
}

/**
 * Returns the y coordinate of the provided node.
 */
int node_get_y(node n)
{
    return n->y;
}

/**
 * Returns the z coordinate of the provided node.
 */
int node_get_z(node n)
{
    return n->z;
}

/**
 * Returns the estimated total cost of a path if
 * the path goes through the provided node.
 */
int node_get_f(node n)
{
    return n->f;
}

/**
 * Returns the cost of a path from its start to the provided node.
 */
int node_get_g(node n)
{
    return n->g;
}

/**
 * Returns the weight of the provided node.
 */
int node_get_w(node n)
{
    return n->w;
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
void node_set_f(node* n, int f)
{
    (*n)->f = f;
}

/**
 * Sets the cost of a path from the path's starting point to
 * the node at the provided reference.
 */
void node_set_g(node* n, int g)
{
    (*n)->g = g;
}

/**
 * Prints the node.
 */
void node_print(node n)
{
    printf("{ node: x:%d, y:%d, z:%d, g:%d, f:%d, w:%d }", 
            n->x, n->y, n->z, n->g, n->f, n->w);
}