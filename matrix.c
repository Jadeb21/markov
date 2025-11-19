#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <math.h>

Matrix* creer_matrice_adj(int n, int** liste_adjacence, int* tailles_listes) {
  Matrix* matrice=(Matrix*)malloc(sizeof(Matrix));
  matrice->lignes = n;
  matrice->cols=n;
  matrice->data =(double**)malloc(sizeof(double*)*n);

  for (int i = 0; i < n; i++) {
    matrice->data[i] = (double*)calloc(n, sizeof(double));
    }
   	//Probabilité
  	for (int i = 0; i < n; i++) {
     	int nb_voisins = tailles_listes[i];
     	if(nb_voisins > 0) {
       	double probability = 1.0/nb_voisins;
       	for (int j = 0; j < nb_voisins; j++) {
                int etat_arrivee = liste_adjacence[i][j] - 1;
                matrice->data[i][etat_arrivee] = probability;
            }
        }
  	}
    return matrice;
}

Matrix* creer_matrice_valzeros(int lignes, int cols){
  Matrix* matrice = (Matrix*)malloc(sizeof(Matrix));
  matrice->lignes = lignes;
  matrice->cols = cols;
  matrice->data =(double**)malloc(sizeof(double*)*lignes);
  for (int i = 0; i < lignes; i++) {
    matrice->data[i] = (double*)calloc(cols, sizeof(double));
  }
  return matrice;
}

void copie_matrice(Matrix* src, Matrix* dest){
  if (src->lignes != dest->lignes || src->cols != dest->cols) {
    printf("Attention : Matrice de taille différentes\n");
    return;
    }
    for (int i = 0; i < src->lignes; i++) {
      for (int j = 0; j < src->cols; j++) {
        dest->data[i][j] = src->data[i][j];
      }
  }
}

Matrix* multiplication_matrice(Matrix* M, Matrix* N){
  if (M->cols != N->lignes) {
    printf("Attention : Matrice de dimension differentes\n");
    return NULL;
  }
  Matrix* result = creer_matrice_valzeros(M->lignes, N->cols);
  for (int i = 0; i < M->lignes; i++) {
    for (int j = 0; j < N->cols; j++) {
      for (int k = 0; k < M->cols; k++) {
        result->data[i][j] += M->data[i][k] * N->data[k][j];
      }
    }
  }
  return result;
}


/*Matrix* difference_matrix(Matrix* M, Matrix* N){
	if (M->lignes != N->lignes || M->cols != N->cols){
		printf("Attention: Matrice de tailles differentes\n");
		return NULL;
	}
	Matrix* result = creer_matrice_valzeros(M->lignes, M-> cols);
		for (int i = 0; i < M->lignes; i++) {
			for (int j = 0; j < M->cols; j++) {
				result->data[i][j] = M->data[i][j] - N->data[i][j];
			}
		}
	return result;
}
*/

double difference_matrix(Matrix* M, Matrix* N){
  if (M->lignes != N->lignes || M->cols != N->cols) {
        printf("Attention: Matrices de tailles différentes\n");
        return -1.0;
    }

    double difference = 0.0;
    for (int i = 0; i < M->lignes; i++) {
        for (int j = 0; j < M->cols; j++) {
            difference += fabs(M->data[i][j] - N->data[i][j]); //fabs --> pour calculer la valeur absolue
        }
    }

    return difference;
}