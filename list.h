#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure de type cellule :
typedef struct cellule {
    int sommet_arrivee;
    float proba;
    struct cellule* suivante;
} Cellule;

// Structure de type liste :
typedef struct liste {
    Cellule* head;
} Liste;

// structure de liste adjacente
typedef struct liste_adj{
    Liste* tab_liste;
    int nb_sommets;
} ListeAdj;