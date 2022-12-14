/**
 * astar.c
 * 
 * Data-structure and procedure definitions for an
 * A* (A Star) search algorithm.
 * 
 * Author: RIchard Gale
 * Version: 30th August, 2022
 */

#include "astar.h"

/** 
 * The data contained within the astar data-structure.
 */
struct astar_data {
	graph* g_ref;		// The graph.
	min_heap openset;	// The openset.
	array path;			// The nodes that make up the shortest path.
};

/**
 * Intialises the astar.
 */
void astar_init(astar* as_ref, graph* g_ref)
{
	*as_ref = (astar) malloc(sizeof(struct astar_data));
	(*as_ref)->g_ref = g_ref;
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
 * Returns an estimate of the distance between two graph-nodes.
 */
uint32_t astar_h(node node_a, node node_b, enum graph_styles style)
{
	uint64_t cost;	// The estimated distance between the two nodes
	uint8_t dx;	// The absolute difference of the x axes.
	uint8_t dy;	// The absolute difference of the y axes.
	uint8_t dz;	// The absolute difference of the z axes.
	uint8_t min; 	// The minimum absolute difference out of all the axes.
	
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
	node* neighbour;	// A neighbour of the current node on the path.
	edge* e;	// The edge separating the current node and neighbour.
	bool path_found = false;	// Whether a path has been found
	uint64_t next_g;	// Cost from start to neighbour through the current node
	uint64_t i; // The index of the edge we're assessing from the openset

	// Initialising the array used to store the neighbours of the current node
	// array_init(&neighbours);

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
			// Assessing each edge of the current node
			for (i = 0; i < array_size(node_get_edges(*current)); i++)
			{
				// Assigning to some variables to make the code easier
				// to read.
				e = array_get_data(node_get_edges(*current), i);
				neighbour = graph_get_node(*(*as_ref)->g_ref, edge_get_x(*e), 
											edge_get_y(*e), edge_get_z(*e));

				// Measuring the cost of this path to the neighbour.
				next_g = node_get_g(*current) + edge_get_w(*e);
				if (next_g < node_get_g(*neighbour))
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





