#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "hasse.h"
#include "utils.h"

int main() {
    // Lire le graphe avec les exemples
    const char *filename = "../data/exemple1.txt";
    listeAdj g = readGraph(filename);

    // Affiche la liste adjacente
    printf("Adjacency List of the graph:\n");
    displayListeAdj(g);

    // Memoire liberer
    for (int i = 0; i < g.nb_sommets; i++) {
        cell *current = g.tab_liste[i].head;
        while (current != NULL) {
            cell *tmp = current;
            current = current->suivante;
            free(tmp);
        }
    }
    free(g.tab_liste);

    return 0;
}
