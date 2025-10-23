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