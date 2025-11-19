#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <math.h>

t_matrix* creer_matrice_adj(int n, int** liste_adjacence, int* tailles_listes) {
  t_matrix* matrice=(t_matrix*)malloc(sizeof(t_matrix));
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

t_matrix* creer_matrice_valzeros(int lignes, int cols){
  t_matrix* matrice = (t_matrix*)malloc(sizeof(t_matrix));
  matrice->lignes = lignes;
  matrice->cols = cols;
  matrice->data =(double**)malloc(sizeof(double*)*lignes);
  for (int i = 0; i < lignes; i++) {
    matrice->data[i] = (double*)calloc(cols, sizeof(double));
  }
  return matrice;
}

void copie_matrice(t_matrix* src, t_matrix* dest){
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

t_matrix* multiplication_matrice(t_matrix* M, t_matrix* N){
  if (M->cols != N->lignes) {
    printf("Attention : Matrice de dimension differentes\n");
    return NULL;
  }
  t_matrix* result = creer_matrice_valzeros(M->lignes, N->cols);
  for (int i = 0; i < M->lignes; i++) {
    for (int j = 0; j < N->cols; j++) {
      for (int k = 0; k < M->cols; k++) {
        result->data[i][j] += M->data[i][k] * N->data[k][j];
      }
    }
  }
  return result;
}


/*t_matrix* difference_matrix(t_matrix* M, t_matrix* N){
	if (M->lignes != N->lignes || M->cols != N->cols){
		printf("Attention: Matrice de tailles differentes\n");
		return NULL;
	}
	t_matrix* result = creer_matrice_valzeros(M->lignes, M-> cols);
		for (int i = 0; i < M->lignes; i++) {
			for (int j = 0; j < M->cols; j++) {
				result->data[i][j] = M->data[i][j] - N->data[i][j];
			}
		}
	return result;
}
*/

double difference_matrix(t_matrix* M, t_matrix* N){
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
