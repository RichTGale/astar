/**
 * min_heap.c
 * 
 * Data-structure and function definitions for a minimum heap.
 * 
 * Author: Richard Gale
 * Version: 30th August, 2022
 */

#include "min_heap.h"

// Error codes
#define HEAP_EMPTY_ERROR 1
#define HEAP_FULL_ERROR 2

#define MAX_CAPACITY UINT64_MAX // The number of value the heap can hold.

/**
 * The data contained in the min_heap data-structure
 */
struct min_heap_data {
    array heap;         // Stores the values in the heap.
    enum heap_types type;    // The type of data the min_heap stores
    uint64_t num_elems; // The number of elements in the heap.
};

/**
 * Initialises the min_heap at the provided reference.
 */
void min_heap_init(min_heap* mh_ref, enum heap_types t)
{
    *mh_ref = (min_heap) malloc(sizeof(struct min_heap_data));
    array_init(&(*mh_ref)->heap);
    (*mh_ref)->type = t;
    (*mh_ref)->num_elems = 0;
}

/**
 * Frees the memory allocated to the min_heap at the provided reference.
 */
void min_heap_free(min_heap* mh_ref)
{
    array_free(&(*mh_ref)->heap);
    free(*mh_ref);
}

/**
 * Returns true if the provided reference to a value is already 
 * in the min_heap.
 */
bool min_heap_val_exists(min_heap mh, void* val)
{
    bool val_exists = false;    // Whether the value is already in the min_heap.
    uint64_t i;                 // The index of the element in the heap we are comparing. 

    for (i = 0; i < array_size(mh->heap); i++)
    {
        if (val == array_get_data(mh->heap, i))
        {
            // The value is already in the min_heap
            val_exists = true;
        }
    }

    return val_exists;
}

/**
 * Returns true if the provided min_heap is empty.
 */
bool min_heap_is_empty(min_heap mh)
{
    bool is_empty = false;  // Whether the min_heap is empty

    if (mh->num_elems == 0)
    {
        // The min heap is empty
        is_empty = true;
    }
    
    return is_empty;
}

/**
 * Swaps the value in the min_heap at the provided index with its
 * parents value if it is a lower vaue than the parent, moving the 
 * value up through the heap until the minimum heap property is 
 * satisfied.
 */
void min_heapify_up(min_heap* mh_ref, int i)
{
    void* p_ref;    // The reference in the heap at the parent's index
    void* i_ref;    // The reference in the heap at the passed index 
    uint64_t p_val; // The value in the heap at the parent's index
    uint64_t i_val; // The value in the heap at the provided index 
    uint64_t p;     // The index of the parent of the value at the passed index 

    if (i > 0)
    {
        // Setting the parent's index
        p = (i - 1) / 2;

        // Getting the child's and the parent's references from the heap
        p_ref = array_get_data((*mh_ref)->heap, p);
        i_ref = array_get_data((*mh_ref)->heap, i);
        
        if ((*mh_ref)->type == NODE)
        {
            // Setting values for node type
            p_val = node_get_f(*((node*) p_ref));
            i_val = node_get_f(*((node*) i_ref));
        }
        else if ((*mh_ref)->type == INTEGER)
        {
            // Setting values for integer type
            p_val = *((uint64_t*) p_ref);
            i_val = *((uint64_t*) i_ref);
        }
        
        if (i_val < p_val)
        {
            // The child has a lower value than the parent so we swap them.
            array_set_data(&(*mh_ref)->heap, i, p_ref);
            array_set_data(&(*mh_ref)->heap, p, i_ref);
            min_heapify_up(mh_ref, p);
        }
    }
}

/**
 * Adds a reference to a value to the min_heap.
 */
void min_heap_add(min_heap* mh_ref, void* data)
{
    if ((*mh_ref)->num_elems < MAX_CAPACITY)
    {
        array_push_back(&(*mh_ref)->heap, data);
        min_heapify_up(mh_ref, (*mh_ref)->num_elems);
        (*mh_ref)->num_elems++;
    }
    else
    {
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
void min_heapify_down(min_heap* mh_ref, int i)
{
    void* l_ref;    // The reference to the left child of the parent.
    void* r_ref;    // The reference to the right child of the parent.
    void* t_ref;    // Temporary reference for swapping.
    uint64_t m_val; // The minimum value out of the parent's two children.
    uint64_t i_val; // The value at the index provided to the procedure.
    uint64_t l;     // The index of the parent's left child.
    uint64_t r;     // The index of the parent's right child.
    uint64_t m;     // The index of the minimum value out of the parent, left and right children.

    // Determining the indices of the two children of the parent value
    l = (i * 2) + 1;
    r = (i * 2) + 2;

    // Defaulting the index of the minimum value between the parent's
    // children to the parent's index.
    m = i;

    // Determining which child of the parent has the lowest value.
    // There may not necessarily be any children.
    if (l < (*mh_ref)->num_elems && r < (*mh_ref)->num_elems)
    {
        l_ref = array_get_data((*mh_ref)->heap, l);
        r_ref = array_get_data((*mh_ref)->heap, r);

        // Comparing the values of the two children
        if ((*mh_ref)->type == NODE)
        {
            m = node_get_f(*((node*) l_ref)) < node_get_f(*((node*) r_ref)) ? l : r;
        }
        else if ((*mh_ref)->type == INTEGER)
        {
            m = *((uint64_t*) l_ref) < *((uint64_t*) r_ref) ? l : r;
        }
    } 
    else if (l < (*mh_ref)->num_elems)
    {
        m = l;    
    } 

    if (m != i)
    {
        // Getting the minimum child's value and the parent's value.
        if ((*mh_ref)->type == NODE)
        {
            // Getting child's and parent's values from node data type
            m_val = node_get_f(*((node*) array_get_data((*mh_ref)->heap, m)));
            i_val = node_get_f(*((node*) array_get_data((*mh_ref)->heap, i)));
        }
        else if ((*mh_ref)->type == INTEGER)
        {
            // Getting child's and parent's values from integer data type
            m_val = *((uint64_t*) array_get_data((*mh_ref)->heap, m));
            i_val = *((uint64_t*) array_get_data((*mh_ref)->heap, i));
        }

        if (m_val < i_val)
        {
            // The child has a lower value than the parent so we swap them.
            t_ref = array_get_data((*mh_ref)->heap, m);
            array_set_data(&(*mh_ref)->heap, m, array_get_data((*mh_ref)->heap, i));
            array_set_data(&(*mh_ref)->heap, i, t_ref);

            // Trickling down
            min_heapify_down(mh_ref, m);
        }
    }
}

/**
 * Returns the minimum value in the heap.
 */
void* min_heap_get_min(min_heap mh)
{
    return array_get_data(mh->heap, 0);
}

/**
 * Removes the minimum value from the heap and returns it.
 */
void* min_heap_pop_min(min_heap* mh_ref)
{
    void* min;  // The minimum value in the heap.

    if ((*mh_ref)->num_elems > 1)
    {
        min = min_heap_get_min(*mh_ref);
        array_set_data(&(*mh_ref)->heap, 0, array_pop_back(&(*mh_ref)->heap));
        (*mh_ref)->num_elems--;
        min_heapify_down(mh_ref, 0);
    } 
    else if ((*mh_ref)->num_elems == 1)
    {
        min = array_pop_back(&(*mh_ref)->heap);
        (*mh_ref)->num_elems--;
    } 
    else
    {
        printf("ERROR: In function min_heap_pop_min(): heap is empty!");
        exit(HEAP_EMPTY_ERROR);
    }

    return min;
}
