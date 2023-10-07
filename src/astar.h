/**
 * astar.h
 * 
 * This file contains the data-structure and function prototype declarations
 * for the astar type.
 *
 * The astar type is an implementation of the A* (A Star) search algorithm. It
 * finds the shortest path between two nodes on a weighted graph.
 * 
 * Author: Richard Gale
 * Astar version: 1.0.0
 * File version: 1.0.1
 */

#ifndef ASTAR_H
#define ASTAR_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "array.h"
#include "node.h"
#include "graph.h"
#include "min_heap.h"

/**
 * This is the astar data-structure.
 */
typedef struct astar_data* astar;

/**
 * This function initialises the astar that is provided to it.
 */
void astar_init(astar* as_ref, graph* g);

/**
 * This function destroys the astar that is provided to it.
 */ 
void astar_free(astar* as_ref);

/**
 * This function returns an array containing the nodes that make up the
 * shortest path found by the search function. The array is empty if no path
 * was found by the search procedure. 
 */
array astar_get_path(astar as);

/**
 * This is the A* search algorithm. It searches for the shortest path from
 * the start node to the end node.
 */
void astar_search(astar* as_ref, node* start, node* end);

#endif // ASTAR_H
