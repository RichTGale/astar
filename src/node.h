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
 * These are the identities of the different types of nodes.
 */
enum node_type { PASSABLE, IMPASSABLE };

/**
 * This is the data-structure of the node type.
 */
typedef struct node_data* node;

/**
 * This function initialises the node provided to it.
 */
void node_init(node* np, uint8_t x, uint8_t y, uint8_t z, enum node_type type);

/**
 * This function destroys the node provided to it.
 */
void node_free(node* np);

/**
 * This function returns the node on a path created by the astar algorithm
 * that preceeds the node provided to this function on that path.
 */
node* node_get_came_from(node n);

/**
 * This function returns the edges of the node provided to it.
 */
array node_get_edges(node n);

/**
 * This function returns the array of neighbours of the node provided to it.
 */
array node_get_neighbours(node n);

/**
 * This function is passed two nodes as its parameters. If the second node is a
 * neighbour of the first, this function will return the edge of the second
 * node that is relevant to the first node. */
edge* node_get_neighbouring_edge(node* np1, node n2);

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
 * This function returns the cost of a path from its start to the node provided
 * to this function.
 */
uint64_t node_get_g(node n);


/**
 * This function returns the node-type of the node provided to this procedure.
 */
enum node_type node_get_type(node n);

/**
 * This function sets which node on a path created by the astar algorithm
 * preceeds the node provided to this function on that path.
 */
void node_set_came_from(node* np, node* came_from);

/**
 * This function sets the estimated total cost of a path from the start
 * node to the goal node if the path goes through the node provided to this
 * function.
 */
void node_set_f(node* n, uint64_t f);

/**
 * This function sets the cost of a path from its start to the node provided
 * to this function.
 */
void node_set_g(node* n, uint64_t g);

/**
 * This function initialises the edges that belong to the neighbouring nodes 
 * of the node at the pointer that was provided to this function.
 */
void node_init_edges(node* np, uint8_t* weights);

/**
 * This function adds a connection from one graph node to another, making the
 * "to" node be considered a neighbour of the "from" node.
 * Note: this creates a one-way connection.
 */
void node_add_edge(node* fromp, node* top, uint8_t weight);

/**
 * This function adds neighbour provided to it to the node also provided's
 * array of neighbours.
 */
void node_add_neighbour(node* np, node* neighbour);

/**
 * This function removes the neighbour provided to it from the node also
 * provided's array of neighbours.
 */
void node_remove_neighbour(node* np, node* neighbourp);

/**
 * This function resets the node to its original state.
 */
void node_reset(node* np);

/**
 * This function removes a connection from one node from another, stopping
 * the "from" node from being considered a neighbour of the "to" node.
 * Note: this is a one-way disconnection.
 */
void node_remove_edge(node* fromp, node* top);

/**
 * This function prints information about the node provided to it.
 */
void node_print(node n);

#endif // NODE_H
