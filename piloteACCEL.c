#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
 *   Ce pilote ne génère aucun fichier de log et produit des
 *   accélérations démesurées qui garantissent une consommation
 *   très rapide de tout le carburant. Il peut servir de pilote
 *   inutile qui termine sa course rapidement, à court de carburant.
 */

int main(int argn, char** argv){
  char c;
  int i;
  int tx, ty;
  int carburant; // carburant dans le réservoir
  // Lecture du carburant au départ
  fscanf(stdin,"%d %d %d", &tx, &ty,&carburant);
  while(fread(&c, sizeof(char), 1, stdin)==1 && c!='\n');
  for (i=0; i<ty; i++) { // Lecture de la carte ligne par ligne
    while(fread(&c, sizeof(char), 1, stdin)==1 && c!='\n') { }
  }
  char action[100];
  while(!feof(stdin)){
    //Lecture des positions.
    while(fread(&c, sizeof(char), 1, stdin)==1 && c!='\n') { }
    sprintf(action,"%d %d",2000,2000);
    fprintf(stdout, "%s\n", action);
    fflush(stdout); // Vidage du buffer nécessaire.
  }
  return EXIT_SUCCESS;
}
