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
        // REMETTRE l'ordre ORIGINAL
        addCell(&g.tab_liste[depart - 1], arrivee, proba);
    }

    fclose(file);
    return g;
}

// Fonction pour vérifier si le graphe est un graphe de Markov
int verifierGrapheMarkov(listeAdj g) {
    int estMarkov = 1;
    for (int i = 0; i < g.nb_sommets; i++) {
        float somme = 0.0;
        cell *current = g.tab_liste[i].head;

        // Calculer la somme des probabilités sortantes pour le sommet i
        while (current != NULL) {
            somme += current->proba;
            current = current->suivante;
        }

        // Vérifier si la somme est entre 0.99 et 1.00
        if (somme < 0.99 || somme > 1.00) {
            printf("la somme des probabilites du sommet %d est %.6f\n", i + 1, somme);
            estMarkov = 0;
        }
    }

    // Afficher le résultat final UNE SEULE FOIS
    if (estMarkov) {
        printf("Le graphe est un graphe de Markov\n");
    } else {
        printf("Le graphe n'est pas un graphe de Markov\n");
    }

    return estMarkov;
}


// Fonction getId
char* getId(int num) {
    static char id[10];
    int index = 0;
    int temp = num;

    while (temp > 0) {
        temp--;
        id[index++] = 'A' + (temp % 26);
        temp /= 26;
    }
    // Inverser la chaîne
    for (int i = 0; i < index / 2; i++) {
        char temp = id[i];
        id[i] = id[index - 1 - i];
        id[index - 1 - i] = temp;
    }

    id[index] = '\0';
    return id;
}

// Fonction pour generer le fichier mermaid.txt
void genererFichierMermaid(listeAdj g, const char* nomFichier) {
    FILE *file = fopen(nomFichier, "w");
    if (!file) {
        perror("Impossible de créer le fichier");
        return;
    }

    // Écrire les sommets avec leur numéro
    for (int i = 0; i < g.nb_sommets; i++) {
        fprintf(file, "%s((%d))\n", getId(i + 1), i + 1);
    }

    // Écrire les arêtes avec les probabilités
    for (int i = 0; i < g.nb_sommets; i++) {
        cell* current = g.tab_liste[i].head;
        while (current != NULL) {
            fprintf(file, "%s -->|%.2f|%s\n",
                    getId(i + 1),
                    current->proba,
                    getId(current->sommet_arrivee));
            current = current->suivante;
        }
    }

    fclose(file);

    }
