/**
 * array.c
 *
 * This file contains the internal data-structure and function definitions 
 * for a singly-linked-list, 
 * This is an array that dynamically allocates and de-allocates memory as 
 * elements are added to it and removed from it.
 *
 * Author: Richard Gale
 * Version: 17th June, 2023
 */

#include "array.h"

/** 
 * Error codes.
 */
#define INDEX_OUT_OF_BOUNDS_ERROR 1
#define ARRAY_EMPTY_ERROR 2
#define ARRAY_FULL_ERROR 3

/** 
 * Maximum capacity of the array.
 */
#define MAX_CAPACITY UINT64_MAX

/**
 * The internal data-structure of the array type.
 */
struct array_data {
    void* data; // The data that the node contains
    array next; // The next element in the array
};

/**
 * This function initialises the array at the provided array pointer.
 */
void array_init(array* ap)
{
    /* Allocating memory to the array. */
    *ap = (array) malloc(sizeof(struct array_data));

    /* Initialising internal properties. */
    (*ap)->data = NULL;
    (*ap)->next = NULL;
}

/**
 * This function de-allocates the memory of the array at the 
 * provided array pointer.
 */
void array_free_elem(array* ap)
{
    /* De-allocating memory from the array. */
    free(*ap);
}

/**
 * This function de-allocates the memory of the array at the 
 * provided array pointer and any arrays (elements) linked to it.
 */
void array_free(array* ap)
{
    /* Determining if an array element is linked to the array. */
    if ((*ap)->next != NULL)
    {
        /* De-allocating the memory from the array element linked to the
         * array. */
        array_free(&(*ap)->next);
    }

    /* De-allocating memory from the array. */
    array_free_elem(ap);
}

/**
 * This function returns a pointer to the data stored at the provided 
 * index in the provided array.
 * Once the data is returned, it should then be cast to the data-type
 * it was before it was placed in the array.
 */ 
void* array_get_data(array a, uint64_t index)
{
    /* The current element of the array. */
    uint64_t elem; 

    /* Moving to the appropriate array index. */
    for (elem = 0; elem < index; elem++)
    {
        /* Determining if an array element is linked to the current element. */
        if (a->next != NULL)
        {
            /* Moving to the next array element. */
            a = a->next;
        }
        else
        {
            /* There was no array element linked to the current element,
             * so we are printing an error and exiting the program. */
            printf("\nERROR: In function array_get_data(): index %d "
                                                "out of bounds!\n", index);
            exit(INDEX_OUT_OF_BOUNDS_ERROR);
        }
    }
    /* Returning the data contained in the array element that was at
     * the index provided to this function. */
    return a->data;
}

/**
 * This function returns the number of elements in the provided array.
 */
uint64_t array_size(array a)
{
    /* The number of elements in the array. */
    uint64_t size;
 
    /* Initialising our counting of the number of array elements. */
    size = 0;

    /* Determining if the array element (array head) that was supplied to
     * this function contains data. */
    if (a->data != NULL)
    {
        /* The array element (array head) contains data so we are
         * counting it. */
        size++;

        /* Determining if there are array elements linked to the current 
         * array element. */
        while (a->next != NULL)
        {
            /* The current array element has an element linked to it
             * so we are counting it. */
            size++;

            /* Moving to the next array element. */
            a = a->next;
        }
    }
    /* Returning the size of the array. */
    return size;
}

/**
 * This function removes the first element from the array at the array 
 * pointer provided to it and returns it.
 * Once the data is returned, it should then be cast to the data-type
 * it was before it was placed in the array.
 */
void* array_pop_front(array* ap)
{
    /* A copy of the array starting from the second element. */
    array next;

    /* A copy of the data contained in the first element. */
    void* front; 

    /* Determining if the array is storing any data. */
    if (array_size(*ap) > 0)
    {
        /* Copying the data stored in the first element of the array. */
        front = (*ap)->data;

        /* Copying the second element of the array. */
        next  = (*ap)->next;

        /* De-allocating memory from the first element. */ 
        array_free_elem(ap);

        /* Pointing the head at the second element. */ 
        *ap = next;

        /* The array provided to this function may have contained only one
         * element. If this was the case, then we need to initialise
         * the element we just stored at the array head, which was previously
         * the uninitialised second element. */
        if (*ap == NULL)
        {
            /* Initialising the array head. */
            array_init(ap);
        }
    }
    else
    {
        /* The array passed to this function has a size of zero so we
         * are printing an error and exiting the program. */
        printf("\nERROR: In function arrary_pop_front: Attempting to pop " 
                                                "front of empty array!\n");
        exit(ARRAY_EMPTY_ERROR);
    }

    /* Returning the first element of the array that was passed to
     * this function. */
    return front;
}

/**
 * This function removes the last element from the array at the array 
 * pointer provided to it and returns it.
 * Once the data is returned, it should then be cast to the data-type
 * it was before it was placed in the array.
 */
