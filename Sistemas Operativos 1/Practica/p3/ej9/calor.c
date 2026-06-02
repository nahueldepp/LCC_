#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "barreras.h"

#define N 20 
#define W 3
#define ITERS 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
barrier_t barrera1;
barrier_t barrera2;

float arr1[N], arr2[N];
void calor(float *arr, int lo, int hi, float *arr2)
{
    int i;
    for (i = lo; i < hi; i++)
    {
        int m = arr[i];
        int l = i > 0 ? arr[i - 1] : m;
        int r = i < N - 1 ? arr[i + 1] : m;
        arr2[i] = m + (l - m) / 1000.0 + (r - m) / 1000.0;
    }
}
void imprimir_arr(void){

    printf("Arr 1: \n");
    for(int i = 0; i< N; i++){
        printf("[%.2f]", arr1[i]);
    }
    printf("\nArr 2: \n");
    for(int i = 0; i< N; i++){
        printf("[%.2f]", arr2[i]);
    }
    printf("\n");
}
/* Dado un array de [n], devuelve el punto de corte [i] de los [m] totales. */
static inline int cut(int n, int i, int m)
{
    return i * (n / m) + (int)fmin(i, n % m);
}

void *thr(void *arg)
{
    int id = arg - (void *)0; /* 0 <= id < W */
    int lo = cut(N, id, W), hi = cut(N, id + 1, W);
    int i;
    for (i = 0; i < ITERS; i++)
    {
        calor(arr1, lo, hi, arr2);
        barrier_wait(&barrera1,1);
        calor(arr2, lo, hi, arr1);
        barrier_wait(&barrera1,2); 
    }
}

int main()
{
    
    pthread_t hilos[W];
    barrier_init(&barrera1,W);
    barrier_init(&barrera2,W);
    
    for(int i= 0; i < N; i++)
        arr1[i] = i;
    imprimir_arr();
    for(int i = 0; i < W; i++)
        pthread_create(&hilos[i], NULL, thr, i+(void*)0);
    for(int i = 0; i < W; i++)
        pthread_join(hilos[i],NULL);
        
    imprimir_arr();
    
    
    barrier_destroy(&barrera1);
    barrier_destroy(&barrera2);
    return 0;
}