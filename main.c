#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "tradicional/tradicional.h"

#define MODO_VERBOSO 'V'
#define MODO_SILENCIOSO 'S'
#define METODO_TRADICIONAL 'T'
#define METODO_RUSO 'R'

int array_to_int(int n, int *A) {
    int number = 0;
    for (int i = 0; i < n; i++) {
        number = number * 10 + A[i];
    }
    return number;
}

void file_content(FILE *f) {
    int c;
    while ((c = fgetc(f)) != EOF) {
        putchar(c); // ejemplo: mostrar el contenido
    }
}

void *Usage(char *argv[]) {
    printf("Usage: %s k -M -O < data.txt\n", argv[0]);
    exit(1);
}


int main(int argc, char *argv[]) {

    // Declaración de variables
    int tA, tB, k, *A, *B, *R;
    char metodo, modo;

    
    // Verificar parámetros
    if (argc != 4) {
        Usage(argv);
    } else {
        k = atoi(argv[1]);
        metodo = argv[2][1];
        modo = argv[3][1];

        // Lectura de digitos de num. 1
        scanf("%d", &tA);
        A = calloc(tA, sizeof(int));
        for (int i = 0; i < tA; i++)
            scanf("%d", &A[i]);

        // Lectura de digitos de num. 2
        scanf("%d", &tB);
        B = calloc(tB, sizeof(int));
        for (int i = 0; i < tB; i++)
            scanf("%d", &B[i]);

        R = calloc(tA + tB, sizeof(int));

        if (metodo == METODO_TRADICIONAL) {
            if (k == 1) {
                R = tradicional_secuencial(A, B, tA, tB);
            } else {
                printf("Implementación tradicional paralela\n");
            }
        }

        if (metodo == METODO_RUSO) {
            if (k == 1) {
                printf("Implementación rusa secuencial\n");
            } else {
                printf("Implementación rusa paralela\n");
            }
        }

        printf("Resultado: ");
                    
        for (int i = 0; i < tA + tB; i++) {
            printf("%d", R[i]);
        }

        printf("\n");

        // Liberación de memoria de A y B
        free(A);
        free(B);

    }

    return 0;
}