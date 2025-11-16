#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "list.h"

// Dans utils.c, utilisez l'algorithme qui fonctionne
char* getID(int num) {
    char* id = malloc(10 * sizeof(char));
    int index = 0;
    int temp = num;

    while (temp > 0) {
        temp--;
        id[index++] = 'A' + (temp % 26);
        temp /= 26;
    }
    // Inverser la chaîne
    for (int i = 0; i < index / 2; i++) {
        char tmp = id[i];
        id[i] = id[index - 1 - i];
        id[index - 1 - i] = tmp;
    }

    id[index] = '\0';
    return id;
}