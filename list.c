#include "list.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Liste createListe(){
  Liste list;
  list.head = NULL;
  return list;
}

//Ajouter cellule a une liste
void addCell(Liste *l, int arrivee, float probab) {
    Cell* new_cell = createCell(arrivee, probab);
    new_cell->suivante = l->head;
    l->head = new_cell;
}

//Afficher une liste
void displayListe(liste l){
    Cell* current = l.head;
    if (current == NULL) {
        printf("Empty list\n");
        return;
    }
    while(current != NULL){
        printf("-> %d (%.2f)", current->arrivee, current->proba);
        current = current->suivante;
    }
}
//Afficher la liste adjacente
void displayListeAdj(ListeAdj g){
  for (int i = 0; i < g.nb_sommets; i++) {
    printf("Sommet %d: ", i + 1);
    displayListe(g.tab_liste[i]);
  }





//Créer une cellule a une liste
cell *createCell(int arrivee, float probab){
	cell *nouv;
	nouv = (t_cell*)malloc(sizeof(cell));
	nouv->sommet_arrivee = arrivee;
	nouv->proba = probab;
	nouv->suivante = NULL;
	return nouv;}

