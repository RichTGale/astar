/**
 * graph.h
 * 
 * This file contains the data-structure and function prototype declarations
 * for the graph type.
 *
 * The graph type is an up to 3 dimentional weighted graph. It can be used
 * for graph-related search/path finding algorithms. This one was written
 * for use with an A* (Astar) search algorithm.
 * 
 * Version: 1.0.0
 * File version: 1.0.1
 * Author: Richard Gale
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "array.h"
#include "node.h"

/**
 * These are the identities of ways a graph-node will be considered the
 * neighbour of another graph-node.
 */
enum graph_style { MANHATTAN, DIAGONAL };

/**
 * This is graph data structure.
 */
typedef struct graph_data* graph;

/**
 * This function initialises the graph provided to it.
 */
void graph_init(graph* g_ref, uint8_t x_size, uint8_t y_size, 
                        uint8_t z_size, enum graph_style g_style);

/**
 * This function destroys the graph provided to it.
 */
void graph_free(graph* g);

/**
 * This function returns a reference to the graph-node at the provided
 * coordinates.
 */
node* graph_get_node(graph g, uint8_t x, uint8_t y, uint8_t z);

/**
 * This function returns the graph's graph_style whic is the relationship
 * between the graph's nodes.
 */
enum graph_style graph_get_style(graph g);

/**
 * This function resets the graph to its original state so it can be searched
 * again. 
 */
void graph_reset(graph* g_ref);


/**
 * Adds a connection from one graph node to another, considering 
 * it as a neighbour.
 * Note, this creates a one-way connection.
 */
void graph_add_edge(node* from_ref, node* to_ref, uint8_t weight);

/**
 * Disconnects one graph node from another, stopping
 * them from considered neighbours.
 * Note, this is a one-way disconnection.
 */
void graph_remove_edge(node* from_ref, node* to_ref);

/**
 * This function prints the graph.
 */
void graph_print(graph g);

#endif // GRAPH_H
