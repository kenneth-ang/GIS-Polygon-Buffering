#ifndef __SLL__
#define __SLL__
#include "geometry.h"

struct vert_s
{
	int id;
	struct vert_s *next;
	struct vert_s *prev;
	point_t *data;
};

struct ll_s
{
	int numvert;
	double remdist;
	struct vert_s *current;
	struct ll_s *nextlst;
};

struct sll_s
{
	struct ll_s *currentlst;
};

typedef struct vert_s vert_t;
typedef struct ll_s ll_t;
typedef struct sll_s sll_t;

/*Initialize vertex point
Note: The id of each vertex should be unique*/
vert_t *vert_init(int id, point_t *data);
/*Initialize a linked list. 
remdist id the remainding distance a polygon need to be buffered*/
ll_t *ll_init(double remdist);
/*
Initializes a set of linked lists
*/
sll_t *sll_init(); 

/*
Moves current pointer of the linked-list rightwards
*/
void incrementLLcurrent(ll_t *llst); 
/*
Looks through the vertices of the linked list and points the current pointer to the 
vertex with the desired id. 
Note: returns 1 on success and 0 on failure
*/
int changeLLcurrent(ll_t *llst, int id); 
/*
Inserts a new vertex in the current position. 
The previous current gets pushed behind the new current vertex
*/
void insertLLcurrent(ll_t *llst, vert_t *newvert); 
/*
removes the current vertex from the linked list and returns it. 
The next vertex in the linked list becomes the new current vertex. 
*/
vert_t *removeLLcurrent(ll_t *llst); 
/*
Counts the number of vertices contained within a linked list
*/
int countLLvert(ll_t *lav);

/*Splits polygon into 2 separate shapes, v1 replaces the reflex and end of enge
v2 replaces vertex and start of edge
IMPORTANT: lav->current should be the reflex vertex when calling this function*/
ll_t *split_reflex(ll_t *lav, vert_t *v1, vert_t *v2, int edgeSid);

/*
Inserts a new linked list at the start of the set of linked lists
*/
void insertSLL(sll_t *sllst, ll_t *newllst); 
/*
Removes and returns the first linked list from the set of linked lists
*/
ll_t *removeSLL(sll_t *sllst); 

//Helper functions to print data
void printSLL(sll_t *slav);
void printLL(ll_t * lst);

#endif