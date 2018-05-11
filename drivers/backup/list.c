/**
*@author BASS Yannick
*@file list.c
*@date 06/05/16
*/
#include "list.h"

list* createList()
{
	list* l=(list*)malloc(sizeof(list));
	l->head=NULL;
	return l;
}

int contains(list *l,node *n){
	int found=0;
	cell *c= l->head;
	while(!found && c)
		{
		if(equals(c->node->coord, n->coord))
		{
			found=1;
		}
		c=c->next;
	}
	return found;
}

void addElement(list *l, node* n)
{
	cell *c = (cell*)malloc(sizeof(cell));
	c->node=n;
	c->next=l->head;
	l->head=c;
}

void addSortedElement(list *l,node *n)
{
cell *c = (cell*)malloc(sizeof(cell));
	c->node=n;
	c->next=NULL;
	if(l->head==NULL)
		{
		l->head=c;
		}
	else
		{	
		cell* temp=l->head;
		while(temp->next!=NULL && compareNodes(temp->next->node, n))
			{
			temp=temp->next;
			}
		c->next=temp->next;
		temp->next=c;
	}

}

node* removeElement(list *l)
{
	cell *c = l->head;
	node *n = c->node;
	l->head=c->next;
	free(c);
	return n;
}

void freeCell(cell* c)
{
	if(c)
		{
		freeCell(c->next);
		free(c);
		}
}

void freeList(list *l)
{
	freeCell(l->head);
	free(l);
}
