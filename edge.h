/**
 * edge.h
 * 
 * Data-structure and function declarations for an edge.
 * Simulates the an edge of a graph-node.
 * 
 * Author: Richard Gale
 * Version: 28th August, 2022
 */

#ifndef EDGE_H
#define EDGE_H

#include <stdlib.h>
#include <stdint.h>

/**
 * The edge data-structure.
 */
typedef struct edge_data* edge;

/**
 * Initialises the edge. 
 */
void edge_init(edge* e_ref, uint8_t x, uint8_t y, uint8_t z, uint8_t w);

/**
 * Frees the memory allocated to the edge. 
 */
void edge_free(edge* e_ref);

/**
 * Returns the x coordinate of the neighbour this edge is against.
 */
uint16_t edge_get_x(edge e);

/**
 * Returns the y coordinate of the neighbour this edge is against.
 */
uint16_t edge_get_y(edge e);

/**
 * Returns the z coordinate of the neighbour this edge is against.
 */
uint16_t edge_get_z(edge e);

/**
 * Returns the weight of the edge.
 */
uint16_t edge_get_w(edge e);

#endif // EDGE_H