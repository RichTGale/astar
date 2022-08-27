/**
 * astar.h
 * 
 * Data-structure and procedure declarations for
 * an A* (A Star) search algorithm.
 * 
 * Author: Richard Gale
 * Version: 28th August, 2022
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
 * The astar data-structure.
 */
typedef struct astar_data* astar;

/**
 * Intialises the astar.
 */
void astar_init(astar* as_ref, graph* g);

/**
 * Frees the memory allocated to the astar.
 */ 
void astar_free(astar* as_ref);

/**
 * Returns an array containing references to the nodes that 
 * make up the shortest path found by the search procedure. 
 */
array astar_get_path(astar as);

/**
 * Search algorithm. Searches for the shortest
 * path from the start node to the end node.
 */
void astar_search(astar* as_ref, node* start, node* end);

#endif // ASTAR_H
