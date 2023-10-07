/**
 * node.c
 * 
 * This file contains the internal data structure and function definitions for
 * the node type.
 *
 * The node type is a location on map. It represents a node on a weighted graph.
 *
 * This node was written for use in an A* (Astar) search algorithm.
 * 
 * Node version: 1.0.0
 * File version: 1.0.0
 * Author: Richard Gale
 */

#include "node.h"

/**
 * This is the internal data structure of the node type.
 */
struct node_data {
    array edges;     /* The edges of the node's neighbour's. */
    node* came_from; /* The node preceeding this node on the path. */
    uint8_t x;       /* The node's x coordinate in the graph. */
    uint8_t y;       /* The node's y coordinate in the graph. */
    uint8_t z;       /* The node's z coordinate in the graph. */
    uint64_t f;      /* The estimated total cost of path after going through this node. */
    uint64_t g;      /* The cost of the path from the start node to this node. */
};

/**
 * This function initialises the node provided to it.
 */
void node_init(node* np, uint8_t x, uint8_t y, uint8_t z)
{
    /* Allocate memory to the node. */
    *np = (node) malloc(sizeof(struct node_data));

    /* Initialise the node's properties. */
    array_init(&(*np)->edges);
    (*np)->came_from = NULL;
    (*np)->x = x;
    (*np)->y = y;
    (*np)->z = z;
    (*np)->f = UINT64_MAX;
    (*np)->g = UINT64_MAX;
}

/**
 * This function destroys the node provided to it.
 */
void node_free(node* np)
{
    uint64_t e; /* The index of the current edge. */

    /* Destroy the node's edges. */
    for (e = 0; e < array_size((*np)->edges); e++)
    {
        edge_free(array_get_data((*np)->edges, e));
    }
    array_free(&(*np)->edges);

    /* De-allocate memory from the node. */
    free(*np);
}

/**
 * This function returns the node that preceeded the node provided to the
 * function on a path.
 */
node* node_get_came_from(node n)
{
    return n->came_from;
}

/**
 * This function returns the x coordinate of the node provided to it.
 */
uint8_t node_get_x(node n)
{
    return n->x;
}

/**
 * This function returns the y coordinate of the node provided to it.
 */
uint8_t node_get_y(node n)
{
    return n->y;
}

/**
 * This function returns the z coordinate of the node provided to it.
 */
uint8_t node_get_z(node n)
{
    return n->z;
}

/**
 * This function returns the estimated total cost of a path if the path goes
 * through the node provided to the function.
 */
uint64_t node_get_f(node n)
{
    return n->f;
}

/**
 * This function returns the cost of a path from its start to the node
 * provided to the function.
 */
uint64_t node_get_g(node n)
{
    return n->g;
}

/**
 * This function returns the edges of the node provided to it.
 */
array node_get_edges(node n)
{
    return n->edges;
}

/**
 * This function sets the node provided to it with the node a path came from.
 */
void node_set_came_from(node* n, node* came_from)
{
    (*n)->came_from = came_from;
}

/**
 * This function sets the estimated total cost of a path if the path were to go 
 * through the node provided to the function.
 */
void node_set_f(node* n, uint64_t f)
{
    (*n)->f = f;
}

/**
 * This function sets the cost of a path from the path's starting point to
 * the node at the provided reference.
 */
void node_set_g(node* n, uint64_t g)
{
    (*n)->g = g;
}

/**
 * This functions resets the node provided to it to its original state.
 */
void node_reset(node* np)
{
    /* Reset the node's properties. */
    (*np)->came_from = NULL;
    (*np)->f = UINT64_MAX;
    (*np)->g = UINT64_MAX;
}

/**
 * This function initialises the edge of each neighbour of the node provided
 * to the function.
 */
void node_init_edges(node* np, array neighbours)
{
    node* neighbour;    /* The neighbour the edge belongs to. */
    edge* edges;        /* The array of edges. */
    uint8_t x;          /* The x coordinate of the node. */
    uint8_t y;          /* The y coordinate of the node. */
    uint8_t z;          /* The z coordinate of the node. */
    uint64_t e;         /* The index of the current edge. */

    /* Allocate memory for all the edges. */
    edges = (edge*) malloc(array_size(neighbours) * sizeof(edge));

    /* Initialise and add the edges to the node's neighbours. */
    for (e = 0; e < array_size(neighbours); e++)
    {
        neighbour = (node*) array_get_data(neighbours, e);
        x = (*np)->x;
        y = (*np)->y;
        z = (*np)->z;

        /* Here is where a weight/cost is given for moving from the node to
         * the neighbour. At the moment, every edge has a cost of 1. */
        edge_init(&(edges[e]), x, y, z, 1);
        array_push_back(&(*neighbour)->edges, &(edges[e]));
    }
}

