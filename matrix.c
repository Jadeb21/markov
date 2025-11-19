#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "list.h"

struct listeAdj* g;
Matrix* creer_matrice_liste_adjacence(listeAdj* g) {
    int n = g->nb_sommets;
    Matrix* matrice = (Matrix*)malloc(sizeof(Matrix));
    matrice->lignes = n;
    matrice->cols = n;
    matrice->data = (double**)malloc(sizeof(double*) * n);

    // Initialiser à 0
    for (int i = 0; i < n; i++) {
        matrice->data[i] = (double*)calloc(n, sizeof(double));
    }

    // Remplir avec les probabilités réelles depuis la liste d'adjacence
    for (int i = 0; i < n; i++) {
        cell* current = g->tab_liste[i].head;
        while (current != NULL) {
            int etat_arrivee = current->sommet_arrivee - 1;  // -1 pour l'indice C
            float proba_reelle = current->proba;
            matrice->data[i][etat_arrivee] = (double)proba_reelle;
            current = current->suivante;
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

void afficher_matrice(Matrix* matrice) {
    for (int i = 0; i < matrice->lignes; i++) {
        for (int j = 0; j < matrice->cols; j++) {
            printf("%.3f\t", matrice->data[i][j]);
        }
        printf("\n");
    }
}

