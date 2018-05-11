/**
 *@author DURAND Valentin/BASS Yannick
 *@file main.c
 *@date 15/05/16
 */
#include "car.h"
#define SANDNORM 1.0
#define NORM 5.0
car createCar(coord position, int fuel)
{
  car car;
  car.currentPosition = createCoord(position.x, position.y);
  car.previousPosition = createCoord(position.x, position.y);
  car.speed = createCoord(0, 0);
  car.boosts = 5;
  car.fuel = fuel;

  return car;
}
boolean boostable(map map, car car, int topredict)
{
  int i;
  coord cur = createCoord(car.currentPosition.x, car.currentPosition.y);

  for (i = 0; i < topredict; ++i){
    cur = addition(cur, car.speed);
    if(!isRoad(cur, map ))
      return FALSE;
  }
  return FALSE;
}
void updateCar(car* car, coord position)
{
  changeCoord(&(car->previousPosition), car->currentPosition.x, car->currentPosition.y);
  changeCoord(&(car->currentPosition), position.x, position.y);
  car->speed = substractCoords(car->currentPosition, car->previousPosition);
  car->fuel -= ((car->speed.x)^2 + (car->speed.y)^2 + (int)(sqrt((car->speed.x)^2 + (car->speed.y)^2) * 3/2));
}

boolean isBoost(coord c)
{
  if(c.x == 2 || c.x == -2 || c.y == 2 || c.y == -2)
    return TRUE;
  return FALSE;
}

boolean isPossibleAcceleration(car c, coord v, map m){
  coord newspeed,newPosition;	
  newspeed= addition(c.speed,v);
  newPosition= addition(c.currentPosition, newspeed);
  int isInSand = m.map[c.currentPosition.y][c.currentPosition.x]==SAND;
  if(isInSand){
    if(norm(newspeed)>SANDNORM){
      return FALSE;
    }
  }
  else{
    if(norm(newspeed)>NORM){
      fprintf(stderr, "norm2big\n");
      return FALSE;
    }
  }
  if(newPosition.y<0 || newPosition.x<0 || newPosition.x>=m.width || newPosition.y>=m.height){
    return FALSE;
  }
  if(m.map[newPosition.y][newPosition.x] == WALL || m.map[newPosition.y][newPosition.x] == PILOTE){
    return FALSE;
  }

  return TRUE;
}

coord getNextMove(map map, car* cars, path path)
{
  int i, j, k, l, limit, max = -1;
  boolean stillOnTheRoad;
  coord cur, newSpeed, temp,prev, best = createCoord(99, 99);

  if(cars[0].boosts > 0 && boostable(map, cars[0], 10))
    limit = 2;
  else
    limit = 1;

  if(isSand(cars[0].currentPosition, map)){
    fprintf(stderr, "in sand\n");

    for(k = 0; k < path.index; k++){
      if(equals(path.coords[k], addition(cars[0].currentPosition, createCoord(1,0)))) best = createCoord(1,0);
      else if(equals(path.coords[k], addition(cars[0].currentPosition, createCoord(0,-1)))) best = createCoord(0,-1);
      else if(equals(path.coords[k], addition(cars[0].currentPosition, createCoord(-1,0)))) best = createCoord(-1,0);
      else if(equals(path.coords[k], addition(cars[0].currentPosition, createCoord(0,-1)))) best = createCoord(0,-1);
    }
    if(best.x>2){
      if(cars[0].speed.x > 0 && cars[0].speed.x > cars[0].speed.y && !isObstacle(addition(cars[0].currentPosition, createCoord(1,0)), map)){
	best = createCoord(1,0);
	fprintf(stderr, "best deduced1 %d %d\n", best.x, best.y);
      }
      else if(cars[0].speed.y < 0 && cars[0].speed.y < cars[0].speed.x && !isObstacle(addition(cars[0].currentPosition, createCoord(0,-1)), map)){
	best = createCoord(0,-1);
	fprintf(stderr, "best deduced2 %d %d\n", best.x, best.y);
      } 
      else if(cars[0].speed.x < 0 && cars[0].speed.x < cars[0].speed.y && !isObstacle(addition(cars[0].currentPosition, createCoord(-1,0)), map)){
	best = createCoord(-1,0);
	fprintf(stderr, "best deduced3 %d %d\n", best.x, best.y);
      } 
      else if(cars[0].speed.y > 0 && cars[0].speed.y > cars[0].speed.x && !isObstacle(addition(cars[0].currentPosition, createCoord(0,-1)), map)){
	best = createCoord(0,1);
	fprintf(stderr, "best deduced4 %d %d\n", best.x, best.y);
      } 
      else{
	best=prev;
	fprintf(stderr, "best deduced5 %d %d\n", best.x, best.y);
      } 
    }
    best = substractCoords(best,cars[0].speed);
    prev = best;
    return best;
  }

  fprintf(stderr, "Testing moves\n");
  if(cars[0].boosts > 0 && boostable(map, cars[0],5))
    limit = 2;
  else
    limit = 1;
  for(i = -limit; i <= limit; i++){
    for(j = -limit; j <= limit; j++){
      newSpeed = createCoord(j, i);
      cur = addition(cars[0].currentPosition, addition(newSpeed, cars[0].speed));
      if(!equals(cars[0].currentPosition, cur)){
	fprintf(stderr, "test %d %d\n", cur.x, cur.y);
	if(isPossibleAcceleration(cars[0],newSpeed,map) || (boostable(map, cars[0], 10)) && norm(addition(cars[0].speed,newSpeed))<25.0){
	  fprintf(stderr, "in\n");
	  for(k = 0; k < path.index; k++){
	    if(equals(path.coords[k], cur)){
	      if(k > max){
		max = k;
		best = newSpeed;
		stillOnTheRoad = TRUE;
		fprintf(stderr, "is best %d %d\n", best.x, best.y);
	      }
	    }
	  }
	}
      }
    }
  }

  if(norm(addition(cars[0].speed,best))>5.0 && !boostable(map, cars[0], 3)){
    if(best.x < 0) best.x += 1;
    if(best.x >= 0) best.x -= 1;
    if(best.y < 0) best.y += 1;
    if(best.y >= 0) best.y -= 1;
  }

  if(best.x>2){
    if(cars[0].speed.x > 0 && cars[0].speed.x > cars[0].speed.y && !isObstacle(addition(cars[0].currentPosition, createCoord(1,0)), map)) best = createCoord(1,0);
    else if(cars[0].speed.y < 0 && cars[0].speed.y < cars[0].speed.x && !isObstacle(addition(cars[0].currentPosition, createCoord(0,-1)), map)) best = createCoord(0,-1);
    else if(cars[0].speed.x < 0 && cars[0].speed.x < cars[0].speed.y && !isObstacle(addition(cars[0].currentPosition, createCoord(-1,0)), map)) best = createCoord(-1,0);
    else if(cars[0].speed.y > 0 && cars[0].speed.y > cars[0].speed.x && !isObstacle(addition(cars[0].currentPosition, createCoord(0,-1)), map)) best = createCoord(0,1);
  }
  prev = best;
  return best;
}
