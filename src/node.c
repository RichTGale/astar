/**
 * node.c
 * 
 * This file contains the internal data-structure and function definitions 
 * for the node type.
 * 
 * Author: Richard Gale
 * Version: 17th June, 2023
 */

#include "node.h"

/**
 * The internal data-structure of the node type.
 */
struct node_data {
    /* The weighted edges of the node's neighbours. */
    array edges;

    /* A pointer to the node preceeding this node on the path that was
     * created by the astar algorithm. */
    node* came_from;

    /* The node's coordinates in the graph. */
    uint8_t x;
    uint8_t y;
    uint8_t z;

    /* The estimated cost of the path that was created by the astar algorithm 
     * from the start node to the goal node if the path was to go through
     * this node. */
    uint64_t f;

    /* The cost of the path from the start node to this node. */
    uint64_t g;

    /* The type of node this is e.g PASSABLE, IMPASSABLE. */
    enum node_type type;
};

/**
 * This function initialises the node at the provided reference.
 */
void node_init(node* np, uint8_t x, uint8_t y, uint8_t z, enum node_type type)
{
    /* Allocating memory to the node. */
    *np = (node) malloc(sizeof(struct node_data));

    /* Initialising the array of neighbouring edges. */
    array_init(&(*np)->edges);

    /* There has not been any paths created by the astar algorithm. */
    (*np)->came_from = NULL;

    /* Setting the node's coordinates in the graph. */
    (*np)->x = x;
    (*np)->y = y;
    (*np)->z = z;

    /* Defaulting the path costs to maximum. */
    (*np)->f = UINT64_MAX;
    (*np)->g = UINT64_MAX;

    /* Setting the node's type. */
    (*np)->type = type;
}

/**
 * This function initialises the edges that belong to the neighbouring nodes 
 * of the node at the pointer that was provided to this function.
 */
void node_init_edges(node* np, array neighbours, uint8_t* weights)
{
    /* The neighbour the edge belongs to. */
    node* neighbour;

    /* The array of neighbouring edges. */
    edge* edges;    // The array of edges

    /* The neighbouring node's coordinates. */
    uint8_t x;
    uint8_t y;
    uint8_t z;

    /* The index of the current edge. */
    uint64_t e;

    /* The weight of the neighbour's edge. */
    uint8_t w;

    // Allocating memory for all the edges.
    edges = (edge*) malloc(array_size(neighbours) * sizeof(edge));

    // Initialising and adding the edges to the neighbours of the 
    // node provided to this function.
    for (e = 0; e < array_size(neighbours); e++)
    {
        /* Getting the neighbouring node that the edge belongs to. */
        neighbour = (node*) array_get_data(neighbours, e);

        /* Getting the weight of the edge. */
        w = weights[e];

        /* Getting the coordinates of the neighbour that the edge
         * belongs to. */
        x = (*np)->x;
        y = (*np)->y;
        z = (*np)->z;

        /* Initialising the edge. */
        edge_init(&(edges[e]), x, y, z, w);

        /* Giving the edge to the neighbour it belongs to. */
        array_push_back(&(*neighbour)->edges, &(edges[e]));
    }
}

/**
 * This function de-allocates memory from the node at the pointer
 * provided to this function as well as the memory allocated to its edges.
 */
void node_free(node* np)
{
    /* The index of the current edge. */
    uint64_t edge;

    /* de-allocating memory from the node's edges. */
    for (edge = 0; edge < array_size((*np)->edges); edge++)
    {
        edge_free(array_get_data((*np)->edges, edge));
    }
    array_free(&(*np)->edges);

    /* De-allocating memory from the node. */
    free(*np);
}

/**
 * This function returns the node on a path created by the astar algorithm
 * that preceeds the node provided to this function on that path.
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
 * This function returns the estimated total cost of a path from the start
 * node to the goal node if the path goes through the node provided to
 * this function.
 */
uint64_t node_get_f(node n)
{
    return n->f;
}

/**
 * This function returns the cost of a path from its start to the
 * node provided to this function.
 */
uint64_t node_get_g(node n)
{
    return n->g;
}


/**
 * This function returns the edges of the node provided to this procedure.
 */
array node_get_edges(node n)
{
    return n->edges;
}

/**
 * This function returns the node-type of the node provided to this procedure.
 */
enum node_type node_get_type(node n)
{
    return n->type;
}

/**
 * This function sets the node on a path created by the astar algorithm
 * that preceeds the node at the node pointer provided to this function 
 * on that path.
 */
void node_set_came_from(node* n, node* came_from)
{
    (*n)->came_from = came_from;
}

/**
 * This function sets the estimated total cost of a path from the start
 * node to the goal node if the path goes through the node at the node pointer
 * provided to this function.
 */
void node_set_f(node* n, uint64_t f)
{
    (*n)->f = f;
}

/**
 * This function sets the cost of a path from its start to the
 * node at the node pointer provided to this function.
 */
