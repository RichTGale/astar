/**
 * array.h
 *
 * This file contains the data-structure and function prototype declarations 
 * for a singly-linked-list. 
 * This is an array that dynamically allocates and de-allocates memory as 
 * elements are added to it and removed from it.
 *
 * Author: Richard Gale
 * Version: 17th June, 2023
 */

#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * The array data-structure.
 */
typedef struct array_data* array;

/**
 * This function initialises the array at the provided array pointer.
 */
void array_init(array* ap);

/**
 * This function de-allocates the memory of the array at the 
 * provided array pointer and any arrays (elements) linked to it.
 */
void array_free(array* ap);

/**
 * This function returns a pointer to the data stored at the provided 
 * index in the provided array.
 * Once the data is returned, it should then be cast to the data-type
 * it was before it was placed in the array.
 */ 
void* array_get_data(array a, uint64_t index);

/**
 * This function returns the number of elements in the provided array.
 */
uint64_t array_size(array a);

/**
 * This function removes the first element from the array at the array 
 * pointer provided to it and returns it.
 * Once the data is returned, it should then be cast to the data-type
 * it was before it was placed in the array.
 */
void* array_pop_front(array* ap);

/**
 * This function removes the last element from the array at the array 
 * pointer provided to it and returns it.
 * Once the data is returned, it should then be cast to the data-type
 * it was before it was placed in the array.
 */
void* array_pop_back(array* ap);

/**
 * This function removes the element from the array at the provided array 
 * pointer at the index provided to the function and returns it.
 * Once the data is returned, it should then be cast to the data-type
 * it was before it was placed in the array.
 */
void* array_pop_data(array* ap, uint64_t index);

/**
 * This function adds a new element to the beginning of the array at
 * the provided array pointer.
 */
void array_push_front(array* ap, void* data);

/**
 * This function adds a new element to the end of the array at the provided
 * array pointer.
 */
void array_push_back(array* ap, void* data);

/**
 * This function replaces the data in the array element at the provided 
 * index of the array at the provided array reference.
 */
void array_set_data(array* ap, uint64_t index, void* data);

#endif // ARRAY_H
