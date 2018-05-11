#ifndef _CAR_
#define _CAR_ 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "coord.h"
#include "path.h"

typedef struct
{
	coord currentPosition;
	coord previousPosition;
	coord speed;
	int boosts;
	int fuel;
} car;

/**
 * @brief Fonction créant une voiture
 * @param  la position de la voiture 
 * @param  le carburant alloué
 * @return c une voiture
 */
car createCar(coord position, int fuel);
/**
 * @brief Fonction mettant à jour une voiture
 * @param  la voiture 
 * @param  la nouvelle position
 */
void updateCar(car* car, coord position);
/**
 * @brief Fonction testant si un boost est possible
 * @param la piste 
 * @param la voiture
 * @return VRAI si boost possible
 */
boolean boostable(map map, car car,int topredict);
/**
 * @brief Fonction testant si le coup est un boost
 * @param l'acceleration
 * @param le nombre de coup à prevoir
 * @return VRAI si boost
 */
boolean isBoost(coord c);
/**
 * @brief Fonction testant si le coup est valide
 * @param la voiture
 * @param l'acceleration
 * @param la piste
 * @return VRAI si valide
 */
boolean isPossibleAcceleration(car c, coord v, map m);
/**
 * @brief Fonction testant si le coup est valide
 * @param la piste
 * @param les voitures
 * @param le chemin a suivre
 * @return un vecteur acceleration
 *
 */
coord getNextMove(map map, car* cars, path path);

#endif
