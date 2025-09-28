#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int m, n; // Cantidad de digitos de A y B
    int *A, *B; // Digitos de A y B

    scanf("%d", &m);
    printf("m = %d\n", m);

    A = calloc(m, sizeof(int));

    for (int i = 0; i < m; i++) {
        scanf("%d", &A[i]);
        printf("Scanf A[%d]: %d\n", i, A[i]);
    }

    scanf("%d", &n);
    printf("n = %d\n", n);

    B = calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &B[i]);
        printf("Scanf A[%d]: %d\n", i, B[i]);
    }

    free(A);
    free(B);

    return 0;
}