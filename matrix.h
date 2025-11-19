#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    double **data;
    int lignes;
    int cols;
} Matrix;

Matrix* creer_matrice_adj(int n, int** liste_adjacence, int* tailles_listes);
Matrix* creer_matrice_valzeros(int lignes, int cols);
void copie_matrice(Matrix* src, Matrix* dest);

#endif