/**
 * astar.h
 * 
 * This file contains the data-structure and function prototype declarations
 * for the astar type.
 *
 * The astar type is an implementation of the A* (A Star) search algorithm. It
 * finds the shortest path between two nodes on a weighted graph.
 * 
 * Version: 1.0.0
 * File version: 1.0.1
 * Author: Richard Gale
 */

#ifndef ASTAR_H
#define ASTAR_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "array.h"
#include "edge.h"
#include "node.h"
#include "graph.h"
#include "min_heap.h"

/**
 * The data-structure of the astar type.
 */
typedef struct astar_data* astar;

/**
 * This function intialises the astar provided to it.
 */
void astar_init(astar* asp, graph* g);

/**
 * This function destroys the astar provided to it.
 */ 
void astar_free(astar* asp);

/**
 * This function returns an array containing the nodes that make up the
 * shortest path found by the search function. The array is empty if no path
 * was found by the search procedure. 
 */
array astar_get_path(astar as);

/**
 * This function resets the astar provided to it to its original state so it
 * is ready to search again.
 */
void astar_reset(astar* asp);

/**
 * This is the A* search algorithm. It searches for the shortest path from
 * the start node to the end node.
 */
void astar_search(astar* asp, node* start, node* end);

#endif // ASTAR_H
