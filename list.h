#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure de type cellule :
typedef struct cell {
    int sommet_arrivee;
    float proba;
    struct cell* suivante;
} Cell;

// Structure de type liste :
typedef struct liste {
    Cell* head;
} Liste;

// structure de liste adjacente
typedef struct liste_adj{
    Liste* tab_liste;
    int nb_sommets;
} ListeAdj;

void add_list_cell(Liste* liste, Cell* cell);
Cell *createCell(int arrivee, float proba);
Liste createListe();
void addCell(liste *l, int arrivee, float proba);
void displayListe(Liste l);
ListeAdj createListeAdj(int taille);
void displayListeAdj(ListeAdj g);

#endif