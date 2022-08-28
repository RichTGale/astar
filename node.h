/**
 * node.h
 * 
 * Data structure and procedure declarations for a weighted graph node.
 * 
 * Author: Richard Gale
 * Version: 28th August, 2022 
 */

#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <math.h>

#include "array.h"
#include "edge.h"

/**
 * The node data-structure.
 */
typedef struct node_data* node;

/**
 * Initialises the node at the provided reference.
 */
void node_init(node* n_ref, uint8_t x, uint8_t y, uint8_t z);

/**
 * Initialises the node's edges.
 */
void node_init_edges(node* n_ref, array edges);

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
uint16_t node_get_x(node n);

/**
 * Returns the y coordinate of the provided node.
 */
uint16_t node_get_y(node n);

/**
 * Returns the z coordinate of the provided node.
 */
uint16_t node_get_z(node n);

/**
 * Returns the estimated total cost of a path if
 * the path goes through the provided node.
 */
uint32_t node_get_f(node n);

/**
 * Returns the cost of a path from its start to the provided node.
 */
uint32_t node_get_g(node n);

/**
 * Returns the edges of the supplied node,
 */
array node_get_edges(node n);

/**
 * Sets the node at the provided reference as being the node 
 * preceeding the node at the provided reference on a path.
 */
void node_set_came_from(node* n, node* came_from);

/**
 * Sets the estimated total cost of a path if the path were to go 
 * through the node at the provided reference.
 */
void node_set_f(node* n, uint64_t f);

/**
 * Sets the cost of a path from the path's starting point to
 * the node at the provided reference.
 */
void node_set_g(node* n, uint64_t g);

/**
 * Adds a connection from one node to another, considering 
 * it as a neighbour.
 * Note, this creates a one-way connection.
 */
void node_add_edge(node* from_ref, node* to_ref, uint8_t weight);

/**
 * Removes a connection from node from another, stopping
 * them from considered neighbours.
 * Note, this is a one-way disconnection.
 */
void node_remove_edge(node* from_ref, node* to_ref);

/**
 * Prints the node.
 */
void node_print(node n);

#endif // NODE_H