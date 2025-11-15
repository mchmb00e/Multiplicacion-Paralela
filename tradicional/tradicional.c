#include "tradicional.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *tradicional_secuencial(int *A, int *B, int tA, int tB) {
    int **M;
    int a, b, producto, acarreo, tR = tA + tB;

    M = calloc(tB, sizeof(int*));
    for (int i = 0; i < tB; i++) {
        M[i] = calloc(tR, sizeof(int));
    }

    printf("tA = %d | tB = %d\n\n", tA, tB);

    for (int i = 0; i < tB; i++) {
        b = B[tB - (i + 1)];
        acarreo = 0;

        for (int j = 0; j < tA; j++) {
            a = A[tA - (j + 1)];

            producto = a * b + acarreo; // 1, 2, 4. 

            M[i][tR - 1 - (j + i)] = producto % 10; // 3, 4.
            acarreo = producto / 10;               // 1, 4.
        }


        if (acarreo > 0) { // 1.
            M[i][tR - (tA + i + 1)] = acarreo; // 1, 3.
        }
    }

    int *result = calloc(tR, sizeof(int)); // 3.
    for (int i = 0; i < tB; i++) {
        for (int j = 0; j < tR; j++) { // 3.
            result[j] += M[i][j];
        }
    }

    for (int j = tR - 1; j > 0; j--) {
        if (result[j] >= 10) {
            result[j-1] += result[j] / 10;
            result[j] %= 10;
        }
    }

    for (int i = 0; i < tB; i++) {
        free(M[i]);
    }
    free(M);

    return result;
}