/**
 * edge.h
 * 
 * Data-structure and function definitions for an edge.
 * Simulates the an edge of a graph-node.
 * 
 * Author: Richard Gale
 * Version: 30th August, 2022
 */

#include "edge.h"

/**
 * The data contained in an the edge.
 */
struct edge_data {
    uint8_t x; // The x coordinates of the neighbour this edge is against.
    uint8_t y; // The y coordinates of the neighbour this edge is against.
    uint8_t z; // The z coordinates of the neighbour this edge is against.
    uint8_t  w; // The weight of the edge.
};

/**
 * Initialises the edge. 
 */
void edge_init(edge* e_ref, uint8_t x, uint8_t y, uint8_t z, uint8_t w)
{
    *e_ref = (edge) malloc(sizeof(struct edge_data));
    (*e_ref)->x = x;
    (*e_ref)->y = y;
    (*e_ref)->z = z;
    (*e_ref)->w = w;
}

/**
 * Frees the memory allocated to the edge. 
 */
void edge_free(edge* e_ref)
{
    free(*e_ref);
}

/**
 * Returns the x coordinate of the neighbour this edge is against.
 */
uint8_t edge_get_x(edge e)
{
    return e->x;
}

/**
 * Returns the y coordinate of the neighbour this edge is against.
 */
uint8_t edge_get_y(edge e)
{
    return e->y;
}

/**
 * Returns the z coordinate of the neighbour this edge is against.
 */
uint8_t edge_get_z(edge e)
{
    return e->z;
}

/**
 * Returns the weight of the edge.
 */
uint8_t edge_get_w(edge e)
{
    return e->w;
}