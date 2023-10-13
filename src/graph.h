/*
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
 * This is the data-structure of the graph type.
 */
typedef struct graph_data* graph;

/**
 * This function initialises the graph provided to it.
 */
void graph_init(graph* gp, uint8_t x_size, uint8_t y_size, 
                           uint8_t z_size, enum graph_style gstyle);

/**
 * This function destroys the graph provided to it.
 */
void graph_free(graph* gp);

/**
 * This function returns the node in the graph provided to it located at the
 * coordinates also provided to the function.
 */
node* graph_get_node(graph g, uint8_t x, uint8_t y, uint8_t z);

/**
 * This function returns the graph_style property of the graph provided to it.
 */
enum graph_style graph_get_style(graph g);

/**
 * This function returns the size of the x axis of the graph provided it.
 */
uint8_t graph_get_x_size(graph g);

/**
 * This function returns the size of the y axis of the graph provided it.
 */
uint8_t graph_get_y_size(graph g);

/**
 * This function returns the size of the z axis of the graph provided it.
 */
uint8_t graph_get_z_size(graph g);

/**
 * This function adds an edge to the "to" node provided to it, making it be
 * considered a neighbour of the "from" node provided to the function.
 * Note: This creates a one-way relationship between the nodes. The "from" node
 * will not be considered a neighbour of the "to" node.
 */
void graph_add_edge(node* fromp, node* top, uint8_t weight);

/**
 * This function removes an edge from the "to" node provided to it, making it
 * no longer be considered a neighbour of the "from" node provided to the
 * function.
 * Note: This destroys the relationship between the nodes one-way only. The
 * "from" node may still be considered a neighbour of the "to" node.
 */
void graph_remove_edge(node* fromp, node* top);

/**
 * This function resets the graph to its original state.
 */
void graph_reset(graph* gp);


/**
 * This function prints information about the graph.
 */
void graph_print(graph g);

#endif // GRAPH_H