void* array_pop_back(array* ap)
{ 
    /* The data contained in the last element of the array. */
    void* back;

    /* The number of elements in the array. */
    uint64_t size;

    /* Getting the size of the array. */
    size = array_size(*ap);

    /* Determining if there is any data stored in the array. */
    if (size > 0)
    {
        /* Looping to the last element in the array. */
        while ((*ap)->next != NULL)
        {
            ap = &(*ap)->next;
        }

        /* Copying the data stored in the last element of the array. */
        back = (*ap)->data;

        /* De-allocating the memory from the last element in the array. */
        array_free_elem(ap);

        /* Dealing with the element we just destroyed. */
        if (size > 1)
        {
            /* Re-initialising the previous array element's "next" property. */
            *ap = NULL;
        }
        else
        {
	        /* The array provided to this function may have contained only one
	         * element. If this was the case, then we need to initialise
	         * the first element, because we just destroyed it. */
            array_init(ap);
        }
    }
    else
    {
        /* There was no data stored in the array provided to this function,
         * so we are printing an error and exiting the program. */
        printf("\nERROR: In function array_pop_back: Attempting to pop "
                                                "back of empty array!\n");
        exit(ARRAY_EMPTY_ERROR);
    }

    /* Returning the data that was stored in the last element of the array
     * provided to this function. */
    return back;
}

/**
 * This function removes the element from the array at the provided array 
 * pointer at the index provided to the function and returns it.
 * Once the data is returned, it should then be cast to the data-type
 * it was before it was placed in the array.
 */
void* array_pop_data(array* ap, uint64_t index)
{
    /* A copy of the array starting from the element linked to the element
     * at the index provided to this function. */
    array next;

    /* The data contained in the array element at the index provided to
     * this function. */
    void* data;

    /* The size of the array that was provided to this function. */
    uint64_t size;

    /* The index of the current element of the array. */
    uint64_t elem;

    /* Getting the size of the array. */
    size = array_size(*ap);
    
    /* Determining if index passed to this function is within the bounds
     * of the array. */    
    if (index < size)
    {
        /* Looping to the target array element. */
        for (elem = 0; elem < size; elem++)
        {
            if (elem == index)
            {
                /* Copying the data stored at the target element. */
                data = (*ap)->data;

                /* Copying the array element linked to the target element. */
                next  = (*ap)->next;

                /* De-allocating the memory of the target element. */
                array_free_elem(ap);

                /* Pointing the array head to the element that was linked to 
                 * the target element.*/
                *ap = next;

                /* Ending the loop. */
                size = 0;
            }
            else
            {
                /* Moving to the next element linked to the array. */
                ap = &(*ap)->next;
            }
        }
    }
    else
    {
        /* The index passed to this function was not within the bounds
         * of the array, so we are printing an error message and exiting 
         * the program. */
        printf("\nERROR: In function array_pop_data(): index %d out "
                                                "of bounds!\n", index);
        exit(INDEX_OUT_OF_BOUNDS_ERROR);
    }

    /* Returning the data that was stored at the target array element. */
    return data;
}

/**
 * This function adds a new element to the beginning of the array at
 * the provided array pointer.
 */
void array_push_front(array* ap, void* data)
{
    /* The new element to be added to the array. */
    array new;  

    /* Determining if there is enough space in the array to add a
     * new element. */
    if (array_size(*ap) < MAX_CAPACITY)
    {
        /* Adding the new element to the array. */
        if ((*ap)->data == NULL)
        {
            /* There was no data stored in the array. The first element should
             * already be intialised so we are free to simply store the data 
             * in it. */
            (*ap)->data = data;
        }
        else
        {
            /* There was already data in the first element of the array, so
             * here we intialise the new element.*/
            array_init(&new);

            /* Storing the data in the new array element. */
            new->data = data;

            /* Linking the first element of the array to the new element
             * we just created. */
            new->next = *ap;

            /* Pointing the head of the array to the new element. */
            *ap = new;
        }
    }
    else
    {
        /* There is no space in the array to add a new element so we
         * are printing an error message and exiting the program. */
        printf("\nERROR: In function array_push_front(): Array reached "
                                                    "maximum capacity!\n");
        exit(ARRAY_FULL_ERROR);
    }
}

/**
 * This function adds a new element to the end of the array at the provided
 * array pointer.
 */
void array_push_back(array* ap, void* data)
{
    /* Determining if there is enough space in the array to store a
     * new element. */
    if (array_size(*ap) < MAX_CAPACITY)
    {
        /* Determining if there is any data already stored in the array. */
        if ((*ap)->data == NULL)
        {
            /* There was no data stored in the array. The first element 
             * should already be intialised so we are free to simply
             * store the data in it. */
            (*ap)->data = data;
        }
        else
        {
            /* There was already data in the array so we are moving to the
             * last element in it. */
            while ((*ap)->next != NULL)
            {
                ap = &(*ap)->next;
            }

            /* Initialising a new element of the array. */
            array_init(&(*ap)->next);

            /* Storing the data in the newly initialised element. */
            (*ap)->next->data = data;
        }
    }
    else
    {
        /* There was no space in the array to store a new element so
         * we are printing an error message and exiting the program. */
        printf("\nERROR: In function array_push_back(): Array reached "
                                                "maximum capacity!\n");
        exit(ARRAY_FULL_ERROR);
    }
}

/**
 * This function replaces the data in the array element at the provided 
 * index of the array at the provided array reference.
 */
void array_set_data(array* ap, uint64_t index, void* data)
{
    /* The current array index. */
    uint64_t elem; 

    /* Looping to the target array element. */
    for (elem = 0; elem < index; elem++)
    {
        if ((*ap)->next != NULL)
        {
            ap = &(*ap)->next;
        }
        else
        {
            /* The index provided to the function is beyond the bounds
             * of the array, so we are printing an error message and exiting 
             * the program. */
            printf("\nERROR: In function array_set_data(): index %d "
                                            "out of bounds!\n", index);
            exit(INDEX_OUT_OF_BOUNDS_ERROR);
        }
    }

    /* Replacing the data at the target array element. */
    (*ap)->data = data;
}



