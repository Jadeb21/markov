#include "tarjan.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Initialisation des structures de données pour Tarjan
t_tarjan_data* initialiser_tarjan(listeAdj *g) {
    t_tarjan_data *data = malloc(sizeof(t_tarjan_data));
    data->graphe = g;
    data->sommets = malloc(g->nb_sommets * sizeof(t_tarjan_vertex));
    data->pile = malloc(g->nb_sommets * sizeof(int));
    data->size_pile = 0;
    data->count = 0;
    data->partition = NULL;

    // Initialisation de chaque sommet
    for (int i = 0; i < g->nb_sommets; i++) {
        data->sommets[i].id = i + 1;
        data->sommets[i].num = -1;
        data->sommets[i].num_access = -1;
        data->sommets[i].in_pile = 0;
    }

    return data;
}

// Libère la mémoire de Tarjan
void liberer_tarjan(t_tarjan_data *data) {
    free(data->sommets);
    free(data->pile);
    free(data);
}

// Ajoute une classe à la partition
void ajouter_classe(t_partition *partition, int *sommets, int taille) {
    if (partition->taille >= partition->capacite) {
        partition->capacite *= 2;
        partition->classes = realloc(partition->classes, partition->capacite * sizeof(t_classe));
    }
    t_classe *classe = &partition->classes[partition->taille];

    // Nom de la classe
    snprintf(classe->nom, sizeof(classe->nom), "C%d", partition->taille + 1);

    // Copier les sommets
    classe->sommets = malloc(taille * sizeof(int));
    memcpy(classe->sommets, sommets, taille * sizeof(int));
    classe->taille = taille;
    classe->capacite = taille;

    partition->taille++;
}

// Algorithme pour trouver des composantes fortement connexes
void tarjan_visite(t_tarjan_data *data, int sommet_index) {
    t_tarjan_vertex *sommet_courant = &data->sommets[sommet_index];

    // Assigner un numéro au sommet
    sommet_courant->num = data->count;
    sommet_courant->num_access = data->count;
    data->count++;

    // Empiler le sommet
    data->pile[data->size_pile++] = sommet_index;
    sommet_courant->in_pile = 1;

    // Parcourir les sommets voisins
    cell *current = data->graphe->tab_liste[sommet_index].head;
    while (current != NULL) {
        int voisin_index = current->sommet_arrivee - 1;
        t_tarjan_vertex *sommet_voisin = &data->sommets[voisin_index];

        if (sommet_voisin->num == -1) {
            tarjan_visite(data, voisin_index);
            sommet_courant->num_access = (sommet_courant->num_access < sommet_voisin->num_access) ? sommet_courant->num_access : sommet_voisin->num_access;
        } else if (sommet_voisin->in_pile) {
            sommet_courant->num_access = (sommet_courant->num_access < sommet_voisin->num) ? sommet_courant->num_access : sommet_voisin->num;
        }

        current = current->suivante;
    }
    if (sommet_courant->num_access == sommet_courant->num) {
        // Stocke temporairement les sommets de la composante
        int composante[data->graphe->nb_sommets];
        int taille_composante = 0;

        // Extraire les sommets de la pile
        int voisin_index; //indice du voisin dépilé
        do {
            voisin_index = data->pile[--data->size_pile];
            data->sommets[voisin_index].in_pile = 0;
            composante[taille_composante++] = data->sommets[voisin_index].id;
        } while (voisin_index != sommet_index);

        // Ajoute à la partition
        if (data->partition != NULL) {
            ajouter_classe(data->partition, composante, taille_composante);
        }

        // Affichage des composantes
        printf("Composante C%d: {", data->partition->taille);
        for (int i = taille_composante - 1; i >= 0; i--) {
            printf("%d", composante[i]);
            if (i > 0) printf(",");
        }
        printf("}\n");
    }
}

// Algorithme principal qui retourne une partition
t_partition* algorithme_tarjan_partition(listeAdj g) {
    t_tarjan_data *data = initialiser_tarjan(&g);

    // Initialisation de la partition
    data->partition = malloc(sizeof(t_partition));
    data->partition->classes = malloc(g.nb_sommets * sizeof(t_classe));
    data->partition->taille = 0;
    data->partition->capacite = g.nb_sommets;

    printf("Algorithme de Tarjan\n");

    // Application de l'algo de Tarjan
    for (int i = 0; i < g.nb_sommets; i++) {
        if (data->sommets[i].num == -1) {
            tarjan_visite(data, i);
        }
    }
    t_partition *resultat = data->partition;
    liberer_tarjan(data);
    return resultat;
}

// Fonction pour afficher une partition
void afficher_partition(t_partition *partition) {
    printf("Partition du graphe :\n");
    for (int i = 0; i < partition->taille; i++) {
        printf("%s: {", partition->classes[i].nom);
        for (int j = 0; j < partition->classes[i].taille; j++) {
            printf("%d", partition->classes[i].sommets[j]);
            if (j < partition->classes[i].taille - 1) printf(",");
        }
        printf("}\n");
    }
}