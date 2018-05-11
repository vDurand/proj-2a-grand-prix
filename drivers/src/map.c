/**
 *@author BASS Yannick
 *@file map.c
 *@date 06/05/16
 */
#include "map.h"

map loadMap()
{ 
  map m;
  int i, ret;
  ret = fscanf(stdin,"%d %d %d",&(m.width),&(m.height),&(m.fuel));
  m.map=(char**)malloc((m.height)*sizeof(char*));
  for(i=0;i<m.height;i++)
    { 
      m.map[i]=(char*)malloc((m.width)*sizeof(char));
      ret = fscanf(stdin,"%s",m.map[i]);
      fflush(stdin);
    }
  fflush(stdin);
  return m;
}

finish findFinish(map m)
{
  int i,j,nb=0;
  coord temp[1024];
  finish f;

  for(i=0;i<m.height;i++){
    for(j=0;j<m.width;j++){
      if(m.map[i][j]==FINISH){
	temp[nb] = createCoord(j,i);
	nb++;
      }
    }
  }
	
  f.nb=nb;
  f.finishLine = (coord*)calloc(f.nb, sizeof(coord));
  for (i = 0; i < nb; ++i)
    {
      f.finishLine[i] = temp[i];
    }
	
  return f;
}

boolean isObstacle(coord c, map m)
{
  //test permettant de s'assurer que l'on reste dans la map
  if(c.y>0 && c.x>0 && c.x<m.width && c.y<m.height){
    return m.map[c.y][c.x]==WALL;
  }
  return TRUE;
}

boolean isFinish(coord c,finish f)
{
  int i;
  for(i=0;i<f.nb;i++)
    {
      if(equals(c,f.finishLine[i]))
	return TRUE;
    }
  return FALSE;

}

boolean isSand(coord c, map m)
{
  return m.map[c.y][c.x]==SAND;
}

boolean isRoad(coord c, map m)
{
  if(c.y>0 && c.x>0 && c.x<m.width && c.y<m.height){
    return m.map[c.y][c.x]==ROAD;
  }
  return FALSE;
}


