/**
 * min_heap.h
 * 
 * Data-structure and procedure declarations for a minimum heap.
 * 
 * Author: Richard Gale
 * Version: 25th August, 2022
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
 * The types of data the min_heap can deal with.
 */
enum types { INTEGER, NODE };

/**
 * The min_heap data structure.
 */
typedef struct min_heap_data* min_heap;

/**
 * Initialises the min_heap at the provided reference.
 */
void min_heap_init(min_heap* mh_ref, enum types t);

/**
 * Frees the memory allocated to the min_heap at the provided reference.
 */
void min_heap_free(min_heap* mh_ref);

/**
 * Returns true if the provided reference to a value is already 
 * in the min_heap.
 */
bool min_heap_val_exists(min_heap mh, void* val);

/**
 * Returns true if the provided min_heap is empty.
 */
bool min_heap_is_empty(min_heap mh);

/**
 * Adds a reference to a value to the min_heap.
 */
void min_heap_add(min_heap* mh_ref, void* data);

/**
 * Removes the minimum value from the heap and returns it
 */
void* min_heap_pop_min(min_heap* mh_ref);


#endif // MIN_HEAP_H
