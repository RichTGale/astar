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
 * Version: 1.0.0
 * File version: 1.0.1
 * Author: Richard Gale
 */

#include "node.h"

/**
 * The internal data-structure of the node type.
 */
struct node_data {
    
    /* This is the neighbouring nodes. */
    array neighbours;

    /* This is the weighted edges of the neighbouring nodes. */
    array edges;

    /* This is the node preceeding this node on the path that was
     * created by the astar algorithm. */
    node* came_from;

    /* These are the node's coordinates in the graph. */
    uint8_t x;
    uint8_t y;
    uint8_t z;

    /* This is the estimated cost of the path that was created by the astar
     * algorithm from the start node to the goal node if the path was to go through
     * this node. */
    uint64_t f;

    /* This is the cost of the path from the start node to this node. */
    uint64_t g;

    /* The type of node this is e.g PASSABLE, IMPASSABLE. */
    enum node_type type;
};

/**
 * This function initialises the node provided to it.
 */
void node_init(node* np, uint8_t x, uint8_t y, uint8_t z, enum node_type type)
{
    /* Allocate memory to the node. */
    *np = (node) malloc(sizeof(struct node_data));

    /* Initialise the node's internal data. */
    array_init(&(*np)->neighbours);
    array_init(&(*np)->edges);
    (*np)->came_from = NULL;
    (*np)->x = x;
    (*np)->y = y;
    (*np)->z = z;
    (*np)->f = UINT64_MAX;
    (*np)->g = UINT64_MAX;
    (*np)->type = type;
}

/**
 * This function destroys the node provided to it.
 */
