/**
 * graph.c
 * 
 * This file contains the internal data-structure and procedure definitions
 * for the graph type.
 *
 * The graph type is an up to 3 dimentional weighted graph. It can be used
 * for graph-related search/path finding algorithms. This one was written
 * for use with an A* (Astar) search algorithm.
 *
 * Astar version: 1.0.0
 * File version: 1.0.1
 * Author: Richard Gale
 */

#include "graph.h"

/**
 * This is the internal data structure of the graph type.
 */
struct graph_data {
    node*** nodes;              /* The nodes that make up the graph. */
    uint8_t x_size;             /* The size of the x axis. */
    uint8_t y_size;             /* The size of the y axis. */
    uint8_t z_size;             /* The size of the z axis. */
    enum graph_styles g_style;  /* The relationship between neighbour nodes. */ 
};

/* Function prototype declarations. */
void graph_init_nodes(graph* g_ref);
void graph_init_edges(graph* g_ref);
bool graph_valid_coord(graph g, int16_t x , int16_t y , int16_t z);

/**
 * This function initialises the graph provided to it.
 */
void graph_init(graph* g_ref, uint8_t x_size, uint8_t y_size, 
                              uint8_t z_size, enum graph_styles g_style)
{
    /* Allocate memory to the graph. */
    *g_ref = (graph) malloc(sizeof(struct graph_data));

    /* Initialise the graph's properties. */
    (*g_ref)->x_size = x_size;
    (*g_ref)->y_size = y_size;
    (*g_ref)->z_size = z_size;
    (*g_ref)->g_style = g_style;
    graph_init_nodes(g_ref);
    graph_init_edges(g_ref);
}

/**
 * This function destroys the graph provided to it.
 */
void graph_free(graph* g_ref)
{
    uint8_t x; /* The current x coordinate. */
    uint8_t y; /* The current y coordinate. */
    uint8_t z; /* The current z coordinate. */

    /* Destroying the nodes. */
    for (x = 0; x < (*g_ref)->x_size; x++)
    {
        for (y = 0; y < (*g_ref)->y_size; y++)
        {
            for (z = 0; z < (*g_ref)->z_size; z++)
            {
                /* Destrying the current node. */
                node_free(&(*g_ref)->nodes[x][y][z]);
            }
            /* De-allocating memory from the z axis. */
            free((*g_ref)->nodes[x][y]);
        }
        /* De-allocating memory from the y axis. */
        free((*g_ref)->nodes[x]);
    }
    /* De-allocating memory from the x axis. */
    free((*g_ref)->nodes);

    /* De-allocating memory from the graph. */
    free(*g_ref);
}

/**
 * This function returns a reference to the graph-node at the provided
 * coordinates.
 */
node* graph_get_node(graph g, uint8_t x, uint8_t y, uint8_t z)
{
    node* n;    /* The reference to the node at the provided corrdinate. */

    /* Check if the coordinates are within the bounds of the graph. */
    if (graph_valid_coord(g, (int16_t) x, (int16_t) y, (int16_t) z))
    {
        /* The coordinate is within the bounds of the grap so get the
         * reference to the node at those coordinates. */
        n = &(g->nodes[x][y][z]);
    }
    else
    {
        /* The coordinates are not within the bounds of the graph so
         * print an error message and exit the program. */
        printf("\nERROR: In function graph_get_node(): Invalid node" 
                " coordinates: { %d, %d, %d }!\n", x, y, z);
        exit(EXIT_FAILURE);
    }

    /* Return the reference to the node at the coordinates. */
    return n;
}

/**
 * This function returns the graph's graph_style whic is the relationship
 * between the graph's nodes.
 */
enum graph_styles graph_get_style(graph g)
{
    /* Return the relationship between the graph's nodes. */
    return g->g_style;
}

/**
 * This function resets the graph to its original state so it can be searched
 * again. 
 */
void graph_reset(graph* g_ref)
{
    uint8_t x; /* Current x coordinate. */
    uint8_t y; /* Current y coordinate. */
    uint8_t z; /* Current z coordinate. */
   
    /* Reset the graph's nodes. */ 
    for (x = 0; x < (*g_ref)->x_size; x++)
    {
        for (y = 0; y < (*g_ref)->y_size; y++)
        {
            for (z = 0; z < (*g_ref)->z_size; z++)
            {
                node_reset(&(*g_ref)->nodes[x][y][z]);
            }
        }
    }
}

/**
 * This function adds an edge to a graph node, making it be considered the
 * neighbour of another.
 * NOTE: This creates a one-way connection.
 */
