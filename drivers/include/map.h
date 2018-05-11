/**
*@author BASS Yannick
*@file map.h
*@date 06/05/16
*/

#ifndef _MAP_
#define _MAP_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "coord.h"

#define FINISH '=' 
#define ROAD '#' 
#define SAND '~'
#define WALL '.'
#define PILOTE 'P'
typedef struct
{
	char** map;
	int width, height, fuel;
} map;

typedef struct
{
	coord* finishLine;
	int nb;
} finish;

/**
 * @brief Fonction effectuant le chargement de la carte à partir des données serveur
 * @return une structure map
 */
map loadMap();
/**
 * @brief Fonction permettant de trouver la ligne d'arrivee
 * @param la carte
 * @return une structure finish contenant les cases de la ligne d'arrivee
 */
finish findFinish(map m);

/**
 * @brief Fonction permettant de determiner si une case est composée de sable
 * @param la carte,les coordonnées de la case
 * @return VRAI si la case est faite de sable
 */
boolean isSand(coord c, map m);
/**
 * @brief Fonction permettant de determiner si une case est un mur
 * @param la carte,les coordonnées de la case
 * @return VRAI si la case est un mur
 */
boolean isObstacle(coord c, map m);
/**
 * @brief Fonction permettant de determiner si une case est une arrivée
 * @param la carte,les coordonnées de la case
 * @return VRAI si la case est une arrivée
 */
boolean isFinish(coord c,finish f);
/**
 * @brief Fonction permettant de determiner si une case est un morceau de piste
 * @param la carte,les coordonnées de la case
 * @return VRAI si la case est un bout de piste
 */
boolean isRoad(coord c, map m);

#endif

