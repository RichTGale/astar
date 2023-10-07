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
 * min_heap version: 1.1.0
 * File version: 1.0.1
 * Author: Richard Gale
 */

#include "min_heap.h"

/* This is the maximum number of values the heap type can store. */
#define MAX_CAPACITY UINT64_MAX 

/**
 * This is the internal data-structure of the min_heap type.
 */
struct min_heap_data {
    array heap;             /* The heap's storage. */
    enum data_type dt;      /* The type of data the heap stores. */
    uint64_t num_elems;     /* The number of elements in the heap. */
};

/**
 * This function returns the minimum value in the heap.
 */
void* min_heap_get_min(min_heap mh);

/**
 * This function swaps the value at the index provided to it, which is in the 
 * min_heap also provided's storage, with its parent's value if the value at
 * the index is lower than the parent. The function then calls itself
 * recursively, moving the value up through the heap until a minimum heap
 * state is satisfied.
 */
void min_heap_float_up(min_heap* mhp, int child_index);

/**
 * This function swaps the value at the index provided to it, which is in the
 * min_heap also provided's storage, with the smaller of its two children. The
 * function then calls itself recursively, moving the value down through the
 * heap until a minimum heap state is satisfied. 
 */
void min_heap_sink_down(min_heap* mhp, int parent_index);

/**
 * This function initialises the min_heap provided to it.
 */
void min_heap_init(min_heap* mh_ref, enum data_type dt)
{
    /* Allocate memory to the heap. */
    *mh_ref = (min_heap) malloc(sizeof(struct min_heap_data));

    /* Initialise the heap's properties. */
    array_init(&(*mh_ref)->heap);
    (*mh_ref)->dt = dt;
    (*mh_ref)->num_elems = 0;
}

/**
 * This function destroys the min_heap provided to it.
 */
void min_heap_free(min_heap* mh_ref)
{
    /* Destroy the heap's storage. */
    array_free(&(*mh_ref)->heap);

    /* De-allocate memory from the min_heap. */
    free(*mh_ref);
}

/**
 * This function returns true if the value provided to it is already stored by
 * the min_heap that is also provided to the function.
 */
bool min_heap_val_exists(min_heap mh, void* val)
{
    /* This stores whether the value is already in the heap. */
    bool val_exists;

    /* This is the index of the element in the heap we are comparing. */
    uint64_t i;  

    /* Presume the value is not already in the heap. */
    val_exists = false;
    
    /* Check if the value is already in the heap. */
    for (i = 0; i < array_size(mh->heap); i++)
    {
        if (val == array_get_data(mh->heap, i))
        {
            /* The value is already in the heap. */
            val_exists = true;
        }
    }

    /* Return whether the value was already in the heap. */
    return val_exists;
}

/**
 * This function returns true if the provided min_heap is empty.
 */
bool min_heap_is_empty(min_heap mh)
{
    /*  Return whether the min_heap is empty. */
    return mh->num_elems == 0;
}

/**
 * This function adds a value to the min_heap provided to it.
 */