void  graph_add_edge(node* from_ref, node* to_ref, uint8_t weight)
{
    /* Add the edge. */
    node_add_edge(from_ref, to_ref, weight);
}

/**
 * This function removes an edge from a graph node, stopping it from being 
 * considered the neighbour of another.
 * NOTE: This creates a one-way removal.
 */
void graph_remove_edge(node* from_ref, node* to_ref) 
{
    /* Remove the edge. */
    node_remove_edge(from_ref, to_ref);
}

/**
 * This function returns true if the provided coordinates are within the
 * bounds of the graph.
 */
bool graph_valid_coord(graph g, int16_t x , int16_t y , int16_t z)
{
    /* Return whether the coordinates are within the bounds of the graph. */
    return  x >= 0 && x < (int16_t) g->x_size &&
            y >= 0 && y < (int16_t) g->y_size &&
            z >= 0 && z < (int16_t) g->z_size;
}


/**
 * This function returns true if the relationship between the provided offsets
 * is consistent with that of manhattan neighbours.
 */
bool manhattan_relationship(int8_t xoffset, int8_t yoffset, int8_t zoffset)
{
    /* Return whether the relationship is manhattan. */
    return  (xoffset ==  0 && yoffset ==  0 && zoffset ==  1) ||
            (xoffset ==  0 && yoffset ==  1 && zoffset ==  0) ||
            (xoffset ==  1 && yoffset ==  0 && zoffset ==  0) ||
            (xoffset ==  0 && yoffset ==  0 && zoffset == -1) ||
            (xoffset ==  0 && yoffset == -1 && zoffset ==  0) ||
            (xoffset == -1 && yoffset ==  0 && zoffset ==  0);
}

/**
 * This function returns true if the relationship between the provided offsets
 * is consistent with that of diagonal neighbours.
 */
bool diagonal_relationship(int8_t xoff, int8_t yoff, int8_t zoff)
{
    /* Return whether the relationship is diagonal. */
    return  (manhattan_relationship(xoff, yoff, zoff)) ||
            (
            /* Top layer. */
	        (xoff == -1 && yoff == -1 && zoff != -1) ||
	        (xoff ==  0 && yoff == -1 && zoff != -1) ||
	        (xoff ==  1 && yoff == -1 && zoff != -1) ||
	        (xoff == -1 && yoff == -1 && zoff !=  0) ||
	        (xoff ==  1 && yoff == -1 && zoff !=  0) ||
	        (xoff == -1 && yoff == -1 && zoff !=  1) ||
	        (xoff ==  0 && yoff == -1 && zoff !=  1) ||
	        (xoff ==  1 && yoff == -1 && zoff !=  1) ||
	
	        /* Middle layer. */
	        (xoff == -1 && yoff ==  0 && zoff != -1) ||
	        (xoff ==  1 && yoff ==  0 && zoff != -1) ||
	        (xoff == -1 && yoff ==  0 && zoff !=  1) ||
	        (xoff ==  1 && yoff ==  0 && zoff !=  1) ||
	
	        /* Bottom layer. */
	        (xoff == -1 && yoff ==  1 && zoff != -1) ||
	        (xoff ==  0 && yoff ==  1 && zoff != -1) ||
	        (xoff ==  1 && yoff ==  1 && zoff != -1) ||
	        (xoff == -1 && yoff ==  1 && zoff !=  0) ||
	        (xoff ==  1 && yoff ==  1 && zoff !=  0) ||
	        (xoff == -1 && yoff ==  1 && zoff !=  1) ||
	        (xoff ==  0 && yoff ==  1 && zoff !=  1) ||
	        (xoff ==  1 && yoff ==  1 && zoff !=  1)
	        );
}


/**
 * This function populates the array of neighbours provided to it with
 * the neighbouring nodes of the node also provided to the function.
 */
