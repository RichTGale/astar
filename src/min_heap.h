/**
 * min_heap.h
 * 
 * This file contains the data-structure and function prototype declarations 
 * for a minimum heap.
 * A minimum heap stores values as a binary-tree and in such an order that
 * the minimum value is at the very top, and is not a child of any other value.
 * 
 * Author: Richard Gale
 * Version: 17th June, 2023
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
