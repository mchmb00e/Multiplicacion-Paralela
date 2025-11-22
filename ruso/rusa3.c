#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <time.h>
#include <ctype.h>

#define SILENT  0
#define VERBOSE 1

struct Message{
   unsigned int myid, numthreads, start, end;
};

struct BigInt{
   int *digits;
   int size;
};

struct BigInt *terms; 
struct BigInt global_sum; 
unsigned int terms_count;
pthread_mutex_t lock;

void InitBigInt(struct BigInt *n, int size){
   n->digits = calloc(size, sizeof(int));
   n->size = size;
}

void CopyBigInt(struct BigInt *dest, struct BigInt *src){
   unsigned int i;
   dest->size = src->size;
   dest->digits = calloc(dest->size, sizeof(int));
   for (i = 0; i < src->size; i = i + 1)
      dest->digits[i] = src->digits[i];
}

int cero(struct BigInt *n){
   unsigned int i;
   for (i = 0; i < n->size; i = i + 1)
      if (n->digits[i] != 0)
         return 0;
   return 1;
}


int impar(struct BigInt *n){
   if (n->size == 0) return 0;
   return (n->digits[n->size - 1] % 2 != 0);
}

void Div2(struct BigInt *n){
   int i, residuo, temp_digit;
   residuo = 0;
   for (i = 0; i < n->size; i = i + 1){
      temp_digit = n->digits[i] + residuo * 10;
      n->digits[i] = temp_digit / 2;
      residuo = temp_digit % 2;
   }
}

void Mul2(struct BigInt *n){
   int i, carry, temp_digit;
   int *new_digits;
   carry = 0;
   for (i = n->size - 1; i >= 0; i = i - 1){
      temp_digit = n->digits[i] * 2 + carry;
      n->digits[i] = temp_digit % 10;
      carry = temp_digit / 10;
   }
   if (carry > 0){
      new_digits = calloc(n->size + 1, sizeof(int));
      new_digits[0] = carry;
      for (i = 0; i < n->size; i = i + 1)
         new_digits[i + 1] = n->digits[i];
      free(n->digits);
      n->digits = new_digits;
      n->size = n->size + 1;
   }
}

void AddBigInts(struct BigInt *res, struct BigInt *a, struct BigInt *b){
   int i, j, k, sum, carry;
   int *temp_res;
   int max_size;
   if (a->size > b->size) max_size = a->size; else max_size = b->size;
   max_size = max_size + 1; 
   temp_res = calloc(max_size, sizeof(int));
   carry = 0;
   i = a->size - 1;
   j = b->size - 1;
   k = max_size - 1;
   
   while (i >= 0 || j >= 0 || carry > 0){
      sum = carry;
      if (i >= 0){ sum = sum + a->digits[i]; i = i - 1; }
      if (j >= 0){ sum = sum + b->digits[j]; j = j - 1; }
      
      temp_res[k] = sum % 10;
      carry = sum / 10;
      k = k - 1;
   }

   if (res->digits != NULL) free(res->digits);
   
   res->size = max_size - (k + 1);
   res->digits = calloc(res->size, sizeof(int));
   for (i = 0; i < res->size; i = i + 1)
      res->digits[i] = temp_res[k + 1 + i];
      
   free(temp_res);
}

void PrintBigInt(struct BigInt *n){
   unsigned int i;
   for (i = 0; i < n->size; i = i + 1)
      printf("%d", n->digits[i]);
   printf("\n");
}

void *PartialSum(void *arg){
   struct BigInt local_sum;
   struct Message *m;
   unsigned int i;
   m = (struct Message *) arg;
   local_sum.size = 1;
   local_sum.digits = calloc(1, sizeof(int)); 
   for (i = m->start; i <= m->end; i = i + 1){
      struct BigInt temp_sum;
      temp_sum.digits = NULL; 
      AddBigInts(&temp_sum, &local_sum, &terms[i]);
      free(local_sum.digits);
      local_sum = temp_sum;
   }
   
   pthread_mutex_lock(&lock);
   struct BigInt new_global;
   new_global.digits = NULL;
   AddBigInts(&new_global, &global_sum, &local_sum);
   free(global_sum.digits);
   global_sum = new_global;
   pthread_mutex_unlock(&lock);
   
   free(local_sum.digits);
   pthread_exit(0);
}