void collect_neighbours(graph* g_ref, node* n_ref, array* neighbours)
{
    node* neighbour;    /* The current node neighbouring the provided node. */
    int8_t xoffset;     /* The x axis coordinate offset. */
    int8_t yoffset;     /* The y axis coordinate offset. */
    int8_t zoffset;     /* The z axis coordinate offset. */
    int16_t xcoord;     /* The current neighbour's x coordinate. */
    int16_t ycoord;     /* The current neighbour's y coordinate. */
    int16_t zcoord;     /* The current neighbour's z coordinate. */


    /* Collect the neighbours of the node. */
    for (xoffset = -1; xoffset <= 1; xoffset++)
    {
        for (yoffset = -1; yoffset <= 1; yoffset++)
        {
            for (zoffset = -1; zoffset <= 1; zoffset++)
            {
                /* Calculate the coordinates of the neighbour. */
                xcoord = (int16_t) node_get_x(*n_ref) + (int16_t) xoffset;
                ycoord = (int16_t) node_get_y(*n_ref) + (int16_t) yoffset;
                zcoord = (int16_t) node_get_z(*n_ref) + (int16_t) zoffset;
                
                /* Collect manhattan neighbours. */
                if ((*g_ref)->g_style == MANHATTAN &&
                    manhattan_relationship(xoffset, yoffset, zoffset) &&
                    graph_valid_coord(*g_ref, xcoord, ycoord, zcoord))
                {
                    /* This is a valid neighbour so add it to the array of
                     * neighbours. */
                    neighbour = graph_get_node(*g_ref, (uint8_t) xcoord, 
                                    (uint8_t) ycoord, (uint8_t) zcoord);
                    array_push_back(neighbours, neighbour); 
                }
                
                /* Collect diagonal neighbours. */
                else if ((*g_ref)->g_style == DIAGONAL &&
                    diagonal_relationship(xoffset, yoffset, zoffset) &&
                    graph_valid_coord(*g_ref, xcoord, ycoord, zcoord))
                {
                    /* This is a valid neighbour so add it to the array of
                     * neighbours. */
                    neighbour = graph_get_node(*g_ref, (uint8_t) xcoord, 
                                    (uint8_t) ycoord, (uint8_t) zcoord);
                    array_push_back(neighbours, neighbour); 
                }
            }
        }
    }
}

/**
 * This function initialises the edges of the graph's nodes.
 */
void graph_init_edges(graph* g_ref)
{
    array neighbours;   /* The neighbours of the current node. */
    uint8_t x;          /* The current x coordinate. */
    uint8_t y;          /* The current y coordinate. */
    uint8_t z;          /* The current z coordinate. */

    /* Create the edges of the graph's nodes' neighbours. */
    for (x = 0; x < (*g_ref)->x_size; x++)
    {
        for (y = 0; y < (*g_ref)->y_size; y++)
        {
            for (z = 0; z < (*g_ref)->z_size; z++)
            {
                /* Initialise the array of neighbours. */
                array_init(&neighbours);

                /* Collect the neighbouring nodes. */
                collect_neighbours(g_ref, &(*g_ref)->nodes[x][y][z], 
                                          &neighbours);

                /* Initialise the edges of the neighbours of the current
                 * node. */
                node_init_edges(&(*g_ref)->nodes[x][y][z], neighbours);
                
                /* Destroy the array of neighbours. */
                array_free(&neighbours);
            }
        }
    }
}

/**
 * This function initialises the graph's nodes. 
 */
void graph_init_nodes(graph* g_ref)
{
    uint8_t x; /* Current x coordinate. */
    uint8_t y; /* Current y coordinate. */
    uint8_t z; /* Current z coordinate. */

    /* Allocate memory to the x axis. */
    (*g_ref)->nodes = (node***) malloc((*g_ref)->x_size * sizeof(node**));
    for (x = 0; x < (*g_ref)->x_size; x++)
    {
        /* Allocate memory to the y axis. */
        (*g_ref)->nodes[x] = (node**) malloc((*g_ref)->y_size * sizeof(node*));
        for (y = 0; y < (*g_ref)->y_size; y++)
        {
            /* Allocate memory to the z axis. */
            (*g_ref)->nodes[x][y] = 
                (node*) malloc((*g_ref)->z_size * sizeof(node));
            for (z = 0; z < (*g_ref)->z_size; z++)
            {
                /* Initialise the current node. */
                node_init(&(*g_ref)->nodes[x][y][z], x, y, z);
            }
        }
    }
}

/**
 * This function prints the graph.
 */
void graph_print(graph g)
{
    uint8_t x; /* Current x coordinate. */
    uint8_t y; /* Current y coordinate. */
    uint8_t z; /* Current z coordinate. */

    /* Print the graph. */
    printf("Graph:\n{\n");
    for (x = 0; x < g->x_size; x++)
    {
        printf("\t{\n");
        for (y = 0; y < g->y_size; y++)
        {
            printf("\t\t{\n");
            for (z = 0; z < g->z_size; z++)
            {
                // Printing the current node.
                printf("\t\t\t");
                node_print(g->nodes[x][y][z]);
                if (z < g->z_size - 1)
                {
                    printf(",");
                }
                printf("\n");
            }
            printf("\t\t}");
            if (y < g->y_size - 1)
            {
                printf(",");
            }
            printf("\n");
        }
        printf("\t}");
        if (x < g->x_size - 1)
        {
            printf(",");
        }
        printf("\n");
    }
    printf("}\n");
}
