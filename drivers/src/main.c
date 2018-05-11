/**
 *@author BASS Yannick
 *@file main.c
 *@date 06/05/16
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "heap.h"
#include "car.h"

int main(int argc, char const *argv[]){
  int i, ret, round = 0;
  boolean log;
  car cars[3];
  map map;
  finish f;
  path p;
  coord next;
  coord* coords = (coord*)calloc(3,sizeof(coord));

  FILE* fp;
  coord velocity;
  fp = fopen("drivers/race.log","w+");
  fprintf(fp, "Race starting\n\n");

  map = loadMap();
  f=findFinish(map);

  while(!feof(stdin)){
    fprintf(fp, "Round %d :\n", ++round);

    if(round == 1){
      for (i = 0; i < 3; ++i){
	ret = fscanf(stdin, "%d %d", &(coords[i].x), &(coords[i].y));
	cars[i] = createCar(coords[i], map.fuel);
	fprintf(fp, "* Car %d start at %d %d\n", i+1, cars[i].currentPosition.x, cars[i].currentPosition.y);
	log = TRUE;
	//p = getPath(map, cars[0].currentPosition, f, log);
      }
    }
    else{
      for (i = 0; i < 3; ++i){
	ret = fscanf(stdin, "%d %d", &(coords[i].x), &(coords[i].y));
	updateCar(&cars[i], coords[i]);
	fprintf(fp, "Car %d move to %d %d w/ speed %d %d\n", i+1, cars[i].currentPosition.x, cars[i].currentPosition.y, cars[i].speed.x, cars[i].speed.y);
	log = TRUE;
      }
    }

    map.map[cars[1].currentPosition.y][cars[1].currentPosition.x] = WALL;
    map.map[cars[2].currentPosition.y][cars[2].currentPosition.x] = WALL;
    p = getPath(map, cars[0].currentPosition, f, log);
    map.map[cars[1].currentPosition.y][cars[1].currentPosition.x] = ROAD;
    map.map[cars[2].currentPosition.y][cars[2].currentPosition.x] = ROAD;

    next = getNextMove(map, cars, p);
    if(next.x > 2){
      fprintf(stderr, "invalid\n");
      next = createCoord(0, 0);
    }
    if(isBoost(next))
      cars[0].boosts--;

    fprintf(fp, "> Playing car moving by %d %d\n\n", next.x, next.y);
    fprintf(stdout, "%d %d\n", next.x, next.y);
    fprintf(stderr, "%d %d -> %d %d\n", next.x, next.y, addition(cars[0].currentPosition, addition(next,cars[0].speed)).x, addition(cars[0].currentPosition, addition(next,cars[0].speed)).y);
    fflush(stdout);

    if(isFinish(addition(cars[0].currentPosition, addition(next,cars[0].speed)),f)){
      fprintf(stderr, "over & out\n");
      break;
    }
  }

  fprintf(fp, "Race over\n");
  fprintf(stderr, "Fini\n");
  fclose(fp);

  return 0;
}
