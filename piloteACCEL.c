#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
 *   Ce pilote ne g�n�re aucun fichier de log et produit des
 *   acc�l�rations d�mesur�es qui garantissent une consommation
 *   tr�s rapide de tout le carburant. Il peut servir de pilote
 *   inutile qui termine sa course rapidement, � court de carburant.
 */

int main(int argn, char** argv){
  char c;
  int i;
  int tx, ty;
  int carburant; // carburant dans le r�servoir
  // Lecture du carburant au d�part
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
    fflush(stdout); // Vidage du buffer n�cessaire.
  }
  return EXIT_SUCCESS;
}
