#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

/*
 *   Ce pilote ne génère aucun fichier de log et produit des
 *   accélérations aléatoires. Il peut être pratique pour
 *   tester votre pilote contre un autre avec de possibles
 *   collisions...
 */

int main(int argn, char** argv){
  char c;
  int i;
  srand(time(0));
  //Lecture de la carte.
  int tx, ty;
  int carburant; // carburant dans le réservoir
  // Il y a maintenant lecture du carburant au départ
  fscanf(stdin,"%d %d %d", &tx, &ty,&carburant);
  while(fread(&c, sizeof(char), 1, stdin)==1 && c!='\n');
  for (i=0; i<ty; i++) { // Lecture de la carte ligne par ligne
    while(fread(&c, sizeof(char), 1, stdin)==1 && c!='\n') { }
  }
  char action[100];
  while(!feof(stdin)){
    //Lecture des positions.
    while(fread(&c, sizeof(char), 1, stdin)==1 && c!='\n') { }
    sprintf(action,"%d %d",rand()%3-1,rand()%3-1);
    fprintf(stdout, "%s\n", action);
    fflush(stdout); // Vidage du buffer nécessaire.
  }
  return EXIT_SUCCESS;
}
