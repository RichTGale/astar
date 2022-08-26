/**
 * node.c
 * 
 * Data structure and function definitions for a weighted graph node.
 * 
 * Author: Richard Gale
 * Version: 26th August, 2022 
 */

#include "node.h"

/**
 * The data contained within the node data-structure.
 */
struct node_data {
    node* came_from; // A reference to the node preceeding this node on the path.
    uint16_t x;  // x coordinate.
    uint16_t y;  // y coordinate.
    uint16_t z;  // z coordinate.
    uint32_t f;  // Estimated cost from start to end node after going through this node.
    uint32_t g;  // Cost from start node to this node.
    array neighbours;  // The nodes in the graph that this node is connected to.
};

/**
 * Initialises the node at the provided reference.
 */
void node_init(node* n_ref, uint16_t x, uint16_t y, uint16_t z)
{
    *n_ref = (node) malloc(sizeof(struct node_data));
    (*n_ref)->came_from = NULL;
    (*n_ref)->x = x;
    (*n_ref)->y = y;
    (*n_ref)->z = z;
    (*n_ref)->f = UINT32_MAX;
    (*n_ref)->g = UINT32_MAX;
    array_init(&(*n_ref)->neighbours);
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


array* node_get_neighbours(node* n_ref)
{
    return &(*n_ref)->neighbours;
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
void node_add_neighbour(node* n_ref, node* neighbour)
{
    bool already_neighbours = false;    // Whether the two provided nodes are already neighbours

    // Determining if the nodes are already neighbours.
    for (int n = 0 ; n < array_size((*n_ref)->neighbours); n++)
    {
        if (neighbour == array_get_data((*n_ref)->neighbours, n))
        {
            already_neighbours = true;

        }
    }

    if (!already_neighbours)
    {
        // Adding the node as a neighbour.
        array_push_back(&(*n_ref)->neighbours, neighbour);
    }
    else
    {
        // The node was already a neighbour so we are printing a warning.
        printf("\nWARNING: In function node_add_neighbour(): "
            "Node at memory address %p was already a neighbour of "
            "the node at memory address %p and wan't added again!\n", 
            neighbour, n_ref);
    }
}

/**
 * Removes a connection from node from another, stopping
 * them from considered neighbours.
 * Note, this is a one-way disconnection.
 */
void node_remove_neighbour(node* n_ref, node* neighbour)
{
    bool already_neighbours = false;    // Whether the two provided nodes are already neighbours.

    // Finding the neighbour to remove.
    for (int n = 0 ; n < array_size((*n_ref)->neighbours); n++)
    {
        if (neighbour == array_get_data((*n_ref)->neighbours, n))
        {
            already_neighbours = true;

            // Removing the neighbour
            array_pop_data(&(*n_ref)->neighbours, n);
        }
    }

    printf("ARRAYSIZE:%d\n", array_size((*n_ref)->neighbours));
    if (!already_neighbours)
    {
        // The node wasn't a neighbour so we are printing a warning.
        printf("\nWARNING: In function node_remove_neighbour(): "
            "Node at memory address %p wasn't a neighbour of "
            "the node at memory address %p so it wasn't removed!\n", 
            neighbour, n_ref);
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