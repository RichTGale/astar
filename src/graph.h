/**
 * graph.h
 * 
 * Data-structure and procedure declarations for a 
 * three-dimensional weighted graph.
 * 
 * Author: Richard Gale
 * Version: 21st September, 2022
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
 * Defines for the way in which a graph-node will be considered 
 * the neighbour of another graph-node.
 */
enum graph_styles { MANHATTAN, DIAGONAL };


/**
 * The graph data structure.
 */
typedef struct graph_data* graph;

/**
 * Initialises the graph.
 */
void graph_init(graph* g_ref, uint8_t x_size, uint8_t y_size, 
                        uint8_t z_size, enum graph_styles g_style);

/**
 * Frees the memory allocated to the graph.
 */
void graph_free(graph* g);

/**
 * Returns a reference to the graph-node at the provided coordinate.
 */
node* graph_get_node(graph g, uint8_t x, uint8_t y, uint8_t z);

/**
 * Returns the graph's graph_style.
 */
enum graph_styles graph_get_style(graph g);

/**
 * Prints the graph.
 */
void graph_print(graph g);

#endif // GRAPH_H
