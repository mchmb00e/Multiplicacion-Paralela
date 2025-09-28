#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define VERBOSE_MODE 'V'
#define SILENCE_MODE 'S'
#define TRADITIONAL_METHOD 'T'
#define RUSSIAN_METHOD 'R'

int array_to_int(int n, int *A) {
    int number = 0;
    for (int i = 0; i < n; i++) {
        number = number * 10 + A[i];
    }
    return number;
}


int main(int argc, char *argv[]) {

    // Declaración de variables
    int size_A, size_B, k;
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
    scanf("%d", &size_A);
    printf("Tamaño del primer número  = %d | Número: ", size_A);
    A = calloc(size_A, sizeof(int));
    for (int i = 0; i < size_A; i++) {
        scanf("%d", &A[i]);
        printf("%d", A[i]);
    }
    printf("\n");

    // Lectura de cantidad de digitos del num. 2
    scanf("%d", &size_B);
    printf("Tamaño del segundo número = %d | Número: ", size_B);
    B = calloc(size_B, sizeof(int));
    for (int i = 0; i < size_B; i++) {
        scanf("%d", &B[i]);
        printf("%d", B[i]);
    }
    printf("\n");


    if (k == 1) {
        printf("\n\nImplementación secuencial.\n\n");
        if (method == TRADITIONAL_METHOD) {
            int pivot, sum = 0, *C;
            C = calloc(size_B, sizeof(int));
            pivot = array_to_int(size_A, A);
            for (int i = 0; i < size_B; i++) {
                C[i] = B[i] * pivot;
            }
            for (int i = 0; i < size_B; i++) {
                printf("sum = sum + %d * 10^%d\n", C[i], size_B-(i+1));
                sum = sum + C[i] * pow(10, size_B-(i+1));
            }
            printf("Resultado: %d\n", sum);
        } else if (method == RUSSIAN_METHOD) {

        }

    } else {
        printf("\n\nImplementación paralela.\n\n");
    }


    // Liberación de memoria de A y B
    free(A);
    free(B);

    return 0;
}