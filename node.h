/**
 * node.h
 * 
 * Data structure and function declarations for a graph node.
 * For use in a weighted graph typically used within a search algorithm.
 * 
 * Author: Richard Gale
 * Version: 15th August, 2022 
 */

#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * The node data-structure.
 */
typedef struct node_data* node;

/**
 * Initialises the node at the provided reference.
 */
void node_init(node* n_ref, int x, int y, int z, int weight);

/**
 * Frees the memory allocated to the node at the provided reference.
 */
void node_free(node* n_ref);

/**
 * Returns a reference to the node that preceeded the
 * provided node on the path.
 */
node* node_get_came_from(node n);

/**
 * Returns the x coordinate of the provided node.
 */
int node_get_x(node n);

/**
 * Returns the y coordinate of the provided node.
 */
int node_get_y(node n);

/**
 * Returns the z coordinate of the provided node.
 */
int node_get_z(node n);

/**
 * Returns the estimated total cost of a path if
 * the path goes through the provided node.
 */
int node_get_f(node n);

/**
 * Returns the cost of a path from its start to the provided node.
 */
int node_get_g(node n);

/**
 * Returns the weight of the provided node.
 */
int node_get_w(node n);

/**
 * Sets the node at the provided reference as being the node 
 * preceeding the node at the provided reference on a path.
 */
void node_set_came_from(node* n, node* came_from);

/**
 * Sets the estimated total cost of a path if the path were to go 
 * through the node at the provided reference.
 */
void node_set_f(node* n, int f);

/**
 * Sets the cost of a path from the path's starting point to
 * the node at the provided reference.
 */
void node_set_g(node* n, int g);

/**
 * Prints the node.
 */
void node_print(node n);

#endif // NODE_H