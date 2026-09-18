#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
//#include <math.h>
#define N 500000000ULL


int minimo_secuencial(int* a,unsigned long long n)
{   
    unsigned long min = __INT_MAX__;
    for(unsigned long long i= 1; i < n; i++)
    {
        if(min > a[i]){
            min = a[i];
        }
    }
    return min;
}

int minimo_paralelo(int* a,unsigned long long n ,int num_threads)
{   
    unsigned long min = __INT_MAX__;
    #pragma omp parallel for num_threads(num_threads) reduction(min: min)
    for(unsigned long long i= 1; i < n; i++)
    {
        if(min > a[i]){
            min = a[i];
        }
    }
    return min;
}


int main(void)
{
    int* a = malloc(N*sizeof(int));
    if(a == NULL){
    fprintf(stderr, "Error: no se pudo reservar memoria\n");
    return 1;
    }
    printf("Inicializamos el array\n");

    #pragma omp parallel for
    for(unsigned long long i = 0; i<N; i++){
        a[i] = rand()%1000000 + 1;
    }
    a[N-1]= 0;


    double  inicio,
            fin,
            tiempo_secuencial,
            tiempo_paralelo ,
            speedup;

    int resultado;
    printf("Realizamos la busqueda secuencial...\n");

    inicio = omp_get_wtime();
    resultado = minimo_secuencial(a,N);
    fin = omp_get_wtime();
    tiempo_secuencial = fin-inicio;
    
    printf("tiempo = %.5f | minimo = %d\n",tiempo_secuencial, resultado );

    // Declaramos las threads a probar 
    int hilos[] = {1,2,4,8,16};
    int cant_pruebas = sizeof(hilos)/sizeof(hilos[0]);
    printf("Realizamos la busqueda paralela con reduction...\n");

    for(int i = 0; i<cant_pruebas ; i++){
        int t = hilos[i];
        inicio = omp_get_wtime();
        resultado = minimo_paralelo(a, N, t);
        fin = omp_get_wtime();
        
        tiempo_paralelo = fin-inicio;
        speedup = tiempo_secuencial / tiempo_paralelo;

        printf("hilos = %d | tiempo_paralelo = %.5fs | speedup = %.5fs | minimo = %d\n", 
            t, tiempo_paralelo, speedup, resultado);
    }

    free(a);
    return 0;

}