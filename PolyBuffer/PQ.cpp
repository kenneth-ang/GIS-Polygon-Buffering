#include "stdafx.h"
#include "stdlib.h"
#include"PQ.h"

node_t *node_init(double prty, point_t *point, int Aid, int Bid, int type)
{
	node_t *newnode;
	newnode = (node_t*)malloc(sizeof(*newnode));
	newnode->priority = prty;
	newnode->next = NULL;
	newnode->intersection = point;
	newnode->Aid = Aid;
	newnode->Bid = Bid;
	newnode->type = type; 
	return newnode;
}

pq_t * pq_init()
{
	pq_t *newpq;
	newpq = (pq_t*)malloc(sizeof(*newpq));
	newpq->root = NULL;
	return newpq;
}

node_t * pq_insert(node_t * first, node_t * newnode)
{
	if (first == NULL)
	{
		return newnode;
	}
	else if (newnode->priority <= first->priority)
	{
		newnode->next = first;
		return newnode;
	}
	else
	{
		first->next = pq_insert(first->next, newnode);
		return first;
	}
}

node_t * pq_pop(pq_t * pq)
{
	if (pq->root == NULL)
	{
		return NULL;
	}
	else
	{
		node_t *popnode = pq->root;
		pq->root = popnode->next;
		popnode->next = NULL;
		return popnode;
	}

}

void pq_print(node_t * root)
{
	if (root != NULL)
	{
		printf("Priority: %f\n", root->priority);
		pq_print(root->next);
	}
}
