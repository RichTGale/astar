/**
 * min_heap.c
 * 
 * This file contains the internal data-structure and function
 * definitions for the min_heap type.
 * 
 * The min_heap type is a minimum heap. It arranges the values that are put 
 * into it into a binary tree where the values are sorted from the lowest to 
 * the highest, so if you were to take the first value off its top, that value
 * would be the lowest value in the heap. 
 *
 * This minimum heap was written for use as the openset/priority queue in an
 * A* (Astar) search algorithm.
 * 
 * Version: 1.1.0
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
 * The identities of the types of data the min_heap can use.
 */
enum heap_types { INTEGER, NODE };

/**
 * The min_heap data structure.
 */
typedef struct min_heap_data* min_heap;

/**
 * This function initialises the min_heap at the provided min_heap pointer.
 */
void min_heap_init(min_heap* mhp, enum heap_types t);

/**
 * This function de-allocates memory from the min_heap at the min_heap 
 * pointer provided to it.
 */
void min_heap_free(min_heap* mhp);

/**
 * This function returns true if the memory address of the value provided to
 * it is already in the min_heap at the min_heap pointer that was also
 * provided.
 */
bool min_heap_val_exists(min_heap mh, void* val);

/**
 * This function returns true if the provided min_heap is not storing
 * any values.
 */
bool min_heap_is_empty(min_heap mh);

/**
 * This function adds a pointer to a value to the min_heap.
 */
void min_heap_add(min_heap* mhp, void* data);

/**
 * This function removes the minimum value from the heap and returns it.
 */
void* min_heap_pop_min(min_heap* mhp);


#endif // MIN_HEAP_H
