#include <malloc.h>
#include "hasse.h"
#include "list.h"
#include "tarjan.h"

// Recencer
t_link_array* rencenser(listeAdj *g, int *t_link_corresp) {
    t_link_array *link = creer_list_link(g->nb_sommets);
    for (int i=0; i < g->nb_sommets; i++) {
        int Ci = t_link_corresp[i];
        cell *voisin = g->tab_liste[i].head;

        while (voisin != NULL) {
            int j = voisin->sommet_arrivee -1;
            int Cj = t_link_corresp[j];

            if (Ci != Cj) {
                ajouter_link(link, Ci, Cj);
            }
            voisin = voisin->suivante;
        }
    }
    return link;
}

t_link_array* creer_list_link(int nb_sommets) {
    t_link_array *link = malloc(sizeof(t_link_array));
    link->links=malloc(nb_sommets * nb_sommets * sizeof(t_link));
    link->log_size = 0;
    link->alloc_size = nb_sommets * nb_sommets;
    return link;
}

int* creer_tab_corresp(t_partition *partition, int nb_sommets) {
    int *tab = malloc(nb_sommets * sizeof(int));
    for (int i = 0; i < partition->taille; i++) {
        for (int j = 0; j < partition->classes[i].taille; j++) {
            int sommet = partition->classes[i].sommets[j];
            tab[sommet - 1] = i;
        }
    }

    return tab;
}

//Rajout de chaque lien
void ajouter_link(t_link_array *link, int from, int to) {
    if (link->log_size < link->alloc_size) {
        link->links[link->log_size].from =from;
        link->links[link->log_size].to =to;
        link->log_size++;
    }
}

//generer le fichier Mermaid du diagramme de Hasse
void genererHasseMermaid(t_partition *partition, t_link_array *liens, const char* nomFichier, int avecRedondances) {
    FILE *file = fopen(nomFichier, "w");
    fprintf(file, "---\n");
    fprintf(file, "config:\n");
    fprintf(file, "  layout: elk\n");
    fprintf(file, "  theme: neo\n");
    fprintf(file, "  look: neo\n");
    fprintf(file, "---\n");
    fprintf(file, "flowchart LR\n");

    // Sommets du diagramme de Hasse
    for (int i = 0; i < partition->taille; i++) {
        fprintf(file, "C%d(\"{", i+1);

        // Afficher tous les sommets de la classe
        for (int j = 0; j < partition->classes[i].taille; j++) {
            fprintf(file, "%d", partition->classes[i].sommets[j]);
            if (j < partition->classes[i].taille - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "}\")\n");
    }

    // Supprimer les redondances
    if (!avecRedondances) {
        removeTransitiveLinks(liens);
    }

    // Liens entre classes
    for (int i = 0; i < liens->log_size; i++) {
        int from = liens->links[i].from;
        int to = liens->links[i].to;

        if (from >= 0 && from < partition->taille && to >= 0 && to < partition->taille) {
            fprintf(file, "C%d --> C%d\n", from+1, to+1);
        }
    }
    fclose(file);
}

//Supprimer les redondances
void removeTransitiveLinks(t_link_array *p_link_array)
{
    int i = 0;
    while (i < p_link_array->log_size)
    {
        t_link link1 = p_link_array->links[i];
        int to_remove = 0;
        for (int j = 0; j < p_link_array->log_size && !to_remove; j++)
        {
            if (j != i)
            {
                t_link link2 = p_link_array->links[j];
                if (link2.from == link1.from)
                {
                    for (int k = 0; k < p_link_array->log_size && !to_remove; k++)
                    {
                        if (k != i && k != j)
                        {
                            t_link link3 = p_link_array->links[k];
                            if (link3.from == link2.to && link3.to == link1.to)
                            {
                                to_remove = 1;
                            }
                        }
                    }
                }
            }
        }
        if (to_remove)
        {
            p_link_array->links[i] = p_link_array->links[p_link_array->log_size - 1];
            p_link_array->log_size--;
        }
        else
        {
            i++;
        }
    }
}