void node_set_g(node* n, uint64_t g)
{
    (*n)->g = g;
}

/**
 * This function adds a connection from one graph node to another, making the
 * "to" node be considered a neighbour of the "from" node.
 * Note: this creates a one-way connection.
 */
void node_add_edge(node* fromp, node* top, uint8_t weight)
{
    /* Whether the nodes provided to this function are already neighbours. */
    bool already_neighbours;

    /* The new edge of the "to" node. */
    edge* edgep;

    /* The coordinates of the node the edges of the "to" node belong to. */
    uint8_t x;
    uint8_t y;
    uint8_t z;

    /* The index of the edge in the "to" node's edges array. */
    uint64_t e;

    /* Presuming the two nodes are not already neighbours. */
    already_neighbours = false;
    
    /* Determining if the nodes are already neighbours. */
    for (e = 0 ; e < array_size((*top)->edges); e++)
    {
        /* Getting the coordinates of the node the current edge belongs to. */
        x = edge_get_x(*((edge*) array_get_data((*top)->edges, e)));
        y = edge_get_y(*((edge*) array_get_data((*top)->edges, e)));
        z = edge_get_z(*((edge*) array_get_data((*top)->edges, e)));

        /* Determining if the nodes are already neighbours. */
        if ((*fromp)->x == x && (*fromp)->y == y && (*fromp)->z == z)
        {
            /* The nodes were already neighbours. */
            already_neighbours = true;
        }
    }

    /* Connecting the nodes so they will be considered neighbours. */
    if (!already_neighbours)
    {
        /* Allocating memory to the new edge. */
        edgep = (edge*) malloc(sizeof(edge));

        /* Initialising the the new edge. */
        edge_init(&(edgep[0]), (*fromp)->x, (*fromp)->y, 
                                        (*fromp)->z, weight);

        /* Adding the new edge to the "to" node. */
        array_push_back(&(*top)->edges, &(edgep[0]));
    }
    else
    {
        /* The nodes provided to this function were already neighbours so we
         * are printing a warning. */
        printf("\nWARNING: In function node_add_edge(): "
            "Node at coords (%d,%d,%d) was already a neighbour of the "
            "node at coords (%d,%d,%d) and wasn't added again!\n", 
            node_get_x(*fromp), node_get_y(*fromp), node_get_z(*fromp), 
            node_get_x(*top), node_get_y(*top), node_get_z(*top));
    }
}

/**
 * This function resets the node to its original state.
 */
void node_reset(node* n_ref)
{
    (*n_ref)->came_from = NULL;
    (*n_ref)->f = UINT64_MAX;
    (*n_ref)->g = UINT64_MAX;
}

/**
 * This function removes a connection from one node from another, stopping
 * the "from" node from being considered a neighbour of the "to" node.
 * Note: this is a one-way disconnection.
 */
void node_remove_edge(node* fromp, node* top)
{
    /* Whether the nodes were already neighbours. */
    bool already_neighbours = false;

    /* The coordinates of the node the edges of the "to" node belong to. */
    uint8_t x;
    uint8_t y;
    uint8_t z;

    /* The index of the current edge in the "to" node's edges array. */
    uint64_t e;

    /* Presuming the nodes provided to this function are not neighbours. */
    already_neighbours = false;

    /* Determining if the nodes provided to this function are neighbours,
     * and getting the index of the edge we need to remove. */
    for (e = 0 ; e < array_size((*top)->edges); e++)
    {
        /* Getting the coordinates of the node the current edge belongs to. */
        x = edge_get_x(*((edge*) array_get_data((*top)->edges, e)));
        y = edge_get_y(*((edge*) array_get_data((*top)->edges, e)));
        z = edge_get_z(*((edge*) array_get_data((*top)->edges, e)));

        /* Determining if the nodes are neighbours. */
        if ((*fromp)->x == x && (*fromp)->y == y && (*fromp)->z == z)
        {
            /* The nodes were already neighbours. */
            already_neighbours = true;

            /* Removing the edge. The nodes will no longer be
             * considered neighbours. */
            array_pop_data(&(*top)->edges, e);
        }
    }
    
    /* Potentially printing a warning. */
    if (!already_neighbours)
    {
        /* The nodes provided to this function were not neighbours so we
         * are printing a warning. */
        printf("\nWARNING: In function node_remove_edge(): "
            "Node at coords (%d,%d,%d) wasn't a neighbour of the "
            "node at coords (%d,%d,%d) so it wasn't removed!\n", 
            node_get_x(*fromp), node_get_y(*fromp), node_get_z(*fromp), 
            node_get_x(*top), node_get_y(*top), node_get_z(*top));
    }
}

/**
 * This function prints information about the node provided to it.
 */
void node_print(node n)
{
    printf("{ node: x:%d, y:%d, z:%d, f:%" PRIu64 ", g:%" PRIu64 ", type:%d }", 
            n->x, n->y, n->z, n->f, n->g, n->type);
}
