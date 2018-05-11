/**
*@author BASS Yannick
*@file list.h
*@date 06/05/16
*/

#ifndef _LIST_
#define _LIST_

#include "graph.h"

typedef struct c
{
	node* node;
	struct c *next;
}cell;

typedef struct
{
	cell *head;
}list;

/**
 * @brief Fonction permettant de creer une liste
 * @return l une liste vide
 */
list* createList();

/**
 * @brief Fonction permettant de determiner si un noeud est contenu dans une liste
 * @param *l liste
 * @param *n noeud
 * @return 1 si il est dans la liste, 0 sinon
 */
int contains(list *l,node *n);

/**
 * @brief Fonction permettant d'ajouter un noeud a la liste
 * @param *l liste
 * @param *n noeud à ajouter
 */
void addElement(list *l, node* n);

void addSortedElement(list *l,node *n);
/**
 * @brief Fonction retirant la tête d'une liste et la retourne
 * @param *l liste
 * @return n le noeud retiré
 */
node* removeElement(list *l);
void freeList(list *l);

#endif
