/**
 * array.h
 *
 * This file contains the public data-structure and function prototype
 * declarations for the array type. 
 * 
 * The array type is a singly-linked list. It dynamically allocates and
 * de-allocates memory as elements are added to it and removed from it.
 *
 * Version: 1.0.0
 * File version: 1.0.1
 * Author: Richard Gale
 */

#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * This is the data-structure of the array type.
 */
typedef struct array_data* array;

/**
 * This function initialises the array provided to it.
 */
void array_init(array* ap);

/**
 * This function destroys the array provided to it as well as any array
 * elements linked to it.
 */
void array_free(array* ap);

/**
 * This function returns the data stored at the index provided to it from the
 * array that is also provided to the function.
 */ 
void* array_get_data(array a, uint64_t index);

/**
 * This function returns the number of elements in the array provided to it.
 */
uint64_t array_size(array a);

/**
 * This function removes the first element from the array provided to it, then
 * returns it.
 */
void* array_pop_front(array* ap);

/**
 * This function removes the last element from the array provided to it, then 
 * returns it.
 */
void* array_pop_back(array* ap);

/**
 * This function removes the element from the array provided to it which is at
 * the index provided to the function, then returns it.
 */
void* array_pop_data(array* ap, uint64_t index);

/**
 * This function adds a new element to the beginning of the array provided
 * to it.
 */
void array_push_front(array* ap, void* data);

/**
 * This function adds a new element to the end of the array provided to it.
 */
void array_push_back(array* ap, void* data);

/**
 * This function replaces the data in the array element of the array provided
 * to the function which is at the index also provided to the function.
 */
void array_set_data(array* ap, uint64_t index, void* data);

#endif // ARRAY_H
