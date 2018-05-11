#include "graph.h"

node* createNode(coord coord)
{
	node *n = (node*)malloc(sizeof(node));
	n->pred=NULL;
	n->coord=coord;
	n->cost=0;
	n->heuristic=0;
	n->poids=0;
	return n;
}

int compareNodes(node *n1, node *n2)
{
	return n1->heuristic < n2->heuristic;
}

coord getbestFinish(coord start, finish f){
	int bisNorm=10000, bis=0,currentNorm,i;
	for(i=0; i <f.nb ;i++)
	{
		currentNorm = norm(substractCoords(f.finishLine[i],start));
		if(currentNorm<bisNorm)
			{
			bisNorm=currentNorm;
			bis=i;
			}
	}
	return f.finishLine[bis];
}

path reconstructPath(node* n)
{
	int i;
	path path;
	path.index=0;
	path.currentIndex=0;
	node* temp;
	for(temp=n;temp;temp=temp->pred)
		{
		path.index++;
		}

	path.coords=(coord*)calloc(path.index, sizeof(coord));
	for(i=path.index-1 ; i>=0 ; i--)
		{
		path.coords[i]=n->coord;
		n=n->pred;
		}
	return path;
}

path aStar(map c, coord p, finish f){
	int end=0;
	int i,j;
	list* open=createList();
	list* closed=createList();
	node* startNode=createNode(p);
	node* current;
	node* neighbor;
	addElement(open,startNode);
	coord bestFinish=getbestFinish(p,f);

	while(!end)
		{
		current= removeElement(open);
		addElement(closed,current);
		end=isFinish(current->coord,f);
		for(i=-1;i<=1;i++)
			{
			for(j=-1;j<=1;j++)
				{
				if(i!=0 || j!=0)
					{
					neighbor=createNode(createCoord(current->coord.x+i, current->coord.y+j));
					if(! (isObstacle(neighbor->coord,c) || contains(closed,neighbor)))
						{
						if(contains(open,neighbor))
							{
							if(current->cost+1 < neighbor->cost)
								{
								neighbor->cost= current->cost+1;
								if(isSand(neighbor->coord,c))
									{
									neighbor->cost += 4;
									}
								neighbor->pred=current;
								}
							}
						else
							{
							neighbor->pred=current;
							neighbor->cost=current->cost+1;
							if(isSand(neighbor->coord,c))
								{
								neighbor->cost += 4;
								}
							neighbor->heuristic=neighbor->cost=current->cost + neighbor->cost+norm(substractCoords(bestFinish,current->coord));
							addSortedElement(open,neighbor);
							}
						}
					}
				}
		}
	}
	freeList(closed);
	freeList(open);
	path path=reconstructPath(current);
	return path;
}

