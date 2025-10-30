#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "hasse.h"
#include "utils.h"

int main() {
    // 1. Read the graph from file
    const char *filename = "data/exemple1.txt"; // your input file
    listeAdj g = readGraph(filename);

    // 2. Display the adjacency list
    printf("Adjacency List of the graph:\n");
    displayListeAdj(g);

    // 3. Free memory
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
