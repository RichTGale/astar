/**
 * astar.c
 * 
 * Data-structure and procedure definitions for an
 * A* (A Star) search algorithm.
 * 
 * Author: RIchard Gale
 * Version: 15th August, 2022-
 */

#include "astar.h"

/** 
 * The data contained within the astar data-structure.
 */
struct astar_data {
	graph* g;			// The graph.
	min_heap openset;	// The openset
	// The nodes that are the shortest path 
	// between the starting node and the goal node.
	array path;
};

/**
 * Intialises the astar.
 */
void astar_init(astar* as_ref, graph* g)
{
	*as_ref = (astar) malloc(sizeof(struct astar_data));
	(*as_ref)->g = g;
	min_heap_init(&(*as_ref)->openset, NODE);
	array_init(&(*as_ref)->path);
}

/**
 * Frees the memory allocated to the astar.
 */ 
void astar_free(astar* as_ref)
{
	min_heap_free(&(*as_ref)->openset);
	array_free(&(*as_ref)->path);
    free(*as_ref);
}

/**
 * Returns a reference to an array containing the nodes
 * that make up the shortest path found by the search procedure. 
 */
array astar_get_path(astar as)
{
	return as->path;
}

/**
 * Heuristic function.
 * Uses the Manhattan heuristic where the sum of 
 * the absolute differences of the provided nodes' 
 * three coordinate-axes are returned, providing an 
 * estimate of the distance between the current node
 * and the goal or end node.
 */
int astar_h(node node_a, node node_b, enum graph_styles style)
{
	int cost;	// The estimated distance between the two nodes
	int dx;		// The absolute difference of the x axes.
	int dy;		// The absolute difference of the y axes.
	int dz;		// The absolute difference of the z axes.
	int min; 	// The minimum absolute difference of all axes.
	
	// Calculating the absolute differences of each axis of the two nodes.
	dx = abs(node_get_x(node_a) - node_get_x(node_b));
	dy = abs(node_get_y(node_a) - node_get_y(node_b));
	dz = abs(node_get_z(node_a) - node_get_z(node_b));

	// Calculating the estimated cost
	if (style == MANHATTAN)
	{
		cost = dx + dy + dz; 
	} else if (style == DIAGONAL)
	{
		min = dx < dy ? dx : dy;
		min = min < dz ? min : dz;
		cost = (dx + dy + dz) + (1 - 3) * min;
	} 

	// Returning the estimated cost.
	return cost;
}

/**
 * Reconstructs the shortest path that the search procedure
 * found through the graph that goes from the starting node 
 * to the goal node.
 */
void astar_reconstruct_path(astar* as, node* start, node* current)
{
	array_push_front(&(*as)->path, current);

	while(current != start)
	{
		current = node_get_came_from(*current);
		array_push_front(&(*as)->path, current);
	}
}

/**
 * A* search algorithm. Searches for the shortest
 * path from the start node to the end node.
 */
void astar_search(astar* as_ref, node* start, node* end)
{
	node* current;	// The current node on the path
	array neighbours;	// The neighbours of the current node
	node* neighbour;	// The current neighbour of the current node
	bool path_found = false;	// Whether a path has been found
	int tentative_g;	// Distance from start to the neighbour through the current node

	// Initialising the array used to store the neighbours of the current node
	array_init(&neighbours);

	// Adding the start node to the minimum heap
	min_heap_add(&(*as_ref)->openset, start);

	// Setting the start node's distance from the start node
	node_set_g(start, 0);

	// Searching the graph
	while (!(min_heap_is_empty((*as_ref)->openset)) && !path_found)
	{
		// Getting the currently known node with the lowest
		// estimated cost or distance from the start node to the end node
		current = (node*) min_heap_pop_min(&(*as_ref)->openset);
		
		if (current == end)
		{
			// Reconstructing the shortest path
			astar_reconstruct_path(as_ref, start, current);
			path_found = true;
		} else
		{
			// Create our array of neighbours of the current node
			graph_neighbours((*as_ref)->g, current, &neighbours);

			while(array_size(neighbours) > 0)
			{
				neighbour = array_pop_front(&neighbours);
				tentative_g = node_get_g(*current) + node_get_w(*neighbour);
				if (tentative_g < node_get_g(*neighbour))
				{
					// This path to the neighbour is better than any previous one
					// so we are recording it.
					node_set_came_from(neighbour, current);
					node_set_g(neighbour, tentative_g);

					// Setting the estimation for total cost of the path if it 
					// goes through neighbour
					node_set_f(neighbour, 
								tentative_g + astar_h(*neighbour, 
								*end, 
								graph_get_style(*(*as_ref)->g)));

					if (!min_heap_val_exists((*as_ref)->openset, neighbour))
					{
						// Adding the neighbour to the heap
						min_heap_add(&(*as_ref)->openset, neighbour);
					}
				}
			}
		}
	}
	array_free(&neighbours);
}





