/**
 * node.h
 * 
 * This file contains the public data structure and function prototype
 * declarations for the node type.
 *
 * The node type is a location on map. It represents a node on a weighted graph.
 *
 * This node was written for use in an A* (Astar) search algorithm.
 * 
 * Version: 1.0.0
 * File version: 1.0.1
 * Author: Richard Gale
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
 * This is the data-structure of the node type.
 */
typedef struct node_data* node;

/**
 * This function initialises the node provided to it.
 */
void node_init(node* np, uint8_t x, uint8_t y, uint8_t z);

/**
 * This function destroys the node provided to it.
 */
void node_free(node* np);

/**
 * This function returns the node that preceeded the node provided to the
 * function on a path.
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
 * This function returns the estimated total cost of a path if the path goes
 * through the node provided to the function.
 */
uint64_t node_get_f(node n);

/**
 * This function returns the cost of a path from its start to the node
 * provided to the function.
 */
uint64_t node_get_g(node n);

/**
 * This function returns the edges of the node provided to it.
 */
array node_get_edges(node n);

/**
 * This function sets the node provided to it with the node a path came from.
 */
void node_set_came_from(node* n, node* came_from);

/**
 * This function sets the estimated total cost of a path if the path were to go 
 * through the node provided to the function.
 */
void node_set_f(node* n, uint64_t f);

/**
 * This function sets the cost of a path from the path's starting point to
 * the node at the provided reference.
 */
void node_set_g(node* n, uint64_t g);

/**
 * This functions resets the node provided to it to its original state.
 */
void node_reset(node* np);

/**
 * This function initialises the edge of each neighbour of the node provided
 * to the function.
 */
void node_init_edges(node* np, array edges);

/**
 * This function adds a connection from one graph node to another, making the
 * node the connection is to a neighbour of the node the connection is from..
 * Note, this creates a one-way connection.
 */
void node_add_edge(node* fromp, node* top, uint8_t weight);

/**
 * This function removes a connection from node from another, stopping the node
 * the connection is from from being a neighbour the connection is to.
 * Note, this is a one-way disconnection.
 */
void node_remove_edge(node* fromp, node* top);

/**
 * This function prints the node.
 */
void node_print(node n);

#endif // NODE_H
