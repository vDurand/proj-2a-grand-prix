/**
*@author BASS Yannick
*@file coord.h
*@date 06/05/16
*/
#ifndef _COORD_
#define _COORD_ 

#include <math.h>

typedef enum { FALSE, TRUE } boolean;

typedef struct
{
	int x;
	int y;
}coord;

/**
 * @brief Fonction permettant de creer une coord à partir de deux entiers
 * @param  entier
 * @param  entier
 * @return  coordonnées
 */
coord createCoord(int x,int y);

/**
 * @brief Fonction effectuant la soustraction de deux coordonnées
 * @param  coordonnées
 * @param  coordonnées
 * @return coordonnées
 */
coord substractCoords(coord v1, coord v2);

/**
 * @brief Fonction effectuant l'addition de deux coordonnées
 * @param v1 coordonnées 
 * @param v2 coordonnées
 * @return c coordonnées
 */
coord addition(coord v1, coord v2);

/**
 * @brief Fonction permettant de determiner si deux coordonnes sont identiques
 * @param v1 coordonnées 
 * @param v2 coordonnées
 * @return VRAI si les coordonnées sont egaux 
 */
boolean equals(coord v1, coord v2);

/**
 * @brief Fonction permettant de calculer la norme d'un vecteur
 * @param vecteur coordonnées
 * @return la norme
 */
float norme(coord vecteur);

#endif
