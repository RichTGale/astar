/**
 * min_heap.c
 * 
 * This file contains the internal data-structure and function definitions 
 * for a minimum heap.
 * A minimum heap stores values as a binary-tree and in such an order that
 * the minimum value is at the very top, and is not a child of any other value.
 * 
 * Author: Richard Gale
 * Version: 17th June, 2023
 */

#include "min_heap.h"

/** 
 * Error codes.
 */
#define HEAP_EMPTY_ERROR 1
#define HEAP_FULL_ERROR 2

/**
 * The number of values the heap can hold.
 */
#define MAX_CAPACITY UINT64_MAX 

/**
 * The internal data-structure of the min_heap type.
 */
struct min_heap_data {
    array heap;             // The heap's storage.
    enum heap_types type;   // The data-type the min_heap can store
    uint64_t num_elems;     // The number of elements stored in the heap.
};

/**
 * This function initialises the min_heap at the provided min_heap pointer.
 */
void min_heap_init(min_heap* mhp, enum heap_types t)
{
    /* Allocating memory for the heap. */
    *mhp = (min_heap) malloc(sizeof(struct min_heap_data));

    /* Initialising the heap's storage. */
    array_init(&(*mhp)->heap);

    /* Initialising the heap to store the specified data-type. */
    (*mhp)->type = t;

    /* Initialising our count of the number of elements that are stored
     * in the heap. */
    (*mhp)->num_elems = 0;
}

/**
 * This function de-allocates memory from the min_heap at the min_heap 
 * pointer provided to it.
 */
void min_heap_free(min_heap* mhp)
{
    /* De-allocating memory from the heap's storage. */
    array_free(&(*mhp)->heap);

    /* De-allocating memory from the heap. */
    free(*mhp);
}

/**
 * This function returns true if the memory address of the value provided to
 * it is already in the min_heap at the min_heap pointer that was also
 * provided.
 */
bool min_heap_val_exists(min_heap mh, void* val)
{
    /* Whether the value is already in the min_heap. */
    bool val_exists = false;

    /* The index of the element in the heap we are comparing. */
    uint64_t i;

    /* Comparing the value provided to this function to all the lements in
     * the heap. */
    for (i = 0; i < array_size(mh->heap); i++)
    {
        if (val == array_get_data(mh->heap, i))
        {
            /* The value is already in the min_heap. */
            val_exists = true;
        }
    }

    /* Returning whether the value was already in the heap. */
    return val_exists;
}

/**
 * This function returns true if the provided min_heap is not storing
 * any values.
 */
bool min_heap_is_empty(min_heap mh)
{
    /* Whether the min_heap is not storing any values. */
    bool is_empty = false;  

    /* Determining whether there are any values stored in the heap. */
    if (mh->num_elems == 0)
    {
        /* There are no values in the heap. */
        is_empty = true;
    }

    /* Returning whether the heap is not storing any values. */
    return is_empty;
}

/**
 * This function swaps the value in the min_heap's storage at the index 
 * provided to the function with its parent's value if the value at the 
 * index is lower than the parent, moving the value up through the heap until 
 * the minimum heap state is satisfied.
 */
void min_heap_float_up(min_heap* mhp, int child_index)
{
    /* A pointer to the parent value. */
    void* parentp;
    
    /* A pointer to the child value. */
    void* childp;

    /* The parent value. */ 
    uint64_t parent_val;

    /* The child value. */
    uint64_t child_val;

    /* The index of the parent value in the heap's storage. */
    uint64_t parent_index; 

    /* Determining if the child is not already the minimum value in 
     * the heap. */
    if (child_index > 0)
    {
        /* Calculating the parent index. */
        parent_index = (child_index - 1) / 2;

        /* Getting the child and the parent addresses 
         * from the heap. */
        parentp = array_get_data((*mhp)->heap, parent_index);
        childp = array_get_data((*mhp)->heap, child_index);

        /* Getting the child and parent values for the data-type
         * particular to the heap. */
        if ((*mhp)->type == NODE)
        {
            // Node type
            parent_val = node_get_f(*((node*) parentp));
            child_val = node_get_f(*((node*) childp));
        }
        else if ((*mhp)->type == INTEGER)
        {
            // Integer type
            parent_val = *((uint64_t*) parentp);
            child_val = *((uint64_t*) childp);
        }

        /* Determining if we should swap the child and the parent. */ 
        if (child_val < parent_val)
        {
            /* The child has a lower value than the parent so we are
             * swapping them. */
            array_set_data(&(*mhp)->heap, child_index, parentp);
            array_set_data(&(*mhp)->heap, parent_index, childp);

            /* Repeating this function on the same value. */
            min_heap_float_up(mhp, parent_index);
        }
    }
}

/**
 * This function adds a pointer to a value to the min_heap.
 */
void min_heap_add(min_heap* mhp, void* data)
{
    /* Determining if the min heap has space to store a new value. */
    if ((*mhp)->num_elems < MAX_CAPACITY)
    {
        /* Storing the new reference. */
        array_push_back(&(*mhp)->heap, data);

        /* Placing the reference at the min_heap's storage index that
         * will satisfy the minimum heap property. */
        min_heap_float_up(mhp, (*mhp)->num_elems);

        /* Counting the new reference. */
        (*mhp)->num_elems++;
    }
    else
    {
        /* The heap didn't have enough space in its storage to store a new 
         * reference, so we are printing an error message and exiting the
         * program. */
        printf("\nERROR: In function min_heap_add(): You attempted to "
                "add a value to a heap that was at maximum capacity!\n");
        exit(HEAP_FULL_ERROR);
    }
}

