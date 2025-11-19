#ifndef MATRIX_H
#define MATRIX_H
#include "list.h"
typedef struct {
    double **data;
    int lignes;
    int cols;
} Matrix;

Matrix* creer_matrice_liste_adjacence(listeAdj* g);
Matrix* creer_matrice_valzeros(int lignes, int cols);
Matrix* multiplication_matrice(Matrix* a, Matrix* b);
Matrix* difference_matrice(Matrix* a, Matrix* b);
void copie_matrice(Matrix* src, Matrix* dest);
Matrix* multiplication_matrice(Matrix* M, Matrix* N);
double difference_matrix(Matrix* M, Matrix* N);
void afficher_matrice(Matrix* matrice);

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
