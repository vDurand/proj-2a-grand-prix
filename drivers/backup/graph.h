/**
*@author BASS Yannick
*@file graph.h
*@date 07/05/16
*/
#ifndef _GRAPH_
#define _GRAPH_


#include "coord.h"


typedef struct n
{
	struct n* pred;
	coord coord;
	int heuristic;
	int cost;
	int poids;
}node;

typedef struct p
{
	coord* coords;
	int index;
	int currentIndex;
}path;
#include "list.h"
#include "map.h"

node* createNode(coord coord);
path aStar(map m,coord start,finish f);
int compareNodes(node *n1, node *n2);
path Astar(map c, coord p, finish a);
#endif
