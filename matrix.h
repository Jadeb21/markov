#ifndef MATRIX_H
#define MATRIX_H
#include "list.h"
#include "tarjan.h"

typedef struct {
    double **data;
    int lignes;
    int cols;
} t_matrix;

t_matrix* creer_matrice_liste_adjacence(listeAdj* g);
t_matrix* creer_matrice_valzeros(int lignes, int cols);
t_matrix* multiplication_matrice(t_matrix* a, t_matrix* b);
t_matrix* difference_matrice(t_matrix* a, t_matrix* b);
void copie_matrice(t_matrix* src, t_matrix* dest);
t_matrix* multiplication_matrice(t_matrix* M, t_matrix* N);
double difference_matrix(t_matrix* M, t_matrix* N);
void afficher_matrice(t_matrix* matrice);
void liberer_matrice(t_matrix* matrice);
t_matrix* subMatrix(t_matrix* matrix, t_partition* part, int compo_index);
/**
 * @brief Extract a submatrix corresponding to a specific component of a graph partition.
 *
 * @param matrix The original adjacency matrix of the graph.
 * @param part The partition of the graph into strongly connected components.
 * @param compo_index The index of the component to extract.
 * @return t_matrix The submatrix corresponding to the specified component.
 *
 * We changed t_matrix to Matrix. 
*/

//Matrix subMatrix(Matrix matrix, t_partition part, int compo_index);
#endif
