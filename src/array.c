/**
 * array.c
 *
 * This file contains the internal data-structure and function definitions 
 * for the array type.
 *
 * The array type is a singly-linked list. It dynamically allocates and
 * de-allocates memory as elements are added to it and removed from it.
 *
 * Version: 1.0.0
 * File version: 1.0.1
 * Author: Richard Gale
 */

#include "array.h"

/** 
 * This is the maximum number of elements the array can store.
 */
#define MAX_CAPACITY UINT64_MAX

/**
 * This is the internal data-structure of the array type.
 */
struct array_data {
    void* data; /* The data that the node contains. */
    array next; /* The next element in the array. */
};

/**
 * This function initialises the array provided to it.
 */
void array_init(array* ap)
{
    /* Allocate memory to the array. */
    *ap = (array) malloc(sizeof(struct array_data));

    /* Initialise internal properties. */
    (*ap)->data = NULL;
    (*ap)->next = NULL;
}

/**
 * This function destroys the array provided to it.
 */
void array_free_elem(array* ap)
{
    /* De-allocate memory from the array. */
    free(*ap);
}
/**
 * This function destroys the array provided to it as well as any array
 * elements linked to it.
 */
void array_free(array* ap)
{
    /* Check if an array element is linked to the array. */
    if ((*ap)->next != NULL)
    {
        /* Destroy the array element and any elements linked to it. */
        array_free(&(*ap)->next);
    }

    /* De-allocate memory from the array. */
    array_free_elem(ap);
}

/**
 * This function returns the data stored at the index provided to it from the
 * array that is also provided to the function.
 */ 
void* array_get_data(array a, uint64_t index)
{
    uint64_t elem;  /* The current element of the array. */ 

    /* Move to the appropriate array index. */
    for (elem = 0; elem < index; elem++)
    {
        /* Check if an array element is linked to the current element. */
        if (a->next != NULL)
        {
            /* Move to the next array element. */
            a = a->next;
        }
        else
        {
            /* There was no array element linked to the current element,
             * so print an error and exit the program. */
            fprintf(stdout,
                    "\nERROR: In function array_get_data(): index %ld"
                    " out of bounds!\n", index);
            exit(EXIT_FAILURE);
        }
    }
    /* Return the data contained in the array element that was at the index
     * provided to this function. */
    return a->data;
}

/**
 * This function returns the number of elements in the array provided to it.
 */
uint64_t array_size(array a)
{
    uint64_t size; /* The number of elements in the array. */
 
    /* Presume the array is empty. */
    size = 0;

    /* Check if the array element that was supplied to this function contains
     * any data. */
    if (a->data != NULL)
    {
        /* The array element contains data so count it. */
        size++;

        /* Check if there are array elements linked to the current array
         * element. */
        while (a->next != NULL)
        {
            /* The current array element has an element linked to it so
             * count it. */
            size++;

            /* Move to the next array element. */
            a = a->next;
        }
    }
    /* Return the size of the array. */
    return size;
}

/**
 * This function removes the first element from the array provided to it, then
 * returns it.
 */
void* array_pop_front(array* ap)
{
    /* This is a copy of the array starting from the second element. */
    array next;

    /* This is a copy of the data contained in the array's first element. */
    void* front; 

    /* Check if the array is storing any data. */
    if (array_size(*ap) > 0)
    {
        /* Copy the data stored in the first element of the array. */
        front = (*ap)->data;

        /* Copy the second element of the array. */
        next  = (*ap)->next;

        /* Destroy the first element. */ 
        array_free_elem(ap);

        /* Point the head at the second element. */ 
        *ap = next;

        /* The array provided to this function may have contained only one
         * element. If this was the case, then initialise the element we just
         * stored at the array head, which was previously the uninitialised
         * second element. */
        if (*ap == NULL)
        {
            /* Initialise the array head. */
            array_init(ap);
        }
    }
    else
    {
        /* The array passed to this function has a size of zero so print an
         * error and exiting the program. */
        fprintf(stdout,
                "\nERROR: In function array_pop_front: Attempting to pop " 
                "front of empty array!\n");
        exit(EXIT_FAILURE);
    }

    /* Return the first element of the array that was passed to this
     * function. */
    return front;
}

/**
 * This function removes the last element from the array provided to it, then 
 * returns it.
 */
void* array_pop_back(array* ap)
{ 
    /* This is the data contained in the last element of the array. */
    void* back;

    /* This is the number of elements in the array. */
    uint64_t size;

    /* Get the size of the array. */
    size = array_size(*ap);

    /* Check if there is any data stored in the array. */
    if (size > 0)
    {
        /* Loop to the last element in the array. */
        while ((*ap)->next != NULL)
        {
            /* Move to the next element. */
            ap = &(*ap)->next;
        }

        /* Copy the data stored in the last element of the array. */
        back = (*ap)->data;

        /* Destroy the last element in the array. */
        array_free_elem(ap);

        /* Deal with the element we just destroyed. */
        if (size > 1)
        {
            /* Re-initialising the previous array element's "next" property. */
            *ap = NULL;
        }
        else
        {
	        /* The array provided to this function may have contained only one
	         * element. If this was the case, then initialise the first
             * element because we just destroyed it. */
            array_init(ap);
        }
    }
    else
    {
        /* There was no data stored in the array provided to this function,
         * so print an error and exit the program. */
        fprintf(stdout,
                "\nERROR: In function array_pop_back: Attempting to pop "
                "back of empty array!\n");
        exit(EXIT_FAILURE);
    }

    /* Return the data that was stored in the last element of the array
     * provided to this function. */
    return back;
}

