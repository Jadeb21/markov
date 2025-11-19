#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

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

Matrix* multiplication_matrice(Matrix* a, Matrix* b){
  if (a->cols != b->lignes) {
    printf("Attention : Matrice de dimension differentes\n");
    return NULL;
  }
  Matrix* result = creer_matrice_valzeros(a->lignes, b->cols);
  for (int i = 0; i < a->lignes; i++) {
    for (int j = 0; j < b->cols; j++) {
      for (int k = 0; k < a->cols; k++) {
        result->data[i][j] += a->data[i][k] * b->data[k][j];
      }
    }
  }
  return result;
}