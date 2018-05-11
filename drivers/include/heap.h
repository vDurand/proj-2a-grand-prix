#ifndef _HEAP_
#define _HEAP_

#include <stdio.h>
#include <stdlib.h>
#include "coord.h"

typedef struct d_t {
	coord coord;
	int cost;
	struct d_t *previous;
} data_t;

typedef struct n_t {
    int priority;
    data_t *data;
    struct n_t *next;
} node_t;
 
typedef struct {
    node_t *head;
    int size;
} heap_t;
/**
 * @brief Fonction qui crée une donnée à empiler
 * @param  les coords de la case
 * @return la donnée à empiler
 */
data_t *createData(coord coord);
/**
 * @brief Fonction qui crée un tas
 * @return le tas
 */
heap_t *createHeap();
/**
 * @brief Fonction qui empile une donnée
 * @param  le tas
 * @param  la priorité de la donnée
 * @param  la donnée
 */
void push(heap_t *h, int priority, data_t *data);
/**
 * @brief Fonction qui récupère une donnée
 * @param  le tas
 * @return la donnée
 */
data_t *pop(heap_t *h);
/**
 * @brief Fonction qui test si le tas est vide
 * @param  le tas
 * @return VRAI si vide
 */
boolean empty(heap_t *h);
/**
 * @brief Fonction qui test si une donnée est dans la pile
 * @param  le tas
 * @param  la donnée
 * @param  la donnée si elle est dans le tas
 */
data_t *peek(heap_t *h, data_t *d);

#endif
