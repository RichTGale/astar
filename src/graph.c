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
 * Version: 1.0.0
 * File version: 1.0.1
 * Author: Richard Gale
 */

#include "graph.h"

/**
 * This is the internal data-structure of the graph type.
 */
struct graph_data {
    
    /* This is the three-dimensional array of the nodes that make up the
     * graph. */
    node*** nodes;
    
    /* These are the sizes of each of the axes/dimensions of the graph. */ 
    uint8_t xsize;
    uint8_t ysize;
    uint8_t zsize;

    /* This stores the way in which a graph-node will be considered a neighbour
     * of another graph-node. */
    enum graph_style gstyle;
};

/**
 * This function returns true if the coordinates provided to it are within the
 * bounds of the graph's axes which is also provided to the function.
 */
bool graph_valid_coord(graph g, int16_t x, int16_t y, int16_t z);

/**
 * 
 * Initialises the graph's nodes. 
 */
void graph_init_nodes(graph* gp);

/**
 * This function initialises the graph provided to it.
 */
void graph_init(graph* gp,
                uint8_t xsize, uint8_t ysize, uint8_t zsize, 
                enum graph_style gstyle)
{
    /* Allocate memory for the graph. */
    *gp = (graph) malloc(sizeof(struct graph_data));

    /* Initialise the graph's internal data. */
    (*gp)->xsize = xsize;
    (*gp)->ysize = ysize;
    (*gp)->zsize = zsize;
    (*gp)->gstyle = gstyle;
    
    /* Initialise the graph's nodes. */
    graph_init_nodes(gp);
}

/**
 * This function destroys the graph provided to it.
 */
void graph_free(graph* gp)
{
    uint8_t x;      /* The current x coordinate. */
    uint8_t y;      /* The current y coordinate. */
    uint8_t z;      /* The current z coordinate. */
    uint8_t xsize;  /* The size of the graph's x axis. */
    uint8_t ysize;  /* The size of the graph's y axis. */
    uint8_t zsize;  /* The size of the graph's z axis. */

    /* Get the size of the graph's axes/dimensions. */
    xsize = (*gp)->xsize;
    ysize = (*gp)->ysize;
    zsize = (*gp)->zsize;

    /* De-allocate memory from the graph's nodes. */
    for (x = 0; x < xsize; x++)
    {
        for (y = 0; y < ysize; y++)
        {
            for (z = 0; z < zsize; z++)
            {
                /* Destroy the node. */
                node_free(&(*gp)->nodes[x][y][z]);
            }
            /* De-allocate memory from the z axis. */
            free((*gp)->nodes[x][y]);
        }
        /* De-allocate memory from the y axis. */
        free((*gp)->nodes[x]);
    }
    /* De-allocate memory from the x axis. */
    free((*gp)->nodes);

    /* De-allocate memory from the graph. */
    free(*gp);
}

/**
 * This function returns the node in the graph provided to it located at the
 * coordinates also provided to the function.
 */
node* graph_get_node(graph g, uint8_t x, uint8_t y, uint8_t z)
{
    node* n;    /* The node at the coordinates. */

    /* Check if the coordinates are within the bounds of the graph. */
    if (graph_valid_coord(g, (int16_t) x, (int16_t) y, (int16_t) z))
    {
        /* The provided coordinates is within the bounds of the graph so
         * get the node at those coordinates. */
        n = &(g->nodes[x][y][z]);
    }
    else
    {
        /* The provided coordinates are not within the bounds of the graph
         * so print an error message and exit the program. */
        fprintf(stdout,
                "\nERROR: In function graph_get_node(): "
                "Invalid node coordinates: { %d, %d, %d }!\n", x, y, z);
        exit(EXIT_FAILURE);
    }

    /* Returning the node at the coordinates. */
    return n;
}

/* This function returns the way in which a graph-node will be considered a
 * neighbour of another graph-node.
 */
enum graph_style graph_get_style(graph g)
{
    /* Return the way in which graph-nodes are considered neighbours of each
     * other. */
    return g->gstyle;
}

