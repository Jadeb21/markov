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
} cell;

// Structure de type liste :
typedef struct liste {
    struct cell* head;
    struct cell* tail;
} liste;

// structure de liste adjacente
typedef struct liste_adj{
    liste* tab_liste;
    int nb_sommets;
} listeAdj;

cell *createCell(int arrivee, float probab);
liste *createListe();
void addCell(liste *l, int arrivee, float probab);
void displayListe(liste l);
listeAdj createListeAdj(int taille);
void displayListeAdj(listeAdj g);
listeAdj readGraph(const char *filename);
int verifierGrapheMarkov(listeAdj g);
void genererFichierMermaid(listeAdj g, const char* nomFichier);
void genererFichierMermaid(listeAdj g, const char* nomFichier);
int verifierGrapheMarkov(listeAdj g);

#endif
