/**
 * edge.h
 * 
 * This file contains the data-structure and function prototype declarations
 * for an edge.
 *
 * An edge represents a distance between two nodes on a weighted graph, or the
 * cost to travel between the two nodes.
 * 
 * Version: 1.0.0
 * File version: 1.0.1
 * Author: Richard Gale
 */

#ifndef EDGE_H
#define EDGE_H

#include <stdlib.h>
#include <stdint.h>

/**
 * This is the edge data-structure.
 */
typedef struct edge_data* edge;

/**
 * This function initialises the edge provided to it.. 
 */
void edge_init(edge* e_ref, uint8_t x, uint8_t y, uint8_t z, uint8_t w);

/**
 * This function destroys the edge provided to it.
 */
void edge_free(edge* e_ref);

/**
 * This function returns the x coordinate of the node the edge provided to
 * the function belongs to.
 */
uint8_t edge_get_x(edge e);

/**
 * This function returns the y coordinate of the node the edge provided to
 * the function belongs to.
 */
uint8_t edge_get_y(edge e);

/**
 * This function returns the z coordinate of the node the edge provided to
 * the function belongs to.
 */
uint8_t edge_get_z(edge e);

/**
 * This function returns the weight of the edge provided to it.
 */
uint8_t edge_get_w(edge e);

#endif // EDGE_H
