/**
 * edge.c
 * 
 * This file contains the internal data-structure and function definitions for
 * an edge.
 *
 * An edge represents a distance between two nodes on a weighted graph, or the
 * cost to travel between the two nodes.
 * 
 * Version: 1.0.0
 * File version: 1.0.1
 * Author: Richard Gale
 */

#include "edge.h"

/**
 * This is the internal data-structure of the edge type.
 */
struct edge_data {
    /* These are the coordinates of the neighbour of the node this edge
     * belongs to. */
    void* neighbourp;

    /* This is the weight/cost to move from the neighbour of the the node that
     * this edge belongs to into the node this edge belongs to. */
    uint8_t w;
};

/**
 * This function initialises the edge provided to it. 
 */
void edge_init(edge* ep, void* neighbourp, uint8_t w)
{
    /* Allocate memory to the edge. */
    *ep = (edge) malloc(sizeof(struct edge_data));

    /* Initialise the edge's internal data. */
    (*ep)->w = w;
    (*ep)->neighbourp = neighbourp;
}

/**
 * This function destroys the edge provided to it.
 */
void edge_free(edge* ep)
{
    /* De-allocate memory from the edge. */
    free(*ep);
}

/**
 * This function returns the neighbouring node of the node that the edge
 * provided to the function belongs to.
 */
void* edge_get_neighbourp(edge* ep)
{
    /* Return the neighbouring node of the node the edge belongs to. */
    return (*ep)->neighbourp;
}

/**
 * This function returns the weight of the edge provided it.
 */
uint8_t edge_get_w(edge e)
{
    /* Return the weight of the edge. */
    return e->w;
}

/**
 * This function prints information about the edge provided to it.
 */
void edge_print(edge e)
{
    /* Print information about the edge. */
    fprintf(stdout, "Edge: { addr:%p w:%d }",  e->neighbourp, e->w);
}
