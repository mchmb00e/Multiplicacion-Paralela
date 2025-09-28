#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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

void file_content(FILE *f) {
    int c;
    while ((c = fgetc(f)) != EOF) {
        putchar(c); // ejemplo: mostrar el contenido
    }
}

unsigned long long mul_tradicional_seq(int *A, int *B, int ta, int tb) {
    unsigned long long *partial_sum;
    unsigned long long total = 0;
    unsigned long long partial_number = 0;

    partial_sum = calloc(tb, sizeof(unsigned long long));

    float E_cpu;
    long E_wall;
    time_t ts, te;
    clock_t cs, ce;

    ts = time(NULL);
    cs = clock();

    for (int i = 0; i < ta; i++) {
        partial_number = partial_number * 10 + A[i];
    }
    for (int i = 0; i < tb; i++) {
        partial_sum[i] = partial_number * B[i];
        partial_sum[i] *= (unsigned long long) pow(10, tb - (i + 1));
        total += partial_sum[i];
    }

    ce = clock();
    te = time(NULL);
    E_wall = (long) (te - ts);
    E_cpu = (float)(ce - cs) / CLOCKS_PER_SEC;
    printf("Elapsed CPU Time %f Wall Time %ld\n", E_cpu,E_wall);

    free(partial_sum);
    return total;
}

void *Usage(char *argv[]) {
    printf("Usage: %s k -M -O < data.txt\n", argv[0]);
    exit(1);
}


int main(int argc, char *argv[]) {

    // Declaración de variables
    int size_A, size_B, k;
    int *A, *B;
    char method, mode;
    unsigned long long res;

    
    // Verificar parámetros
    if (argc != 4) {
        Usage(argv);
    } else {
        k = atoi(argv[1]); // Lectura de cantidad de hilos
        method = argv[2][1]; // Lectura del método de multiplicación
        mode = argv[3][1]; // Lectura del modo de ejecución


        if (mode == VERBOSE_MODE) {
            printf("-- Contenido del archivo --\n\n");
            file_content(stdin);
            printf("\n\n -- Fin del contenido --\n\n");
            rewind(stdin); // ⚠️ solo funciona si stdin es un archivo real, no un pipe
        }


        // Lectura de digitos de num. 1
        scanf("%d", &size_A);
        A = calloc(size_A, sizeof(int));
        for (int i = 0; i < size_A; i++)
            scanf("%d", &A[i]);

        // Lectura de digitos de num. 2
        scanf("%d", &size_B);
        B = calloc(size_B, sizeof(int));
        for (int i = 0; i < size_B; i++)
            scanf("%d", &B[i]);

        if (k == 1) { // Forma secuencial
            if (method == TRADITIONAL_METHOD) {
                res = mul_tradicional_seq(A, B, size_A, size_B);
                if (mode == SILENCE_MODE) {
                    printf("Cantidad de digitos\n    Numero 1: %d\n    Numero 2: %d\n\n", size_A, size_B);
                } else if (mode == VERBOSE_MODE) {
                    printf("Resultado: %llu\n", res);
                }
            } else if (method == RUSSIAN_METHOD) {
                // Implementación rusa
            }

        } else { // Forma paralela
            printf("\n\nImplementación paralela.\n\n");
        }


        // Liberación de memoria de A y B
        free(A);
        free(B);

    }

    return 0;
}