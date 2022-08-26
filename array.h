/**
 * array.h
 *
 * Data-structure and procedure declarations for a singly-linked-list, 
 * an array that dynamically allocates and frees memory as elements 
 * are added to it and removed from it.
 *
 * Author: Richard Gale
 * Version: 26th August, 2022
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
 * Inititialises the array.
 */
void array_init(array* a_ref);

/**
 * Frees the memory allocated at the provided array reference
 * and any arrays (elements) linked to it.
 */
void array_free(array* a_ref);

/**
 * Returns the data in the provided array at the element
 * at the provided index.
 */ 
void* array_get_data(array head, uint32_t index);

/**
 * Returns the number of elements in the provided array.
 */
uint32_t array_size(array head);

/**
 * Removes the first element in the array at the provided
 * reference and returns it.
 */
void* array_pop_front(array* head_ref);

/**
 * Removes the last element from the array at the provided
 * reference and returns it.
 */
void* array_pop_back(array* head_ref);

/**
 * Removes the element at the provided index and returns it.
 */
void* array_pop_data(array* head_ref, uint32_t index);

/**
 * Adds a new element to the beginning of the array at
 * the provided array reference.
 */
void array_push_front(array* head_ref, void* data);

/**
 * Adds a new element to the end of the array at the provided
 * array reference.
 */
void array_push_back(array* head_ref, void* data);

/**
 * Sets the data in the element at the provided index of the
 * array at the provided array reference.
 */
void array_set_data(array* head_ref, uint32_t index, void* data);

#endif // ARRAY_H
