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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * This is the data-structure of the edge type.
 */
typedef struct edge_data* edge;

/**
 * This function initialises the edge provided to it. 
 */
void edge_init(edge* ep, void* neighbourp, uint8_t w);

/**
 * This function destroys the edge provided to it.
 */
void edge_free(edge* ep);

/**
 * This function returns the neighbouring node of the node that the edge
 * provided to the function belongs to.
 */
void* edge_get_neighbourp(edge* ep);

/**
 * This function returns the weight of the edge provided it.
 */
uint8_t edge_get_w(edge e);

/**
 * This function prints information about the edge provided to it.
 */
void edge_print(edge e);

#endif // EDGE_H