void min_heap_add(min_heap* mh_ref, void* data)
{
    /* Check if the heap has space to store a new value. */
    if ((*mh_ref)->num_elems < MAX_CAPACITY)
    {
        /* Store the new value. */
        array_push_back(&(*mh_ref)->heap, data);

        /* Place the value at the heap's storage index that will satisfy
         * the minimum heap state. */
        min_heap_float_up(mh_ref, (*mh_ref)->num_elems);

        /* Record that there's a new value in the heap. */
        (*mh_ref)->num_elems++;
    }
    else
    {   /* The heap didn't have enough space in its storage to store a new 
         * value, so we are print an error message and exit the program. */
        printf("\nERROR: In function min_heap_add(): You attempted to "
                "add a value to a heap that was at maximum capacity!\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * This function removes the minimum value from the heap and returns it.
 */
void* min_heap_pop_min(min_heap* mhp)
{
    /* This is the minimum value in the heap. */
    void* min;

    /* Check if there are multiple values in the heap. */
    if ((*mhp)->num_elems > 1)
    {
        /* There are multiple values in the heap. Copy the minimum value. */
        min = min_heap_get_min(*mhp);

        /* Move the maximum value in the heap to the heap's top.
         * This overwrites the minimum value that was still in the
         * heap's storage. */
        array_set_data(&(*mhp)->heap, 0, array_pop_back(&(*mhp)->heap));

        /* Record that a value has been removed from the heap. */
        (*mhp)->num_elems--;

        /* Sink the maximum value down through the heap. This re-orders the
         * heap into its minimum-heap state. */
        min_heap_sink_down(mhp, 0);
    }

    /* Check if there is only one value in the heap. */ 
    else if ((*mhp)->num_elems == 1)
    {
        /* There is only one value in the heap, so take it out. */
        min = array_pop_back(&(*mhp)->heap);

        /* Record that a value has been removed from the heap. */
        (*mhp)->num_elems--;
    } 
    else
    {
        /* There were no values in the heap, so print an error message and
         * exit the program. */
        fprintf(stdout,
                "ERROR: In function min_heap_pop_min(): heap is empty!");
        exit(EXIT_FAILURE);
    }

    /* Return the minimum value that was stored in the heap. */
    return min;
}
/**
 * This function returns the minimum value in the heap.
 */
void* min_heap_get_min(min_heap mh)
{
    /* Return the heap's minimum value. */
    return array_get_data(mh->heap, 0);
}

/**
 * This function swaps the value at the index provided to it, which is in the 
 * min_heap also provided's storage, with its parent's value if the value at
 * the index is lower than the parent. The function then calls itself
 * recursively, moving the value up through the heap until a minimum heap
 * state is satisfied.
 */
void min_heap_float_up(min_heap* mhp, int child_index)
{
    /* This is a pointer to the parent value. */
    void* parentp;
    
    /* This is a pointer to the child value. */
    void* childp;

    /* This is the parent value. */ 
    uint64_t parent_val;

    /* This is the child value. */
    uint64_t child_val;

    /* This is the index of the parent value in the heap's storage. */
    uint64_t parent_index; 

    /* Check if the child is not already the minimum value in the heap. */
    if (child_index > 0)
    {
        /* Calculate the parent index. */
        parent_index = (child_index - 1) / 2;

        /* Get the child and the parent addresses from the heap. */
        parentp = array_get_data((*mhp)->heap, parent_index);
        childp = array_get_data((*mhp)->heap, child_index);

        /* Get the child and parent values with respect to the data type the
         * heap uses. */
        if ((*mhp)->dt == NODE)
        {
            parent_val = node_get_f(*((node*) parentp));
            child_val = node_get_f(*((node*) childp));
        }
        else if ((*mhp)->dt == INTEGER)
        {
            parent_val = *((uint64_t*) parentp);
            child_val = *((uint64_t*) childp);
        }

        /* Check if the positions of the child and the parent in the min heap
         * should be swapped. */ 
        if (child_val < parent_val)
        {
            /* The child has a lower value than the parent so swap them. */
            array_set_data(&(*mhp)->heap, child_index, parentp);
            array_set_data(&(*mhp)->heap, parent_index, childp);

            /* Repeat this function on the same value. */
            min_heap_float_up(mhp, parent_index);
        }
    }
}

/**
 * This function swaps the value at the index provided to it, which is in the
 * min_heap also provided's storage, with the smaller of its two children. The
 * function then calls itself recursively, moving the value down through the
 * heap until a minimum heap state is satisfied. 
 */
void min_heap_sink_down(min_heap* mhp, int parent_index)
{
    /* This is a pointer to the parent's left child. */
    void* leftp;

    /* iThis is a pointer to the parent's right child. */
    void* rightp;

    /* This is a temporary pointer for swapping. */
    void* tempp;

    /* This is the minimum of the children's values. */
    uint64_t min_val;

    /* This is the value of the storage element at the index provided to
     * this function. */
    uint64_t parent_val;

    /* This is the index of the parent's left child in the heap's storage. */
    uint64_t left_index;

    /* This is the index of the parent's right child in the heap's storage. */
    uint64_t right_index;

    /* This is the minimum of the parent's, left and right childs' values. */
    uint64_t min_index;

    /* Calculate the indices of the two children. */
    left_index = (parent_index * 2) + 1;
    right_index = (parent_index * 2) + 2;

    /* Default the minimum of the parent and child values index to the 
     * parent's index. */
    min_index = parent_index;

    /* Check the minimum value between the children. 
     * There may not necessarily be any children. First we determine if there
     * are two children */
    if (left_index < (*mhp)->num_elems && right_index < (*mhp)->num_elems)
    {
        /* Get the children from the heap storage. */
        leftp = array_get_data((*mhp)->heap, left_index);
        rightp = array_get_data((*mhp)->heap, right_index);

        /* Compare the values of the children and record the index of the child
         * with the lower/minimum value between the two. */
        min_index = *((uint64_t*) leftp) < 
            *((uint64_t*) rightp) ? left_index : right_index;
    }
    /* Check if there is only one child. The left child always has a
     * higher indices in the heap's storage than the right child. */
    else if (left_index < (*mhp)->num_elems)
    {
        /* There is only a left child so set that as the child with the
         * lower/minimum value between the children. */
        min_index = left_index;    
    } 

    /* Check if there were any children. */
    if (min_index != parent_index)
    {
        /* Get the minimum child value and the parent value. */
        min_val = *((uint64_t*) array_get_data((*mhp)->heap, min_index));
        parent_val = *((uint64_t*) array_get_data((*mhp)->heap, parent_index));

        /* Check if a value lower than the parent's was found. */
        if (min_val < parent_val)
        {
            /* The child's value is lower than the parent so swap them. */
            tempp = array_get_data((*mhp)->heap, min_index);
            array_set_data(&(*mhp)->heap, 
                    min_index, array_get_data((*mhp)->heap, parent_index));
            array_set_data(&(*mhp)->heap, parent_index, tempp);

            /* Call this function on the original value that was at the
             * index provided to this function. */
            min_heap_sink_down(mhp, min_index);
        }
    }
}