void Usage(char *argv[]){
   printf("Usage: %s k -M -O < data.txt\n", argv[0]);
   printf("  k: Number of threads\n");
   printf("  M: Method (-T Traditional, -R Russian)\n");
   printf("  O: Output Mode (-V Verbose, -S Silent)\n");
   exit(1);
}

int main(int argc, char **argv){
   pthread_t *thread;
   pthread_attr_t attribute;
   struct Message **mess;
   void *exit_status;
   unsigned int i, k, m_digits, n_digits, s, rem, l;
   int out_mode;
   char method_char, mode_char;
   struct BigInt A, B;
   float E_cpu;
   long E_wall;
   time_t  ts, te;
   clock_t cs, ce;
   
   if (argc != 4)
      Usage(argv);
   else{
      k = atoi(argv[1]);

      if (argv[2][0] == '-') method_char = toupper(argv[2][1]);
      else method_char = toupper(argv[2][0]);

      if (argv[3][0] == '-') mode_char = toupper(argv[3][1]);
      else mode_char = toupper(argv[3][0]);

      if (mode_char == 'V') out_mode = VERBOSE;
      else out_mode = SILENT;

      scanf("%d", &m_digits);
      InitBigInt(&A, m_digits);
      for (i = 0; i < m_digits; i = i + 1)
         scanf("%d", &A.digits[i]);
         
      scanf("%d", &n_digits);
      InitBigInt(&B, n_digits);
      for (i = 0; i < n_digits; i = i + 1)
         scanf("%d", &B.digits[i]);

      if (method_char == 'T'){
         return 0;
      }

      if (method_char == 'R'){
         if (out_mode == VERBOSE){
             printf("---------- ENTRADA ----------\n");
             printf("n: "); PrintBigInt(&A);
             printf("m: "); PrintBigInt(&B);
         }
         
         ts = time(NULL);
         cs = clock();

         terms = calloc(1000, sizeof(struct BigInt)); 
         terms_count = 0;

         while (!cero(&A)){
            if (impar(&A)){
               CopyBigInt(&terms[terms_count], &B);
               terms_count = terms_count + 1;
            }
            Div2(&A);
            Mul2(&B);
         }
         
         global_sum.size = 1;
         global_sum.digits = calloc(1, sizeof(int));
         
         pthread_mutex_init(&lock, NULL);
         pthread_attr_init(&attribute);
         pthread_attr_setdetachstate(&attribute, PTHREAD_CREATE_JOINABLE);
         
         thread = calloc(k, sizeof(pthread_t));
         mess = calloc(k, sizeof(struct Message *));
         for (i = 0; i < k; i = i + 1)
            mess[i] = calloc(1, sizeof(struct Message));

         s = terms_count / k;
         rem = terms_count % k;
         l = 0;
         
         for (i = 0; i < k; i = i + 1){
            mess[i]->myid = i;
            mess[i]->numthreads = k;
            
            if (rem != 0){
               mess[i]->start = l;
               mess[i]->end = l + s;
               l = l + s + 1;
               rem = rem - 1;
            }
            else{
               mess[i]->start = l;
               mess[i]->end = l + s - 1;
               l = l + s;
            }
            
            if (mess[i]->start <= mess[i]->end && mess[i]->start < terms_count)
               pthread_create(&thread[i], &attribute, PartialSum, (void *) mess[i]);
         }
         
         for (i = 0; i < k; i = i + 1){
             if (mess[i]->start <= mess[i]->end && mess[i]->start < terms_count)
               pthread_join(thread[i], &exit_status);
         }

         ce = clock();
         te = time(NULL);
         E_wall = (long) (te - ts);
         E_cpu = (float)(ce - cs) / CLOCKS_PER_SEC;

         if (out_mode == VERBOSE){
            printf("---------- RESULTADO ----------\n");
            PrintBigInt(&global_sum);
            printf("CPU Time %f | Wall Time %ld\n", E_cpu, E_wall);
         }
         else{
            printf("m digitos: %d n digitos: %d\n", m_digits, n_digits);
            printf("Elapsed CPU Time %f | Wall Time %ld\n", E_cpu, E_wall);
         }

         pthread_mutex_destroy(&lock);
         pthread_attr_destroy(&attribute);
      }
   }
   return 0;
}