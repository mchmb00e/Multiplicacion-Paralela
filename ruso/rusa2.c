#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Message{
    unsigned int myid, numthreads;
    unsigned long long a, b;
};

unsigned long long result = 0;
pthread_mutex_t mutex;

void *RussianMultiply(void *p){
    struct Message *m = (struct Message *)p;
    unsigned long long partial_result = 0;
    unsigned long long a = m->a;
    unsigned long long b = m->b;
    int step = 0;

    float E_cpu;
    long E_wall;
    time_t ts, te;
    clock_t cs, ce;

    ts = time(NULL);
    cs = clock();

    while (a > 0) {
        if (step % m->numthreads == m->myid){
            if (a % 2 != 0)
                partial_result += b;
        }
        a /= 2;
        b *= 2;
        step++;
    }

    pthread_mutex_lock(&mutex);
    result += partial_result;
    pthread_mutex_unlock(&mutex);

    ce = clock();
    te = time(NULL);
    E_wall = (long)(te - ts);
    E_cpu = (float)(ce - cs) / CLOCKS_PER_SEC;

    printf("From %d - Elapsed CPU Time %f Wall Time %ld\n", m->myid, E_cpu, E_wall);

    pthread_exit(0);
}

int main(int argc, char **argv){
    if (argc != 2) {
        printf("Usage: %s k < data.txt\n", argv[0]);
        return 1;
    }

    unsigned int k = atoi(argv[1]);
    pthread_t *thread = calloc(k, sizeof(pthread_t));
    struct Message **marray = calloc(k, sizeof(struct Message *));
    pthread_mutex_init(&mutex, NULL);

    int m, n, digit;
    unsigned long long num1 = 0, num2 = 0;

    scanf("%d", &m);
    for (int i = 0; i < m; i++){
        scanf("%d", &digit);
        num1 = num1 * 10 + digit;
    }
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%d", &digit);
        num2 = num2 * 10 + digit;
    }
    for (unsigned int i = 0; i < k; i++) {
        marray[i] = calloc(1, sizeof(struct Message));
        marray[i]->myid = i;
        marray[i]->numthreads = k;
        marray[i]->a = num1;
        marray[i]->b = num2;
        pthread_create(&thread[i], NULL, RussianMultiply, (void *)marray[i]);
    }
    void *exit_status;
    for (unsigned int i = 0; i < k; i++)
        pthread_join(thread[i], &exit_status);

    printf("Resultado final: %llu\n", result);

    for (unsigned int i = 0; i < k; i++)
        free(marray[i]);
    free(marray);
    free(thread);
    pthread_mutex_destroy(&mutex);
    return 0;
}
