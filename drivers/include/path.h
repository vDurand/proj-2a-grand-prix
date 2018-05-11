#ifndef _PATH_
#define _PATH_ 
#include "map.h"
#include "heap.h"

typedef struct p
{
	coord* coords;
	int index;
} path;

/**
 * @brief Fonction test si une case fait partie du chemin
 * @param  le chemin 
 * @param  les coords de la case
 * @return c une voiture
 */
int isInPath(path p, int x, int y);
/**
 * @brief  Fonction calculant le chemin à suivre
 * @param  les coordonnées de départs 
 * @param  la ligne d'arrivée
 * @param  un boolean si on veut un log de la course
 * @return c une voiture
 */
path getPath(map c, coord p, finish f, boolean log);


#endif