/**
 * Swaps the value in the heap at the provided index with
 * the smaller of its two children, moving the value down through
 * the heap until the minimum heap property is satisfied. 
 */
void min_heap_sink_down(min_heap* mhp, int parent_index)
{
    /* A pointer to the parent's left child. */
    void* leftp;

    /* A pointer to the parent's right child. */
    void* rightp;

    /* A temporary pointer for swapping. */
    void* tempp;

    /* The minimum of the children's values. */
    uint64_t min_val;

    /* The value of the storage element at the index provided to
     * this function. */
    uint64_t parent_val;

    /* The index of the parent's left child in the heap's storage. */
    uint64_t left_index;

    /* The index of the parent's right child in the heap's storage. */
    uint64_t right_index;

    /* The minimum of the parent's, left and right children's values. */
    uint64_t min_index;

    /* Calculating the indices of the two children. */
    left_index = (parent_index * 2) + 1;
    right_index = (parent_index * 2) + 2;

    /* Defaulting the minimum of the parent and child values index to
     * the parent's index. */
    min_index = parent_index;

    /* Determining the minimum value between the children. 
     * There may not necessarily be any children. First we determine if there
     * are two children */
    if (left_index < (*mhp)->num_elems && right_index < (*mhp)->num_elems)
    {
        /* Getting the children from the heap storage. */
        leftp = array_get_data((*mhp)->heap, left_index);
        rightp = array_get_data((*mhp)->heap, right_index);

        /* Comparing the values of the two children with consideration towards
         * the particular data-type the heap deals with. */
        if ((*mhp)->type == NODE)
        {
            /* Comparing the values of the children and getting the one with
             * the lower/minimum value between the two. */
            min_index = node_get_f(*((node*) leftp)) < 
                node_get_f(*((node*) rightp)) ? left_index : right_index;
        }
        else if ((*mhp)->type == INTEGER)
        {
            /* Comparing the values of the children and getting the one with
             * the lower/minimum value between the two. */
            min_index = *((uint64_t*) leftp) < 
                *((uint64_t*) rightp) ? left_index : right_index;
        }
    }
    /* Determining if there is only one child. The left child always has a
     * higher indices in the heap's storage than the right child. */
    else if (left_index < (*mhp)->num_elems)
    {
        /* There is only a left child so we are setting that as the child with the
         * lower/minimum value between the children. */
        min_index = left_index;    
    } 

    /* Determining if there were any children. */
    if (min_index != parent_index)
    {
        /* Getting the minimum child value and the parent value with
         * consideration towards the particular data-type the heap
         * deals with. */
        if ((*mhp)->type == NODE)
        {
            min_val = 
                node_get_f(*((node*) array_get_data((*mhp)->heap, min_index)));
            parent_val = 
                node_get_f(*((node*) array_get_data((*mhp)->heap, parent_index)));
        }
        else if ((*mhp)->type == INTEGER)
        {
            min_val = 
                *((uint64_t*) array_get_data((*mhp)->heap, min_index));
            parent_val = 
                *((uint64_t*) array_get_data((*mhp)->heap, parent_index));
        }

        /* Determining if a value lower than the parent's was found. */
        if (min_val < parent_val)
        {
            /* The child value is lower than the parent so we are
             * swapping them. */
            tempp = array_get_data((*mhp)->heap, min_index);
            array_set_data(&(*mhp)->heap, 
                    min_index, array_get_data((*mhp)->heap, parent_index));
            array_set_data(&(*mhp)->heap, parent_index, tempp);

            /* Repeating this function on the same value which was at the
             * index provided to this function in the heap's storage. */
            min_heap_sink_down(mhp, min_index);
        }
    }
}

/**
 * This function returns the minimum value in the heap.
 */
void* min_heap_get_min(min_heap mh)
{
    /* Returning the heap's minimum value. */
    return array_get_data(mh->heap, 0);
}

/**
 * This function removes the minimum value from the heap and returns it.
 */
void* min_heap_pop_min(min_heap* mhp)
{
    /* The minimum value in the heap. */
    void* min;

    /* Getting the minimum value in the heap. */
    if ((*mhp)->num_elems > 1)
    {
        /* There are multiple values in the heap. Here we are
         * copying the minimum. */
        min = min_heap_get_min(*mhp);

        /* Moving the maximum value in the heap to the heap's top.
         * This overwrites the minimum value that was still in the
         * heap's storage. */
        array_set_data(&(*mhp)->heap, 0, array_pop_back(&(*mhp)->heap));

        /* Recording that a value has been deleted. */
        (*mhp)->num_elems--;

        /* Sinking the maximum value down through the heap. This re-orders
         * the heap into its minimum-heap state. */
        min_heap_sink_down(mhp, 0);
    } 
    else if ((*mhp)->num_elems == 1)
    {
        /* There is only one value in the heap, so we are taking it out. */
        min = array_pop_back(&(*mhp)->heap);

        /* Recording that a value has been removed from the heap. */
        (*mhp)->num_elems--;
    } 
    else
    {
        /* There were no values in the heap, so we are printing an error
         * message and exiting the program. */
        printf("ERROR: In function min_heap_pop_min(): heap is empty!");
        exit(HEAP_EMPTY_ERROR);
    }

    /* Returning the minimum value that was stored in the heap. */
    return min;
}
