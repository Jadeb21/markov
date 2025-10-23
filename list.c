#include "list.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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




