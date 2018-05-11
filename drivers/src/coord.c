/**
 *@author BASS Yannick
 *@file coord.c
 *@date 06/05/16
 */
#include "coord.h"

coord createCoord(int x,int y){
  coord c;
  c.x=x;
  c.y=y;
  return c;
}

coord substractCoords(coord v1, coord v2){
  coord c;
  c.x=v1.x-v2.x;
  c.y=v1.y-v2.y;
  return c;
}

coord addition(coord v1, coord v2){
  coord c;
  c.x=v1.x+v2.x;
  c.y=v1.y+v2.y;
  return c;
}

boolean equals(coord v1, coord v2){
  return (v1.x==v2.x && v1.y==v2.y);
}

float norm(coord vecteur){
  return sqrt( 1.0*(vecteur.x*vecteur.x + vecteur.y*vecteur.y));
}

void changeCoord(coord *v, int x, int y){
  v->x=x;
  v->y=y;
}
