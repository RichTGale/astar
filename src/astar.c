/**
 * astar.c
 * 
 * This file contains the internal data-structure and function definitions
 * for the astar type.
 *
 * The astar type is an implementation of the A* (A Star) search algorithm. It
 * finds the shortest path between two nodes on a weighted graph.
 * 
 * Author: RIchard Gale
 * Astar version: 1.0.0
 * File version: 1.0.1
 */

#include "astar.h"

/** 
 * This is internal data-structure of the astar type.
 */
struct astar_data {
    graph* g_ref;		/* The graph. */
    min_heap openset;	/* The openset. */
    array path;			/* The nodes that make up the shortest path. */
};

/**
 * This function initialises the astar that is provided to it.
 */
void astar_init(astar* as_ref, graph* g_ref)
{
    /* Allocate memory to the astar. */
    *as_ref = (astar) malloc(sizeof(struct astar_data));

    /* Initialise the astar's properties. */
    (*as_ref)->g_ref = g_ref;
    min_heap_init(&(*as_ref)->openset, NODE);
    array_init(&(*as_ref)->path);
}

/**
 * This function destroys the astar that is provided to it.
 */ 
void astar_free(astar* as_ref)
{
    /* Destroy the astar's properties. */
    min_heap_free(&(*as_ref)->openset);
    array_free(&(*as_ref)->path);

    /* De-allocate memory from the astar. */
    free(*as_ref);
}

/**
 * This function returns an array containing the nodes that make up the
 * shortest path found by the search function. The array is empty if no path
 * was found by the search procedure. 
 */
array astar_get_path(astar as)
{
    /* Return the shortest path. */
    return as->path;
}

/**
 * This is astar's heuristic function. This function returns an estimate of
 * the distance between two graph-nodes.
 */
uint32_t astar_h(node node_a, node node_b, enum graph_styles style)
{
    uint64_t cost;  /* The estimated distance between the two nodes. */
    uint8_t dx;	    /* The absolute difference of the x axes. */
    uint8_t dy;	    /* The absolute difference of the y axes. */
    uint8_t dz;	    /* The absolute difference of the z axes. */
    uint8_t min; 	/* The minimum absolute difference out of all the axes. */
	
    /* Calculate the absolute differences of each axis of the two nodes. */
    dx = abs(node_get_x(node_a) - node_get_x(node_b));
    dy = abs(node_get_y(node_a) - node_get_y(node_b));
    dz = abs(node_get_z(node_a) - node_get_z(node_b));

    /* Estimate the cost. */
    if (style == MANHATTAN)
    {
        cost = dx + dy + dz; 
    } 
    else if (style == DIAGONAL)
    {
        min = dx < dy ? dx : dy;
        min = min < dz ? min : dz;
        cost = (dx + dy + dz) + (1 - 3) * min;
    }

    /* Return the estimated cost. */
    return cost;
}

/**
 * This function reconstructs the shortest path going from the starting node
 * to the goal node that the search procedure found.
 */
void astar_reconstruct_path(astar* as, node* start, node* current)
{
    /* Add the goal goal node to the array. */
    array_push_front(&(*as)->path, current);

    /* Travel backwards along the path adding each node on it to the
     * front of the array. */
    while(current != start)
    {
        current = node_get_came_from(*current);
        array_push_front(&(*as)->path, current);
    }
}

/**
 * This function resets the astar to its original state so it is ready to
 * search again.
 */
void astar_reset(astar* as_ref)
{
    /* Reset the graph */
    graph_reset((*as_ref)->g_ref);

    /* Empty the openset. */
    while (!(min_heap_is_empty((*as_ref)->openset)))
    {
        min_heap_pop_min(&(*as_ref)->openset);
    }

    /* Empty the previously found path. */
    while (array_size((*as_ref)->path) > 0)
    {
        array_pop_front(&(*as_ref)->path);
    }
}

/**
 * This is the A* search algorithm. It searches for the shortest path from
 * the start node to the end node.
 */
void astar_search(astar* as_ref, node* start, node* end)
{
    array edges;        // The edges of a neighbouring node
    node* current;      // The current node on the path
    node* neighbour;    // A neighbour of the current node on the path.
    edge* e;            // The edge separating the current node and neighbour.
    bool path_found;    // Whether a path has been found
    uint64_t next_g;    // Cost from start to neighbour through the current node
    uint64_t i;         // The index of the edge we're assessing from the openset

    // Resetting the astar to its original state
    astar_reset(as_ref);

    // A path has not yet been found
    path_found = false;

    // Adding the start node to the minimum heap
    min_heap_add(&(*as_ref)->openset, start);

    // Setting the start node's distance from the start node
    node_set_g(start, 0);

    // Searching the graph
    while (!(min_heap_is_empty((*as_ref)->openset)) && !path_found)
    {
        // Getting the currently known node that has the lowest
        // estimated cost or distance from the start node to the end node
        current = (node*) min_heap_pop_min(&(*as_ref)->openset);

        if (current == end)
        {
            // Reconstructing the shortest path
            astar_reconstruct_path(as_ref, start, current);
            path_found = true;
        }
        else
        {
            // Assessing each edge of the current node
            for (i = 0; i < array_size(node_get_edges(*current)); i++)
            {
                // Assigning to some variables to make the code easier
                // to read.
                e = array_get_data(node_get_edges(*current), i);
                neighbour = graph_get_node(*(*as_ref)->g_ref, edge_get_x(*e), 
                                            edge_get_y(*e), edge_get_z(*e));
                edges = node_get_edges(*neighbour);
                for (int j = 0; j < array_size(edges); j++)
                {
                    e = (edge*) array_get_data(edges, j);
                    if (edge_get_x(*e) == node_get_x(*current) &&
                        edge_get_y(*e) == node_get_y(*current) &&
                        edge_get_z(*e) == node_get_z(*current))
                    {
                        break;
                    }
                }
                // Measuring the cost of this path to the neighbour.
                next_g = node_get_g(*current) + edge_get_w(*e);
                if (edge_get_w(*e) != 0 && next_g < node_get_g(*neighbour))
                {
                    // This path to the neighbour is better than any previous 
                    // one so we are recording it.
                    node_set_came_from(neighbour, current);
                    node_set_g(neighbour, next_g);

                    // Setting the estimation for total cost of the path if it 
                    // goes through neighbour.
                    node_set_f(neighbour, next_g + astar_h(*neighbour, *end, 
                                        graph_get_style(*(*as_ref)->g_ref)));

                    // We only need to add the neighbour to the openset
                    // if it's not yet in there.
                    if (!min_heap_val_exists((*as_ref)->openset, neighbour))
                    {
                        // Adding the neighbour to openset.
                        min_heap_add(&(*as_ref)->openset, neighbour);
                    }
                }
            }
        }
    }
}