/**
 * This function returns the size of the x axis of the graph provided it.
 */
uint8_t graph_get_x_size(graph g)
{
    /* Return the size of the x axis. */
    return g->xsize;
}

/**
 * This function returns the size of the y axis of the graph provided it.
 */
uint8_t graph_get_y_size(graph g)
{
    /* Return the size of the y axis. */
    return g->ysize;
}

/**
 * This function returns the size of the z axis of the graph provided it.
 */
uint8_t graph_get_z_size(graph g)
{
    /* Return the size of the z axis. */
    return g->zsize;
}

/**
 * This function adds an edge to the "to" node provided to it, making it be
 * considered a neighbour of the "from" node provided to the function.
 * Note: This creates a one-way relationship between the nodes. The "from" node
 * will not be considered a neighbour of the "to" node.
 */
void  graph_add_edge(node* fromp, node* top, uint8_t weight)
{
    /* Add an edge. */
    node_add_edge(fromp, top, weight);
}

/**
 * This function removes an edge from the "to" node provided to it, making it
 * no longer be considered a neighbour of the "from" node provided to the
 * function.
 * Note: This destroys the relationship between the nodes one-way only. The
 * "from" node may still be considered a neighbour of the "to" node.
 */
void graph_remove_edge(node* fromp, node* top) 
{
    /* Remove an edge. */
    node_remove_edge(fromp, top);
}

/**
 * This function resets the graph to its original state so it is ready to
 * be searched again.
 */
void graph_reset(graph* gp)
{
    uint8_t x;      /* The current x coordinate. */
    uint8_t y;      /* The current y coordinate. */
    uint8_t z;      /* The current z coordinate. */
    uint8_t xsize;  /* The size of the graph's x axis. */
    uint8_t ysize;  /* The size of the graph's y axis. */
    uint8_t zsize;  /* The size of the graph's z axis. */

    /* Get the size of the graph's axes/dimensions. */
    xsize = (*gp)->xsize;
    ysize = (*gp)->ysize;
    zsize = (*gp)->zsize;
   
    /* Reset the graph's nodes. */
    for (x = 0; x < xsize; x++)
    {
        for (y = 0; y < ysize; y++)
        {
            for (z = 0; z < zsize; z++)
            {
	            node_reset(&(*gp)->nodes[x][y][z]);
            }
        }
    }
}

/**
 * This function returns true if the coordinates provided to it are within the
 * bounds of the graph's axes which is also provided to the function.
 */
bool graph_valid_coord(graph g, int16_t x, int16_t y, int16_t z)
{
    /* Return whether the coordinates are within the bounds of the graph. */ 
    return     x >= 0 && x < (int16_t) g->xsize
            && y >= 0 && y < (int16_t) g->ysize
            && z >= 0 && z < (int16_t) g->zsize;
}

/**
 * This functions returns true if the relationship between the provided
 * offsets is consistent with that of manhattan neighbours.
 */
bool manhattan_relationship(int8_t xoff, int8_t yoff, int8_t zoff)
{
    /* Return whether the relationship between the offsets is manhattan. */
    return     (xoff ==  0 && yoff ==  0 && zoff ==  1)
            || (xoff ==  0 && yoff ==  1 && zoff ==  0)
            || (xoff ==  1 && yoff ==  0 && zoff ==  0)
            || (xoff ==  0 && yoff ==  0 && zoff == -1)
            || (xoff ==  0 && yoff == -1 && zoff ==  0)
            || (xoff == -1 && yoff ==  0 && zoff ==  0);
}

/**
 * This function returns true if the relationship between the provided offsets
 * is consistent with that of diagonal neighbours.
 */
