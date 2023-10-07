/**
 * edge.c
 * 
 * This file contains the internal data-structure and function definitions for
 * an edge.
 *
 * An edge represents a distance between two nodes on a weighted graph, or the
 * cost to travel between the two nodes.
 * 
 * Astar version: 1.0.0
 * File version: 1.0.1
 * Author: Richard Gale
 */

#include "edge.h"

/**
 * This is the internal data-structure of the edge type.
 */
struct edge_data {
    uint8_t x;  /* The x coordinate of the node this edge belongs to. */
    uint8_t y;  /* The y coordinate of the node this edge belongs to. */
    uint8_t z;  /* The z coordinate of the node this edge belongs to. */
    uint8_t w;  /* The weight of the edge. */
};

/**
 * This function initialises the edge provided to it.. 
 */
void edge_init(edge* e_ref, uint8_t x, uint8_t y, uint8_t z, uint8_t w)
{
    /* Allocate memory to the endge. */
    *e_ref = (edge) malloc(sizeof(struct edge_data));

    /* Initialise the edge's properties. */
    (*e_ref)->x = x;
    (*e_ref)->y = y;
    (*e_ref)->z = z;
    (*e_ref)->w = w;
}

/**
 * This function destroys the edge provided to it.
 */
void edge_free(edge* e_ref)
{
    /* De-allocating memory from the edge. */
    free(*e_ref);
}

/**
 * This function returns the x coordinate of the node the edge provided to
 * the function belongs to.
 */
uint8_t edge_get_x(edge e)
{
    /* Return the x coordinate. */
    return e->x;
}

/**
 * This function returns the y coordinate of the node the edge provided to
 * the function belongs to.
 */
uint8_t edge_get_y(edge e)
{
    /* Return the y coordinate. */
    return e->y;
}

/**
 * This function returns the z coordinate of the node the edge provided to
 * the function belongs to.
 */
uint8_t edge_get_z(edge e)
{
    /* Return the z coordinate. */
    return e->z;
}

/**
 * This function returns the weight of the edge provided to it.
 */
uint8_t edge_get_w(edge e)
{
    /* Return the weight. */
    return e->w;
}
