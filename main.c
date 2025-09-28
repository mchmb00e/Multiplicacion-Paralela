#include <stdio.h>
#include <stdlib.h>

#define VERBOSE_MODE "V"
#define SILENCE_MODE "S"
#define TRADITIONAL_METHOD "T"
#define RUSSIAN_METHOD "R"

int main(int argc, char *argv[]) {

    // Declaración de variables
    int m, n, k;
    int *A, *B;
    char method, mode;


    // Lectura de cantidad de hilos
    k = atoi(argv[1]);
    printf("k = %d\n", k);

    // Lectura del método de multiplicación
    

    // Lectura del modo de ejecución

    // Lectura de cantidad de digitos del num. 1
    scanf("%d", &m);
    printf("m = %d\n", m);
    A = calloc(m, sizeof(int));
    for (int i = 0; i < m; i++) {
        scanf("%d", &A[i]);
        printf("Scanf A[%d]: %d\n", i, A[i]);
    }

    // Lectura de cantidad de digitos del num. 2
    scanf("%d", &n);
    printf("n = %d\n", n);
    B = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &B[i]);
        printf("Scanf B[%d]: %d\n", i, B[i]);
    }


    if (k == 1) {
        printf("Implementación secuencial\n");
    } else {
        printf("Implementación paralela\n");
    }





    // Liberación de memoria de A y B
    free(A);
    free(B);

    return 0;
}