bool diagonal_relationship(int8_t xoff, int8_t yoff, int8_t zoff)
{
    /* Return whether the relationship ibetween the offsets is diagonal. */
    return  (manhattan_relationship(xoff, yoff, zoff))
            || (
            /* Top layer. */
               (xoff == -1 && yoff == -1 && zoff != -1)
	        || (xoff ==  0 && yoff == -1 && zoff != -1)
	        || (xoff ==  1 && yoff == -1 && zoff != -1)
	        || (xoff == -1 && yoff == -1 && zoff !=  0)
	        || (xoff ==  1 && yoff == -1 && zoff !=  0)
	        || (xoff == -1 && yoff == -1 && zoff !=  1)
	        || (xoff ==  0 && yoff == -1 && zoff !=  1)
	        || (xoff ==  1 && yoff == -1 && zoff !=  1)

            /* Middle layer. */
            || (xoff ==  -1 && yoff ==  0 && zoff != -1)
            || (xoff ==   1 && yoff ==  0 && zoff != -1)
            || (xoff ==  -1 && yoff ==  0 && zoff !=  1)
            || (xoff ==   1 && yoff ==  0 && zoff !=  1)

	        /* Bottom layer. */
	        || (xoff == -1 && yoff ==  1 && zoff != -1)
	        || (xoff ==  0 && yoff ==  1 && zoff != -1)
	        || (xoff ==  1 && yoff ==  1 && zoff != -1)
	        || (xoff == -1 && yoff ==  1 && zoff !=  0)
	        || (xoff ==  1 && yoff ==  1 && zoff !=  0)
	        || (xoff == -1 && yoff ==  1 && zoff !=  1)
	        || (xoff ==  0 && yoff ==  1 && zoff !=  1)
	        || (xoff ==  1 && yoff ==  1 && zoff !=  1)
            );
}

/**
 * This function populates the array of neighbours of the node provided to 
 * this function.
 */
void graph_collect_neighbours(graph* gp, node* np)
{
    node* neighbour;            /* A neighbouring node. */
    enum graph_style gstyle;    /* The graph's style. */
    int16_t x;                  /* The neighbour's x coordinate. */
    int16_t y;                  /* The neighbour's y coordinate. */
    int16_t z;                  /* The neighbour's z coordinate. */
    int8_t xoff;                /* The x axis coordinate offset. */
    int8_t yoff;                /* The y axis coordinate offset. */
    int8_t zoff;                /* The z axis coordinate offset. */
    bool manh_rel;              /* Whether the offsets have a manhattan relationship. */
    bool diag_rel;              /* Whether the offsets have a diagonal relationship. */
    
    /* Get the graph style. */
    gstyle = (*gp)->gstyle;

    /* Collect the neighbours of the provided node. */
    for (xoff = -1; xoff <= 1; xoff++)
    {
        for (yoff = -1; yoff <= 1; yoff++)
        {
            for (zoff = -1; zoff <= 1; zoff++)
            {
                /* Calculate the coordinates of the neighbour. */
                x = (int16_t) node_get_x(*np) + (int16_t) xoff;
                y = (int16_t) node_get_y(*np) + (int16_t) yoff;
                z = (int16_t) node_get_z(*np) + (int16_t) zoff;

                /* Check if the offsets have a manhattan relationship. */
                manh_rel = manhattan_relationship(xoff, yoff, zoff);
                
                /* Check if the offsets have a diagonal relationship.
                 * Note: Diagonal relationships also have a manhattan
                 * relationship. */
                diag_rel = diagonal_relationship(xoff, yoff, zoff);

                /* Collect the neighbours. */
                if ( ( (gstyle == MANHATTAN && manh_rel) 
                    || (gstyle == DIAGONAL  && diag_rel) ) 
                    && graph_valid_coord(*gp, x, y, z)  )
                {
                    /* These coordinates are valid so get the neighbour and add
                     * it to node's array of neighbours. */
                    neighbour = graph_get_node(
                            *gp, (uint8_t) x, (uint8_t) y, (uint8_t) z);
                    node_add_neighbour(np, neighbour);
                }
            }
        }
    }
}

/**
 * This function initialises the edges of the node provided to this function's
 * neighbours.
 */
