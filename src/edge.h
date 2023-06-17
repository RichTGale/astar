/**
 * edge.h
 * 
 * This file contains the data-structure and function prototype declarations
 * for the edge type.
 * An edge represents the cost in an astar algorithm to move from a graph
 * node to a neighbouring node.
 * 
 * Author: Richard Gale
 * Version: 17th June, 2023
 */

#ifndef EDGE_H
#define EDGE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * The data-structure of the edge type.
 */
typedef struct edge_data* edge;

/**
 * This function initialises the edge at the edge pointer provided to it. 
 */
void edge_init(edge* ep, uint8_t x, uint8_t y, uint8_t z, uint8_t w);

/**
 * This function de-allocates memory from the edge at the edge pointer
 * provided to it.
 */
void edge_free(edge* ep);

/**
 * This function returns the x coordinate of the relevant neighbour of the
 * node the edge provided to it belongs to.
 */
uint8_t edge_get_x(edge e);

/**
 * This function returns the y coordinate of the relevant neighbour of the
 * node the edge provided to it belongs to.
 */
uint8_t edge_get_y(edge e);

/**
 * This function returns the z coordinate of the relevant neighbour of the
 * node the edge provided to it belongs to.
 */
uint8_t edge_get_z(edge e);

/**
 * This function returns the weight of the edge provided it.
 */
uint8_t edge_get_w(edge e);

/**
 * This function prints information about the edge provided to it.
 */
void edge_print(edge e);

#endif // EDGE_H
