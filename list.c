#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// crée une cellule
cell *createCell(int arrivee, float probab) {
    cell *nouv = malloc(sizeof(cell));
    nouv->sommet_arrivee = arrivee;
    nouv->proba = probab;
    nouv->suivante = NULL;
    return nouv;
}

// crée une liste vide
liste *createListe() {
    liste *list = malloc(sizeof(liste));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

// ajoute une cellule au début
void addCell(liste *l, int arrivee, float probab) {
    cell* new_cell = createCell(arrivee, probab);
    new_cell->suivante = l->head;
    l->head = new_cell;

    if (l->tail == NULL)
        l->tail = new_cell;
}

// affiche une liste
void displayListe(liste l) {
    cell* current = l.head;
    if (current == NULL) {
        printf("Empty list\n");
        return;
    }
    while (current != NULL) {
        printf("-> %d (%.2f) ", current->sommet_arrivee, current->proba);
        current = current->suivante;
    }
    printf("\n");
}

// crée une liste d'adjacence vide
listeAdj createListeAdj(int taille) {
    listeAdj nouv;
    nouv.nb_sommets = taille;
    nouv.tab_liste = malloc(taille * sizeof(liste));

    for (int i = 0; i < taille; i++) {
        nouv.tab_liste[i].head = NULL;
        nouv.tab_liste[i].tail = NULL;
    }
    return nouv;
}

// affiche une liste d'adjacence
void displayListeAdj(listeAdj g) {
    for (int i = 0; i < g.nb_sommets; i++) {
        printf("Sommet %d: ", i + 1);
        displayListe(g.tab_liste[i]);
    }
}

// lit un graphe depuis un fichier texte
listeAdj readGraph(const char *filename) {
    FILE *file = fopen(filename, "rt");
    int nbvert, depart, arrivee;
    float proba;

    if (file == NULL) {
        perror("Could not open file for reading");
        exit(EXIT_FAILURE);
    }

    if (fscanf(file, "%d", &nbvert) != 1) {
        perror("Could not read number of vertices");
        exit(EXIT_FAILURE);
    }

    listeAdj g = createListeAdj(nbvert);

    while (fscanf(file, "%d %d %f", &depart, &arrivee, &proba) == 3) {
        addCell(&g.tab_liste[depart - 1], arrivee, proba);
    }

    fclose(file);
    return g;
}