void graph_init_edges(graph* gp, node* np)
{
    array neighbours;       /* The node's neighbours. */
    node* neighbour;        /* A node neighbouring the provided node. */
    uint8_t num_neighbours; /* The number of neighbours the node has. */
    uint8_t* weights;       /* The weights of the neighbouring node's edges. */
    
    /* Get the node's neighbours. */
    neighbours = node_get_neighbours(*np);

    /* Get how many neighbours the node has. */
    num_neighbours = array_size(neighbours);

    /* Create the weights of the neighbouring nodes' edges. */
    weights = (uint8_t*) malloc(sizeof(uint8_t) * num_neighbours);
    for (int i = 0; i < num_neighbours; i++)
    {
        neighbour = (node*) array_get_data(neighbours, i);
        if (node_get_type(*neighbour) == PASSABLE)
        {
            weights[i] = 1;
        }
        else
        {
            weights[i] = 0;
        }
    }

    /* Initialise the edges of the neighbours. */
    node_init_edges(np, &(weights[0]));

    /* De-allocate memory from the array of weights. */
    free(&(weights[0]));
}

/**
 * This function initialises the nodes of the graph provided to it. 
 */
void graph_init_nodes(graph* gp)
{
    uint8_t x;      /* The current x coordinate. */
    uint8_t y;      /* The current y coordinate. */
    uint8_t z;      /* The current z coordinate. */
    uint8_t xsize;  /* The size of the graph's x axis. */
    uint8_t ysize;  /* The size of the graph's y axis. */
    uint8_t zsize;  /* The size of the graph's z axis. */

    /* Get the size of the graph's axes. */
    xsize = (*gp)->xsize;
    ysize = (*gp)->ysize;
    zsize = (*gp)->zsize;

    /* Allocate memory to the x axis. */
    (*gp)->nodes = (node***) malloc(sizeof(node**) * xsize);
    for (x = 0; x < xsize; x++)
    {
        /* Allocate memory to the y axis. */
        (*gp)->nodes[x] = (node**) malloc(sizeof(node*) * ysize);
        for (y = 0; y < ysize; y++)
        {
            /* Allocate memory to the z axis. */
            (*gp)->nodes[x][y] = (node*) malloc(sizeof(node) * zsize);
            for (z = 0; z < zsize; z++)
            {
                /* Initialise the node. */
                node_init(&(*gp)->nodes[x][y][z], x, y, z, PASSABLE);
            }
        }
    }

    /* Create the array of neighbouring nodes and their edges. */
    for (x = 0; x < xsize; x++)
    {
        for (y = 0; y < ysize; y++)
        {
            for (z = 0; z < zsize; z++)
            {
                /* Populate the node's array of neighbours. */
                graph_collect_neighbours(gp, &(*gp)->nodes[x][y][z]);
                
                /* Create the edges of this node's array of neighbours. */
                graph_init_edges(gp, &(*gp)->nodes[x][y][z]);
            }
        }
    }
}

/**
 * This function prints information about the graph.
 */
void graph_print(graph g)
{
    uint8_t x;      /* The current x coordinate. */
    uint8_t y;      /* The current y coordinate. */
    uint8_t z;      /* The current z coordinate. */
    uint8_t xsize;  /* The size of the graph's x axis. */
    uint8_t ysize;  /* The size of the graph's y axis. */
    uint8_t zsize;  /* The size of the graph's z axis. */

    /* Get the size of the graph's axes/dimensions. */
    xsize = g->xsize;
    ysize = g->ysize;
    zsize = g->zsize;

    printf("Graph:\n{\n");
    for (x = 0; x < xsize; x++)
    {
        printf("\t{\n");
        for (y = 0; y < ysize; y++)
        {
            printf("\t\t{\n");
            for (z = 0; z < zsize; z++)
            {
                // Print the current node.
                printf("\t\t\t");
                node_print(g->nodes[x][y][z]);
                if (z < zsize - 1)
                {
                    printf(",");
                }
                printf("\n");
            }
            printf("\t\t}");
            if (y < ysize - 1)
            {
                printf(",");
            }
            printf("\n");
        }
        printf("\t}");
        if (x < xsize - 1)
        {
            printf(",");
        }
        printf("\n");
    }
    printf("}\n");
}
