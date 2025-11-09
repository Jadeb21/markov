#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "hasse.h"
#include "utils.h"
#include "tarjan.h"

int main() {

    // laisser l'utilisateur choisir le fichier
    char input[100];
    char filename[120];

    printf("Quel fichier voulez-vous utiliser ?\n");
    printf("Options : exemple1, exemple1_chatGPT_fixed, exemple1_from_chatGPT, exemple2, exemple3, exemple4_2check, exemple_hasse1, exemple_scc1, exemple_valid_step3\n");
    scanf("%99s", input);
    sprintf(filename, "../data/%s.txt", input);
    printf("Fichier choisi : %s\n", filename);

    listeAdj g = readGraph(filename);

    // Affiche la liste adjacente
    printf("Liste Adjacente du graphe :\n");
    displayListeAdj(g);
    printf("\n");

    // Affiche la vérification du graphe de Markov
    printf("Verification graphe de Markov :\n");
    verifierGrapheMarkov(g);
    printf("\n");

    // Génère le fichier Mermaid
    char mermaidFile[150];
    sprintf(mermaidFile, "../data/%s_mermaid.txt", input);
    genererFichierMermaid(g, mermaidFile);
    printf("\n");

    // Affiche l'algo de tarjan
    t_partition *partition = algorithme_tarjan_partition(g);
    printf("\n");


    // Memoire libere
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