/**
 * This function removes the element from the array provided to it which is at
 * the index provided to the function, then returns it.
 */
void* array_pop_data(array* ap, uint64_t index)
{
    /* This is a copy of the array starting from the element linked to the
     * element at the index provided to this function. */
    array next;

    /* This is the data contained in the array element at the index provided to
     * this function. */
    void* data;

    /* This is the size of the array that was provided to this function. */
    uint64_t size;

    /* This is the index of the current element of the array. */
    uint64_t elem;

    /* Get the size of the array. */
    size = array_size(*ap);
    
    /* Check if the index passed to this function is within the bounds
     * of the array. */    
    if (index < size)
    {
        /* Move to the target array element. */
        for (elem = 0; elem < size; elem++)
        {
            if (elem == index)
            {
                /* Copy the data stored at the target element. */
                data = (*ap)->data;

                /* Copy the array element linked to the target element. */
                next  = (*ap)->next;

                /* De-allocate the memory of the target element. */
                array_free_elem(ap);

                /* Point the array head to the element that was linked to the
                 * target element.*/
                *ap = next;

                /* End the loop. */
                size = 0;
            }
            else
            {
                /* Move to the next element of the array. */
                ap = &(*ap)->next;
            }
        }
    }
    else
    {
        /* The index passed to this function was not within the bounds
         * of the array, so print an error message and exit the program. */
        fprintf(stdout,
                "\nERROR: In function array_pop_data(): index %ld out "
                "of bounds!\n", index);
        exit(EXIT_FAILURE);
    }

    /* Return the data that was stored at the target array element. */
    return data;
}

/**
 * This function adds a new element to the beginning of the array provided
 * to it.
 */
void array_push_front(array* ap, void* data)
{
    /* This is the new element to be added to the array. */
    array new;  

    /* Check if there is enough space in the array to add a new element. */
    if (array_size(*ap) < MAX_CAPACITY)
    {
        /* Check if the array is empty. */
        if ((*ap)->data == NULL)
        {
            /* There was no data stored in the array so store the data in the
             * first element. */
            (*ap)->data = data;
        }
        else
        {
            /* There was already data in the first element of the array, so
             * intialise the new element.*/
            array_init(&new);

            /* Store the data in the new array element. */
            new->data = data;

            /* Link the first element of the array to the new element
             * that was just created. */
            new->next = *ap;

            /* Point the head of the array to the new element. */
            *ap = new;
        }
    }
    else
    {
        /* There is no space in the array to add a new element so we print an
         * error message and exit the program. */
        fprintf(stdout,
                "\nERROR: In function array_push_front(): Array reached "
                "maximum capacity!\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * This function adds a new element to the end of the array provided to it.
 */
void array_push_back(array* ap, void* data)
{
    /* Check if there is enough space in the array to store a new element. */
    if (array_size(*ap) < MAX_CAPACITY)
    {
        /* Check if the array is empty. */
        if ((*ap)->data == NULL)
        {
            /* There was no data stored in the array so store the data in the
             * first element. */
            (*ap)->data = data;
        }
        else
        {
            /* There was already data in the array so we are move to the
             * last element. */
            while ((*ap)->next != NULL)
            {
                ap = &(*ap)->next;
            }

            /* Initialise a new element of the array. */
            array_init(&(*ap)->next);

            /* Store the data in the newly initialised element. */
            (*ap)->next->data = data;
        }
    }
    else
    {
        /* There was no space in the array to store a new element so print an
         * error message and exit the program. */
        fprintf(stdout,
                "\nERROR: In function array_push_back(): Array reached "
                "maximum capacity!\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * This function replaces the data in the array element of the array provided
 * to the function which is at the index also provided to the function.
 */
void array_set_data(array* ap, uint64_t index, void* data)
{
    /* This is the current array index. */
    uint64_t elem; 

    /* Move to the target array element. */
    for (elem = 0; elem < index; elem++)
    {
        if ((*ap)->next != NULL)
        {
            ap = &(*ap)->next;
        }
        else
        {
            /* The index provided to the function is beyond the bounds of the 
             * array so print an error message and exit the program. */
            fprintf(stdout,
                    "\nERROR: In function array_set_data(): index %ld "
                    "out of bounds!\n", index);
            exit(EXIT_FAILURE);
        }
    }

    /* Replace the data at the target array element. */
    (*ap)->data = data;
}
