/**
 * node.h
 * 
 * This file contains the data structure and function prototype declarations
 * for the node type.
 * 
 * Author: Richard Gale
 * Version: 17th June, 2023
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
 * Identities of the types of nodes.
 */
enum node_type { PASSABLE, IMPASSABLE };

/**
 * The node data-structure.
 */
typedef struct node_data* node;

/**
 * This function initialises the node at the provided reference.
 */
void node_init(node* np, uint8_t x, uint8_t y, uint8_t z, enum node_type type);

/**
 * This function initialises the edges that belong to the neighbouring nodes 
 * of the node at the pointer that was provided to this function.
 */
void node_init_edges(node* np, array neighbours, uint8_t* weights);

/**
 * This function de-allocates memory from the node at the pointer
 * provided to this function as well as the memory allocated to its edges.
 */
void node_free(node* np);

/**
 * This function returns the node on a path created by the astar algorithm
 * that preceeds the node provided to this function on that path.
 */
node* node_get_came_from(node n);

/**
 * This function returns the x coordinate of the node provided to it.
 */
uint8_t node_get_x(node n);

/**
 * This function returns the y coordinate of the node provided to it.
 */
uint8_t node_get_y(node n);

/**
 * This function returns the z coordinate of the node provided to it.
 */
uint8_t node_get_z(node n);

/**
 * This function returns the estimated total cost of a path from the start
 * node to the goal node if the path goes through the node provided to
 * this function.
 */
uint64_t node_get_f(node n);

/**
 * This function returns the cost of a path from its start to the
 * node provided to this function.
 */
uint64_t node_get_g(node n);

/**
 * This function returns the edges of the node provided to this procedure.
 */
array node_get_edges(node n);

/**
 * This function returns the node-type of the node provided to this procedure.
 */
enum node_type node_get_type(node n);

/**
 * This function sets the node on a path created by the astar algorithm
 * that preceeds the node at the node pointer provided to this function 
 * on that path.
 */
void node_set_came_from(node* n, node* came_from);

/**
 * This function sets the estimated total cost of a path from the start
 * node to the goal node if the path goes through the node at the node pointer
 * provided to this function.
 */
void node_set_f(node* n, uint64_t f);

/**
 * This function sets the cost of a path from its start to the
 * node at the node pointer provided to this function.
 */
void node_set_g(node* n, uint64_t g);

/**
 * This function adds a connection from one graph node to another, making the
 * "to" node be considered a neighbour of the "from" node.
 * Note: this creates a one-way connection.
 */
void node_add_edge(node* from_ref, node* to_ref, uint8_t weight);

/**
 * This function resets the node to its original state.
 */
void node_reset(node* n_ref);

/**
 * This function removes a connection from one node from another, stopping
 * the "from" node from being considered a neighbour of the "to" node.
 * Note: this is a one-way disconnection.
 */
void node_remove_edge(node* from_ref, node* to_ref);

/**
 * This function prints information about the node provided to it.
 */
void node_print(node n);

#endif // NODE_H