/**
 * This function adds a connection from one graph node to another, making the
 * node the connection is to a neighbour of the node the connection is from..
 * Note, this creates a one-way connection.
 */
void node_add_edge(node* fromp, node* top, uint8_t weight)
{
    /* This stores whether the provided nodes are already neighbours. */
    bool already_neighbours; 
    
    edge* ep;    /* The edge seperating the nodes. */
    uint8_t x;      /* The x coordinate of the node an edge belongs to. */
    uint8_t y;      /* The y coordinate of the node an edge belongs to. */
    uint8_t z;      /* The z coordinate of the node an edge belongs to. */
    uint64_t e;     /* The index of the current edge. */

    /* Presume the nodes are already neighbours. */
    already_neighbours = false;

    /* Check if the nodes are already neighbours. */
    for (e = 0 ; e < array_size((*fromp)->edges); e++)
    {
        /* Get the coordinates of the node the current edge belongs to. */
        x = edge_get_x(*((edge*) array_get_data((*fromp)->edges, e)));
        y = edge_get_y(*((edge*) array_get_data((*fromp)->edges, e)));
        z = edge_get_z(*((edge*) array_get_data((*fromp)->edges, e)));

        /* Check if the nodes are already neighbours. */
        if ((*top)->x == x && (*top)->y == y && (*top)->z == z)
        {
            /* The nodes are already neighbours. */
            already_neighbours = true; // The nodes were already neighbours.
        }
    }

    /* Check if the nodes are not already neighbours. */
    if (!already_neighbours)
    {
        /* The nodes are not neighbours, so initialise the new edge and add
         * it to the node's array of edges. */
        ep = (edge*) malloc(sizeof(edge));
        edge_init(&(ep[0]), (*top)->x, (*top)->y, (*top)->z, weight);
        array_push_back(&(*fromp)->edges, &(ep[0]));
    }
    else
    {
        /* The node was already a neighbour so print a warning. */
        printf("\nWARNING: In function node_add_edge(): "
            "Node at coords (%d,%d,%d) was already a neighbour of the "
            "node at coords (%d,%d,%d) and wasn't added again!\n", 
            node_get_x(*top), node_get_y(*top), node_get_z(*top), 
            node_get_x(*fromp), node_get_y(*fromp), node_get_z(*fromp));
    }
}

/**
 * This function removes a connection from node from another, stopping the node
 * the connection is from from being a neighbour the connection is to.
 * Note, this is a one-way disconnection.
 */
void node_remove_edge(node* fromp, node* top)
{
    /* This stores whether the provided nodes are already neighbours. */
    bool already_neighbours; 

    uint8_t x;  /* The x coordinate of the node an edge belongs to. */
    uint8_t y;  /* The y coordinate of the node an edge belongs to. */
    uint8_t z;  /* The z coordinate of the node an edge belongs to. */
    uint64_t e; /* The index of the current edge. */

    /* Presume the nodes are not already neighbours. */
    already_neighbours = false;

    /* Remove the edge after checking that the nodes are neighbours. */
    for (e = 0 ; e < array_size((*fromp)->edges); e++)
    {
        /* Get the coordinates of the node the current edge belongs to. */
        x = edge_get_x(*((edge*) array_get_data((*fromp)->edges, e)));
        y = edge_get_y(*((edge*) array_get_data((*fromp)->edges, e)));
        z = edge_get_z(*((edge*) array_get_data((*fromp)->edges, e)));

        /* Check if the nodes are already neighbours. */
        if ((*top)->x == x && (*top)->y == y && (*top)->z == z)
        {
            /* The nodes are alrady neighbours. */
            already_neighbours = true;

            /* Remove the edge. */
            array_pop_data(&(*fromp)->edges, e); // Removing the edge.
        }
    }

    /* Check if the nodes are not already neighbours. */
    if (!already_neighbours)
    {
        /* The node wasn't a neighbour so print a warning. */
        printf("\nWARNING: In function node_remove_edge(): "
            "Node at coords (%d,%d,%d) wasn't a neighbour of the "
            "node at coords (%d,%d,%d) so it wasn't removed!\n", 
            node_get_x(*top), node_get_y(*top), node_get_z(*top), 
            node_get_x(*fromp), node_get_y(*fromp), node_get_z(*fromp));
    }
}

/**
 * This function prints the node.
 */
void node_print(node n)
{
    /* Print the node. */
    printf("{ node: x:%d, y:%d, z:%d, f:%" PRIu64 ", g:%" PRIu64 " }", 
            n->x, n->y, n->z, n->f, n->g);
}
