/**
 * edge.h
 * 
 * This file contains the internal data-structure and function definitions
 * for the edge type.
 * An edge represents the cost in an astar algorithm to move from a graph
 * node to a neighbouring node.
 * 
 * Author: Richard Gale
 * Version: 17th June, 2023
 */

#include "edge.h"

/**
 * The internal data-structure of the edge type.
 */
struct edge_data {
    /* The coordinates of the relevant neighbour of the node this edge
     * belongs to. */
    uint8_t x;
    uint8_t y;
    uint8_t z;

    /* The weight/cost to move from the neighbour of the the node that this
     * edge belongs into the node this edge belongs to. */
    uint8_t w;
};

/**
 * This function initialises the edge at the edge pointer provided to it. 
 */
void edge_init(edge* ep, uint8_t x, uint8_t y, uint8_t z, uint8_t w)
{
    /* Allocating memory to the edge. */
    *ep = (edge) malloc(sizeof(struct edge_data));

    /* Initialising the edge's internal data. */
    (*ep)->x = x;
    (*ep)->y = y;
    (*ep)->z = z;
    (*ep)->w = w;
}

/**
 * This function de-allocates memory from the edge at the edge pointer
 * provided to it.
 */
void edge_free(edge* ep)
{
    free(*ep);
}

/**
 * This function returns the x coordinate of the relevant neighbour of the
 * node the edge provided to it belongs to.
 */
uint8_t edge_get_x(edge e)
{
    return e->x;
}

/**
 * This function returns the y coordinate of the relevant neighbour of the
 * node the edge provided to it belongs to.
 */
uint8_t edge_get_y(edge e)
{
    return e->y;
}

/**
 * This function returns the z coordinate of the relevant neighbour of the
 * node the edge provided to it belongs to.
 */
uint8_t edge_get_z(edge e)
{
    return e->z;
}

/**
 * This function returns the weight of the edge provided it.
 */
uint8_t edge_get_w(edge e)
{
    return e->w;
}

/**
 * This function prints information about the edge provided to it.
 */
void edge_print(edge e)
{
    fprintf(stdout, "Edge: { x:%d, y:%d, z:%d, w:%d }\n", e->x, e->y, e->z, e->w);
}
