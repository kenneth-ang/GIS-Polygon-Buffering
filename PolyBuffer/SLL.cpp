#include "stdio.h"
#include "stdafx.h"
#include "stdlib.h"
#include"SLL.h"

vert_t *vert_init(int id, point_t *data)
{
	vert_t *newvert;
	newvert = (vert_t*)malloc(sizeof(*newvert));
	newvert->id = id;
	newvert->data = data;
	newvert->next = NULL;
	newvert->prev = NULL;
	return newvert;
}

ll_t *ll_init(double remdist)
{
	ll_t *newlst;
	newlst = (ll_t*)malloc(sizeof(*newlst));
	newlst->current = NULL;
	newlst->nextlst = NULL;
	newlst->remdist = remdist; 
	newlst->numvert = 0;
	return newlst;
}

sll_t *sll_init()
{
	sll_t *newset;
	newset = (sll_t*)malloc(sizeof(*newset));
	newset->currentlst = NULL;
	return newset;
}

void incrementLLcurrent(ll_t *llst)
{
	llst->current = llst->current->next; 
}

int changeLLcurrent(ll_t *llst, int id)
{
	int i;
	for (i = 0; i<llst->numvert; i++)
	{
		if (llst->current->id == id) return 1;
		else llst->current = llst->current->next;
	}
	return 0;
}

void insertLLcurrent(ll_t *llst, vert_t * newvert)
{
	if (llst->current == NULL)
	{
		newvert->next = newvert;
		newvert->prev = newvert;
		llst->current = newvert;
	}
	else
	{
		llst->current->next->prev = newvert;
		newvert->prev = llst->current;
		newvert->next = llst->current->next;
		llst->current->next = newvert;
		llst->current = newvert;
	}
	llst->numvert++;
}

vert_t *removeLLcurrent(ll_t *llst)
{
	vert_t *removed = llst->current;
	removed->prev->next = removed->next;
	removed->next->prev = removed->prev;
	llst->current = removed->next;
	llst->numvert--;
	return removed;
}

int countLLvert(ll_t *lav)
{
	int count = 0;
	if (lav->current == NULL)return count;
	else count++;
	vert_t *currvert = lav->current;
	int startid = currvert->id;
	while (currvert->next->id != startid)
	{
		count++;
		currvert = currvert->next;
	}
	return count;
}

ll_t *split_reflex(ll_t *lav, vert_t *v1, vert_t *v2, int edgeSid)
{
	ll_t *nxtlav = ll_init(lav->remdist); 

	vert_t *reflexvert = lav->current; 
	changeLLcurrent(lav, edgeSid); 
	vert_t *startedge = lav->current; 

	v1->next = startedge->next;
	startedge->next->prev = v1;
	v1->prev = reflexvert->prev;
	reflexvert->prev->next = v1;

	v2->prev = startedge;
	startedge->next = v2;
	v2->next = reflexvert->next;
	reflexvert->next->prev = v2;

	nxtlav->current = v2;
	nxtlav->numvert = countLLvert(nxtlav); 

	lav->current = v1; 
	lav->numvert = countLLvert(lav); 
	lav->nextlst = nxtlav;

	return lav; 

}


void insertSLL(sll_t *sllst, ll_t * newllst)
{
	ll_t *tmp = newllst; 
	ll_t *tmpcurrent = sllst->currentlst; 
	if (newllst->nextlst!= NULL)
	{
		newllst->nextlst->nextlst = tmpcurrent;
	}
	else
	{
		newllst->nextlst = tmpcurrent;
	}
	sllst->currentlst = newllst;
}

ll_t *removeSLL(sll_t *sllst)
{
	if (sllst->currentlst == NULL)
	{
		return NULL; 
	}
	ll_t *remllst = sllst->currentlst; 
	sllst->currentlst = sllst->currentlst->nextlst; 
	remllst->nextlst = NULL; 
	return remllst; 
}

void printLL(ll_t *lst)
{
	//printf("---Start Link List---\n");
	printf("Linked List containing %d vertices:\n", lst->numvert);
	int i;
	vert_t *v = lst->current;
	for (i = 0; i < lst->numvert; i++)
	{
		printf("Vid: %d, ", v->id);
		if (v->data != NULL)
		{
			printf("Coords: (%f ,%10f), ", v->data->xcoord, v->data->ycoord);
		}
		else printf("No data!!");
		printf("\n");
		v = v->next;
	}
	printf("End Link List\n");
}

void printSLL(sll_t *slav)
{
	ll_t *curr = slav->currentlst;
	printf("START\n");
	while (curr != NULL)
	{
		printLL(curr);
		curr = curr->nextlst;
	}
	printf("END\n");
}

