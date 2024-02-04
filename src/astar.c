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
 * The internal data-structure of the astar type.
 */
struct astar_data {
    graph* gp;          // The graph.
    min_heap openset;   // The priority queue
    array path;         // The nodes that make up the shortest path
};

/**
 * This is astar's heuristic function. This function returns an estimate of
 * the distance between two graph-nodes.
 */
uint32_t astar_h(node node_a, node node_b, enum graph_style style);

/**
 * This function reconstructs the shortest path going from the starting node
 * to the goal node that the search procedure found.
 */
void astar_reconstruct_path(astar* asp, node* start, node* current);

/**
 * This function intialises the astar provided to it.
 */
void astar_init(astar* asp, graph* gp)
{
    /* Allocate memory to the astar. */
    *asp = (astar) malloc(sizeof(struct astar_data));

    /* Initialise the astar's internal properties. */
    (*asp)->gp = gp;
    min_heap_init(&(*asp)->openset);
    array_init(&(*asp)->path);
}

/**
 * This function destroys the astar provided to it.
 */ 
void astar_free(astar* asp)
{
    /* Destroy the astar's internal properties. */
    min_heap_free(&(*asp)->openset);
    array_free(&(*asp)->path);

    /* De-allocate memory from the astar. */
    free(*asp);
}

/**
 * This function returns an array containing the nodes that make up the
 * shortest path found by the search function. The array is empty if no path
 * was found by the search procedure. 
 */
array astar_get_path(astar as)
{
    return as->path;
}

/**
 * This function resets the astar provided to it to its original state so it is
 * ready to search again.
 */
void astar_reset(astar* asp)
{
    /* Reset the graph. */
    graph_reset((*asp)->gp);

    /* Empty the priority queue. */
    while (!(min_heap_is_empty((*asp)->openset)))
    {
        min_heap_pop_min(&(*asp)->openset);
    }

    /* Empty the path. */
    while (array_size((*asp)->path) > 0)
    {
        array_pop_front(&(*asp)->path);
    }
}

/**
 * This is the A* search algorithm. It searches for the shortest path from
 * the start node to the end node.
 */
void astar_search(astar* asp, node* start, node* end)
{
    array neighbours;   /* The neighbours of the current node. */
    node* current;      /* The current node on the path. */
    node* neighbour;    /* A neighbour of the current node on the path. */
    edge* e;            /* The edge separating the current node and neighbour. */
    bool path_found;    /* Whether a path has been found. */
    uint64_t next_g;    /* Cost from start to neighbour through the current node. */
    uint64_t i;         /* The index of the edge we're assessing. */
    
    /* Reset the astar to its original state. */
    astar_reset(asp);

    /* A path has not yet been found. */
    path_found = false;

    /* Add the start node to the priority queue. */
    min_heap_add(&(*asp)->openset, start);

    /* Set the start node's distance from the start node. */
    node_set_g(start, 0);

    /* Search the graph. */
    while (!(min_heap_is_empty((*asp)->openset)) && !path_found)
    {
        /* Get the currently known node with the lowest estimated cost/distance
         * from the start node to the end node. */
        current = (node*) min_heap_pop_min(&(*asp)->openset);

        /* Check if the path has reached the goal node. */
        if (current == end)
        {
            /* The shortest path was found, so reconstruct it. */
            astar_reconstruct_path(asp, start, current);
            path_found = true;
        }
        else
        {
            /* Get the neighbours of the current node. */
            neighbours = node_get_neighbours(*current);

            /* Assess the edges of the neighbouring nodes that are relevant
             * to the current node. */
            for (i = 0; i < array_size(neighbours); i++)
            {
                /* Get the edge of the current neighbour that is relevant to
                 * the current node. */
                neighbour = (node*) array_get_data(neighbours, i);
                e = node_get_neighbouring_edge(current, *neighbour);

                /* Measure the cost of the path from its start to the
                 * neighbour. */
                next_g = node_get_g(*current) + edge_get_w(*e);

                /* Check if the path to the neighbour is better than any
                 * previous path. */
                if (edge_get_w(*e) != 0 && next_g < node_get_g(*neighbour))
                {
                    /* This path to the neighbour is better than any previous
                     * one so record it. */
                    node_set_came_from(neighbour, current);
                    node_set_g(neighbour, next_g);

                    /* Set the estimation for total cost of the path if it
                     * goes through the neighbour. */
                    node_set_f(neighbour, next_g + astar_h(*neighbour, *end, 
                                            graph_get_style(*(*asp)->gp)));

                    /* Check if the neighbour is not already in the priority
                     * queue. */
                    if (!min_heap_val_exists((*asp)->openset, neighbour))
                    {
                        /* Add the neighbour to the priority queue. */
                        min_heap_add(&(*asp)->openset, neighbour);
                    }
                }
            }
        }
    }
}

/**
 * This is astar's heuristic function. This function returns an estimate of
 * the distance between two graph-nodes.
 */
uint32_t astar_h(node node_a, node node_b, enum graph_style gstyle)
{
    uint64_t cost;  /* The estimated distance between the two nodes. */
    uint8_t dx;     /* The absolute difference of the x axes. */
    uint8_t dy;     /* The absolute difference of the y axes. */
    uint8_t dz;     /* The absolute difference of the z axes. */
    uint8_t min;    /* The minimum absolute difference out of all the axes. */
	
    /* Calculate the absolute differences of each axis of the two nodes. */
    dx = abs(node_get_x(node_a) - node_get_x(node_b));
    dy = abs(node_get_y(node_a) - node_get_y(node_b));
    dz = abs(node_get_z(node_a) - node_get_z(node_b));

    /* Calculate the estimated cost with consideration towards the graph type. */
    if (gstyle == MANHATTAN)
    {
        cost = (uint64_t) (dx + dy + dz); 
    } 
    else if (gstyle == DIAGONAL)
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
 * to the goal node that was found by the search function.
 */
void astar_reconstruct_path(astar* asp, node* start, node* current)
{
    /* Empty any nodes that might be in the path array. 
     * This may now be redundant as a reset function now exists that is
     * called at the beginning of the search function. */
    while (array_size((*asp)->path) > 0)
    {
        array_pop_front(&(*asp)->path);
    }

    /* Reconst the shortest path. */
    array_push_front(&(*asp)->path, current);
    while(current != start)
    {
        current = node_get_came_from(*current);
        array_push_front(&(*asp)->path, current);
    }
}
