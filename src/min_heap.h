/**
 * min_heap.h
 * 
 * This file contains the public data-structure and function prototype
 * declarations for the min_heap type.
 * 
 * The min_heap type is a minimum heap. It arranges the values that are put 
 * into it into a binary tree where the values are sorted from the lowest to
 * the highest, so if you were to take the first value off its top, that value
 * would be the lowest value in the heap. 
 * 
 * This minimum heap was written for use as the openset/priority queue in an
 * A* (Astar) search algorithm.
 * 
 * Astar version: 1.0.0
 * File version: 1.0.1
 * Author: Richard Gale
 */

#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "array.h"
#include "node.h"

/**
 * These are the types of data min_heaps can deal with.
 */
enum data_type { INTEGER, NODE };

/**
 * This is the min_heap data structure.
 */
typedef struct min_heap_data* min_heap;

/**
 * This function initialises the min_heap provided to it.
 */
void min_heap_init(min_heap* mh_ref, enum data_type t);

/**
 * This function destroys the min_heap provided to it.
 */
void min_heap_free(min_heap* mh_ref);

/**
 * This function returns true if the value provided to it is already stored by
 * the min_heap that is also provided to the function.
 */
bool min_heap_val_exists(min_heap mh, void* val);

/**
 * This function returns true if the provided min_heap is empty.
 */
bool min_heap_is_empty(min_heap mh);

/**
 * This function adds a value to the min_heap provided to it.
 */
void min_heap_add(min_heap* mh_ref, void* data);

/**
 * This function removes the minimum value from the heap and returns it.
 */
void* min_heap_pop_min(min_heap* mh_ref);


#endif // MIN_HEAP_H
