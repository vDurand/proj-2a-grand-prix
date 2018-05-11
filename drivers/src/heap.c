/**
*@author DURAND Valentin
*@file main.c
*@date 15/05/16
*/
#include "heap.h"

data_t *createData(coord coord)
{
    data_t *d = (data_t*)malloc(sizeof(data_t));
    d->coord=coord;
    d->cost=0;
    d->previous = NULL;
    return d;
}

heap_t *createHeap()
{
    heap_t *h = calloc(1, sizeof (heap_t));
    return h;
}

void push(heap_t *h, int priority, data_t *data)
{
    node_t *n = (node_t*)malloc(sizeof(node_t));
    node_t *cur;

    n->priority = priority;
    n->data = data;
    n->next = NULL;

    if(h->head == NULL){
        h->head = n;
    }
    else{   
        cur = h->head;
        while(cur->next && cur->priority <= n->priority){
            cur = cur->next;
        }
        n->next = cur->next;
        cur->next = n;
    }

    h->size++;
}
 
data_t *pop(heap_t *h)
{
    node_t *n = h->head;
    data_t *d = n->data;
    h->head = n->next;

    free(n);
    h->size--;
    
    return d;
}

boolean empty(heap_t *h)
{
    if(!h->size)
        return TRUE;
    return FALSE;
}

data_t *peek(heap_t *h, data_t *d)
{
    node_t *n = h->head;

    while(n){
        if(equals(n->data->coord, d->coord))
            return n->data;
        n = n->next;
    }
    return NULL;
}
