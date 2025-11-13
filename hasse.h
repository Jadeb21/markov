#ifndef __HASSE_H__
#define __HASSE_H__
#include "list.h"
#include "tarjan.h"

typedef struct {
    int from;
    int to;
} t_link;

typedef struct {
    t_link *links;
    int log_size;
    int alloc_size;
} t_link_array;

t_link_array* rencenser(listeAdj *g, int *t_link_corresp);
t_link_array* creer_list_link(int nb_sommets);
int* creer_tab_corresp(t_partition *partition, int nb_sommets);
void ajouter_link(t_link_array *link, int from, int to);
void removeTransitiveLinks(t_link_array *p_link_array);
void genererHasseMermaid(t_partition *partition, t_link_array *link, const char* nomFichier, int avecRedondances);
/**
 * @brief Creates a link array from the given partition and graph.
 *
 * @param part The partition of the graph.
 * @param graph The adjacency list representation of the graph.
 * @return The created link array.
 */

#endif