void node_free(node* np)
{
    /* The index of the current edge. */
    uint64_t e;

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
 * This function returns the node on a path created by the astar algorithm
 * that preceeds the node provided to this function on that path.
 */
node* node_get_came_from(node n)
{
    /* Return the preceeding node on the path. */
    return n->came_from;
}

/**
 * This function returns the edges of the node provided it.
 */
array node_get_edges(node n)
{
    /* Return the node's edges. */
    return n->edges;
}

/**
 * This function returns the array of neighbours of the node provided to it.
 */
array node_get_neighbours(node n)
{
    /* Return the node's neighbours. */
    return n->neighbours;
}

/**
 * This function is passed two nodes as its parameters. If the second node is a
 * neighbour of the first, this function will return the edge of the second
 * node that is relevant to the first node. 
 */
edge* node_get_neighbouring_edge(node* np1, node n2)
{
    array edges;        /* The edges of neighbouring nodes. */
    edge* e;            /* The current edge. */
    uint32_t i;         /* The index of the current edge. */
    bool edge_found;    /* Whether the edge was found. */

    /* Presume the edge won't be found. */
    edge_found = false;

    /* Get the edges of the neighbouring node. */
    edges = node_get_edges(n2);

    /* Search for the relevant edge. */ 
	for (i = 0; i < array_size(edges) && !edge_found; i++)
    {
        e = (edge*) array_get_data(edges, i);
        if (np1 == (node*) edge_get_neighbourp(e))
        {
            /* The relevant edge of the neighbour was found. */
            edge_found = true;
        }
    }

    /* Check that an edge was found. */
    if (!edge_found)
    {
        /* The edge wasn't found so print an error and exit the program. */
        fprintf(stdout,
                "\nERROR: in function node_get_neighbouring_edge(): an edge"
                " wasn't found!\n");
        exit(EXIT_FAILURE);
    }

    /* Return the edge. */
    return e;
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
 * This function returns the cost of a path from its start to the node provided
 * to this function.
 */
uint64_t node_get_g(node n)
{
    return n->g;
}

/**
 * This function returns the node-type of the node provided to this procedure.
 */
enum node_type node_get_type(node n)
{
    return n->type;
}

/**
 * This function sets which node on a path created by the astar algorithm
 * preceeds the node provided to this function on that path.
 */
void node_set_came_from(node* n, node* came_from)
{
    (*n)->came_from = came_from;
}

/**
 * This function sets the estimated total cost of a path from the start
 * node to the goal node if the path goes through the node provided to this
 * function.
 */
void node_set_f(node* n, uint64_t f)
{
    (*n)->f = f;
}

/**
 * This function sets the cost of a path from its start to the node provided
 * to this function.
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
    /* This stores whether the nodes provided to this function are already
     * neighbours. */
    bool already_neighbours;

    /* This is the new edge of the "to" node. */
    edge* edgep;

    /* This is a neighbour of the "to" node. */
    node* neighbourp;

    /* This is the coordinates of the node that the edges of the "to" node
     * belong to. */
    uint8_t x;
    uint8_t y;
    uint8_t z;

    /* This is the index of the edge in the "to" node's edges array. */
    uint64_t e;

    /* Presume the two nodes are not already neighbours. */
    already_neighbours = false;
    
    /* Check if the nodes are already neighbours. */
    for (e = 0 ; e < array_size((*top)->edges); e++)
    {
        neighbourp = (node*) edge_get_neighbourp(
                ((edge*) array_get_data((*top)->edges, e)));
        if (fromp == neighbourp)
        {
            /* The nodes were already neighbours. */
            already_neighbours = true;
        }
    }

    /* Connect the nodes so they will be considered neighbours. */
    if (!already_neighbours)
    {
        /* Allocate memory to the new edge. */
        edgep = (edge*) malloc(sizeof(edge));

        /* Initialise the the new edge. */
        edge_init(&(edgep[0]), fromp, weight);

        /* Add the new edge to the "to" node. */
        array_push_back(&(*top)->edges, &(edgep[0]));

        /* Add the "to" node to the "from" node's array of neighbours. */
        node_add_neighbour(fromp, top);
    }
    else
    {
        /* The nodes provided to this function were already neighbours so print
         * a warning. */
        fprintf(stdout,
                "\nWARNING: In function node_add_edge(): "
                "Node at coords (%d,%d,%d) was already a neighbour of the "
                "node at coords (%d,%d,%d) and wasn't added again!\n", 
                node_get_x(*fromp), node_get_y(*fromp), node_get_z(*fromp), 
                node_get_x(*top), node_get_y(*top), node_get_z(*top));
    }
}

/**
 * This function adds neighbour provided to it to the node also provided's
 * array of neighbours.
 */
void node_add_neighbour(node* np, node* neighbourp)
{
    array_push_back(&(*np)->neighbours, neighbourp); 
}

/**
 * This function removes the neighbour provided to it from the node also
 * provided's array of neighbours.
 */
void node_remove_neighbour(node* np, node* neighbourp)
{
    array neighbours;           /* The array of neighbours. */
    node* neighbour;            /* The current neighbour. */
    uint32_t num_neighbours;    /* The number of neighbours in the array. */
    uint32_t i;                 /* The index of the current neighbour. */

    /* Get the array of neighbours. */
    neighbours = node_get_neighbours(*np);

    /* Get the number of neighbours in the array. */
    num_neighbours = array_size(neighbours);

    /* Search for the correct neighbour in the array. */
    for (i = 0; i < num_neighbours; i++)
    {
        /* Get the current neighbour. */
        neighbour = array_get_data(neighbours, i);
        
        /* Check if it's the correct neighbour. */
        if (neighbour == neighbourp)
        {
            /* The correct neighbour was found so remove it from the array. */
            array_pop_data(&neighbours, i);
        }
    }
}

/**
 * This function resets the node to its original state.
 */
void node_reset(node* np)
{
    /* Reset the node's internal data. */
    (*np)->came_from = NULL;
    (*np)->f = UINT64_MAX;
    (*np)->g = UINT64_MAX;
}

/**
 * This function removes a connection from one node from another, stopping
 * the "to" node from being considered a neighbour of the "from" node.
 * Note: this is a one-way disconnection.
 */
void node_remove_edge(node* fromp, node* top)
{
    /* This is a neighbour of the "to" node. */
    node* neighbourp;

    /* This stores whether the nodes were already neighbours. */
    bool already_neighbours = false;

    /* These are the coordinates of the node that the edges of the "to" node
     * belong to. */
    uint8_t x;
    uint8_t y;
    uint8_t z;

    /* This is the index of the current edge in the "to" node's edges array. */
    uint64_t e;

    /* Presume the nodes provided to this function are not neighbours. */
    already_neighbours = false;

    /* Check if the nodes provided to this function are neighbours, and get
     * the index of the edge we need to remove. */
    for (e = 0 ; e < array_size((*top)->edges); e++)
    {
        /* Get a neighbouring node. */
        neighbourp = (node*) edge_get_neighbourp(
                ((edge*) array_get_data((*top)->edges, e)));
        
        /* Check if the nodes are neighbours. */
        if (fromp == neighbourp)
        {
            /* The nodes are already neighbours. */
            already_neighbours = true;

            /* Remove the edge. The nodes will no longer be considered
             * neighbours. */
            array_pop_data(&(*top)->edges, e);

            /* Remove the "to" node from the "from" node's array of 
             * neighbours. */
            node_remove_neighbour(fromp, top);
        }
    }
    
    /* Check if the nodes weren't neighbours. */
    if (!already_neighbours)
    {
        /* The nodes provided to this function were not neighbours so print a
         * warning. */
        fprintf(stdout,
                "\nWARNING: In function node_remove_edge(): "
                "Node at coords (%d,%d,%d) wasn't a neighbour of the "
                "node at coords (%d,%d,%d) so it wasn't removed!\n", 
                node_get_x(*top), node_get_y(*top), node_get_z(*top),
                node_get_x(*fromp), node_get_y(*fromp), node_get_z(*fromp));
    }
}

/**
 * This function initialises the edges that belong to the neighbouring nodes 
 * of the node provided to this function.
 */
void node_init_edges(node* np, uint8_t* weights)
{
    /* This is the neighbour the edge belongs to. */
    node* neighbour;

    /* This is the array of neighbouring edges. */
    edge* edges;

    /* This is the neighbouring node's coordinates. */
    uint8_t x;
    uint8_t y;
    uint8_t z;

    /* This is the index of the current edge. */
    uint64_t e;

    /* This is the weight of the neighbour's edge. */
    uint8_t w;

    /* Allocate memory for all the edges. */
    edges = (edge*) malloc(array_size((*np)->neighbours) * sizeof(edge));

    /* Initialise and add the edges to the neighbours of the node provided to
     * this function. */
    for (e = 0; e < array_size((*np)->neighbours); e++)
    {
        /* Get the neighbouring node that the edge belongs to. */
        neighbour = (node*) array_get_data((*np)->neighbours, e);

        /* Get the weight of the edge. */
        w = weights[e];

        /* Initialise the edge. */
        edge_init(&(edges[e]), np, w);

        /* Give the edge to the neighbour it belongs to. */
        array_push_back(&(*neighbour)->edges, &(edges[e]));
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
