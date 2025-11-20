#ifndef TARJAN_H
#define TARJAN_H

#include "list.h"

// structure pour identification de chaque sommet
typedef struct tarjan_vertex {
    int id;
    int num;
    int num_access;
    int in_pile;
} t_tarjan_vertex;

typedef struct classe {
    char nom[10];
    int *sommets;
    int taille;
    int capacite;
} t_classe;

typedef struct partition {
    t_classe *classes;
    int taille;
    int capacite;
} t_partition;


typedef struct tarjan_data {
    t_tarjan_vertex *sommets;
    int *pile;
    int size_pile;
    int count;
    listeAdj *graphe;
    t_partition *partition;
} t_tarjan_data;

t_tarjan_data* initialiser_tarjan(listeAdj *g);
void tarjan_parcours(t_tarjan_data *data, int sommet_index);
t_partition* algorithme_tarjan(listeAdj g);
void liberer_tarjan(t_tarjan_data *data);
void afficher_partition(t_partition *partition);
t_partition* tarjan_calculer_partition(listeAdj g);

#endif