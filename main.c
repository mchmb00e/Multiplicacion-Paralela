#include <stdio.h>
#include <stdlib.h>

#define VERBOSE_MODE 'V'
#define SILENCE_MODE 'S'
#define TRADITIONAL_METHOD 'T'
#define RUSSIAN_METHOD 'R'

int main(int argc, char *argv[]) {

    // Declaración de variables
    int m, n, k;
    int *A, *B;
    char method, mode;


    // Lectura de cantidad de hilos
    k = atoi(argv[1]);
    printf("Cantidad de threads (k) = %d\n", k);

    // Lectura del método de multiplicación
    method = argv[2][1];
    printf("\nMetodo seleccionado: ");
    if (method == TRADITIONAL_METHOD) {
        printf("TRADICIONAL\n");
    } else if (method == RUSSIAN_METHOD) {
        printf("RUSO\n");
    }
    printf("\n");

    // Lectura del modo de ejecución


    // Lectura de cantidad de digitos del num. 1
    scanf("%d", &m);
    printf("Tamaño del primer número  = %d | Número: ", m);
    A = calloc(m, sizeof(int));
    for (int i = 0; i < m; i++) {
        scanf("%d", &A[i]);
        printf("%d", A[i]);
    }
    printf("\n");

    // Lectura de cantidad de digitos del num. 2
    scanf("%d", &n);
    printf("Tamaño del segundo número = %d | Número: ", n);
    B = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &B[i]);
        printf("%d", B[i]);
    }
    printf("\n");


    if (k == 1) {
        printf("\n\nImplementación secuencial.\n\n");

        

    } else {
        printf("\n\nImplementación paralela.\n\n");
    }


    // Liberación de memoria de A y B
    free(A);
    free(B);

    return 0;
}