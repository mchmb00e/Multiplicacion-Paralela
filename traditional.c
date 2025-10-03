#include "traditional.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *traditional_seq(int *A, int *B, int tA, int tB) {
    int **M;
    int x, y, prod, carry;

    M = calloc(tB, sizeof(int*));
    for (int i = 0; i < tB; i++) {
        M[i] = calloc(tA + tB, sizeof(int));
    }

    printf("tA = %d | tB = %d\n\n", tA, tB);

    for (int i = 0; i < tB; i++) {
        y = B[tB - 1 - i]; 
        carry = 0;

        for (int j = 0; j < tA; j++) {
            x = A[tA - 1 - j];

            prod = x * y + carry;

            M[i][tA + tB - 1 - (j + i)] = prod % 10;
            carry = prod / 10;
        }


        if (carry > 0) {
            M[i][tA + tB - 1 - (tA + i)] = carry;
        }
    }

    int *result = calloc(tA + tB, sizeof(int));
    for (int i = 0; i < tB; i++) {
        for (int j = 0; j < tA + tB; j++) {
            result[j] += M[i][j];
        }
    }

    for (int j = tA + tB - 1; j > 0; j--) {
        if (result[j] >= 10) {
            result[j-1] += result[j] / 10;
            result[j] %= 10;
        }
    }

    for (int i = 0; i < tA + tB; i++) {
        printf("%d", result[i]);
    }
    printf("\n");

    for (int i = 0; i < tB; i++) {
        free(M[i]);
    }
    free(M);

    return result;
}