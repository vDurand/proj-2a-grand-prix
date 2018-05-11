/**
 *@author DURAND Valentin/BASS Yannick
 *@file main.c
 *@date 15/05/16
 */
#include "path.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


int heuristic(coord pos, coord goal)
{
  int D = 1;
  int D2 = sqrt(2);
  int dx = abs(pos.x - goal.x);
  int dy = abs(pos.y - goal.y);
  return D * (dx + dy) + (D2 - 2 * D) * MIN(dx, dy);
}

coord getbestFinish(coord start, finish f){
  int bisNorm=10000, bis=0,currentNorm,i;
  for(i=0; i <f.nb ;i++)
    {
      currentNorm = heuristic(start,f.finishLine[i]);
      if(currentNorm<bisNorm)
	{
	  bisNorm=currentNorm;
	  bis=i;
	}
    }
  return f.finishLine[bis];
}

int isInPath(path p, int x, int y)
{
  int i;
  for(i = 0; i < p.index; i++){
    if(p.coords[i].x == x && p.coords[i].y == y)
      return 1;
  }
  return 0;
}

path reconstructPath(data_t *d)
{
  int i;
  path path;
  path.index=0;

  FILE* ret;
  ret = fopen("drivers/astar.log","w+");

  data_t *temp = d;
  while(d){
    path.index++;
    d = d->previous;
  }

  d = temp;
  path.coords = (coord*)calloc(path.index, sizeof(coord));

  for(i = path.index-1; i >= 0; i--){
    path.coords[i].x = d->coord.x;
    path.coords[i].y = d->coord.y;
    fprintf(ret, "%d %d\n",path.coords[i].x,path.coords[i].y);
    d = d->previous;
  }
  for (i = 1; i < path.index-1; ++i){
    if(path.coords[i-1].x == path.coords[i+1].x && path.coords[i].x != path.coords[i+1].x)
      path.coords[i].x = path.coords[i-1].x;
    if(path.coords[i-1].y == path.coords[i+1].y && path.coords[i].y != path.coords[i+1].y)
      path.coords[i].y = path.coords[i-1].y;
  }

  return path;
}

path getPath(map c, coord p, finish f, boolean log)
{
  int i, j;
  data_t *current;
  data_t *next_new;
  data_t *next_old;
  int cost, priority;

  heap_t *open = createHeap();
  heap_t *closed = createHeap();
  data_t *start = createData(p);

  coord bestFinish = getbestFinish(p,f);

  push(open, 0, start);
  fprintf(stderr, "Start a*\n");

  while(!empty(open)){
    current = pop(open);

    if(isFinish(current->coord, f)){
      fprintf(stderr, "FINISH LINE MET\n");
      break;
    }

    for(i=-1;i<=1;i++){
      for(j=-1;j<=1;j++){
	if(i != 0 || j != 0){
	  //fprintf(stderr, "test %d %d\n", current->coord.x+j, current->coord.y+i);
	  cost = current->cost + 1;
	  next_new = createData(createCoord(current->coord.x+j, current->coord.y+i));
	  next_old = peek(closed, next_new);
	  if(!isObstacle(next_new->coord, c)){
	    if(isSand(next_new->coord, c)){
	      cost += 4;
	      if(abs(i) == abs(j))
		cost += 99;
	    }
	    if(!next_old){
	      //fprintf(stderr, "no old %d %d\n",next_new->coord.x, next_new->coord.y);
	      next_new->cost = cost;
	      priority = cost + heuristic(next_new->coord, bestFinish);
	      push(open, priority, next_new);
	      next_new->previous = current;
	      push(closed, 0, next_new);
	    }
	    else if(cost < next_old->cost){
	      //fprintf(stderr, "is old %d %d\n",next_old->coord.x, next_old->coord.y);
	      next_old->cost = cost;
	      priority = cost + heuristic(next_old->coord, bestFinish);
	      push(open, priority, next_old);
	      next_old->previous = current;
	    }
	  }
	}
      }
    }
  }

  path path=reconstructPath(current);

  if(log){
    FILE* ret;
    ret = fopen("drivers/astar.map","w+");
    for (i = 0; i < c.height; ++i)
      {
	for (j = 0; j < c.width; ++j)
	  {
	    if(isInPath(path, j, i))
	      fprintf(ret, "+");
	    else
	      fprintf(ret, "%c", c.map[i][j]);
	  }
	fprintf(ret, "\n");
      }
    fclose(ret);
  }

  return path;
}   
