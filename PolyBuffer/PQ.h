#ifndef __PQ__
#define __PQ__
#include "geometry.h"

#define EDGE 0
#define SPLIT 1


struct node_s
{
	double priority, type;
	point_t *intersection;
	int Aid, Bid;
	struct node_s *next;
};

struct pq_s
{
	struct node_s *root;
};

typedef struct node_s node_t;
typedef struct pq_s pq_t;

/*
Initializes a node where the priority corresponds to the distance of 
an intersection point to a perticular edge. 
If type == EDGE
{
    Aid and Bid correspond to the origin points of the bisectors creating the intersection point
}
if type == SPLIT
{
    Aid corresponds to the reflex vertex causing the split
	Bid corresponds to the starting point of the edge which splits
}
*/
node_t *node_init(double prty, point_t *point, int Aid, int Bid, int type);
/*
Initializes a priority queue
*/
pq_t *pq_init();
/*
Inserts a newnode into a priority queue
When function is first called, first corresponds to the root of the priority queue
SYNTAX: 
pq->root = pq_insert(pq->root, node);
*/
node_t* pq_insert(node_t *first, node_t *newnode);
/*
Removes and returns the node with the SMALLEST priority from the queue
*/
node_t *pq_pop(pq_t *pq);

//Printer function
void pq_print(node_t *root);

#endif