#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 500000000ULL


//version secuencial
double suma_secuencial(double *a,unsigned long long n){
    double sum = 0.0;
    for(unsigned long long i=0; i<n; i++){
        sum += a[i];
    }
    return sum;
}

//version paralela usando parallel reduccion_var
double suma_paralela_reduction(double *a, unsigned long long n, int num_threads){
    double sum = 0.0;
    #pragma omp parallel for num_threads(num_threads) reduction(+: sum)
    for(unsigned long long i = 0; i< n; i++){
        sum += a[i];
    }
    return sum; 
    
}

//version paralela usando mutex
double suma_paralela_mutex(double *a, unsigned long long n, int num_threads){
    double sum = 0.0;
    #pragma omp parallel for num_threads(num_threads)
    for(unsigned long long i = 0; i< n; i++){
        #pragma omp critical
        {
            sum += a[i];
        }
    }
    return sum; 
    
}
int main(void){
    double *a = malloc(N * sizeof(double));

    if(a == NULL){
    fprintf(stderr, "Error: no se pudo reservar memoria\n");
    return 1;
    }

    printf("inicializando arreglo de  %llu doubles...\n",N);

    #pragma omp parallel for
    for (unsigned long long i = 0; i<N; i++){
        a[i] = 1.0;
    }

    printf("Inicialización terminada\n");

    double inicio,fin;
    double resultado;

    //versión secuencial
    inicio = omp_get_wtime();
    resultado = suma_secuencial(a, N);
    fin = omp_get_wtime();

    double tiempo_secuencial = fin-inicio;

    printf("Versión Secuencial\n");
    printf(" suma = %.2f \n", resultado);
    printf(" tiempo = %.5f s \n", tiempo_secuencial);

    //calculamos la cantidad de pruebas que vamos a hacer segun los hilos que queramos usar
    int hilos[] = {1, 2, 4, 8, 16};
    int can_pruebas = sizeof(hilos)/sizeof(hilos[0]);


    //Version paralela con reducción
    printf("Versión paralela con reduction\n");

    for(int i = 0; i< can_pruebas; i++){
        int t = hilos[i];
        inicio = omp_get_wtime();
        resultado = suma_paralela_reduction(a, N, t);
        fin = omp_get_wtime();

        double tiempo_paralelo= fin-inicio;
        double speedup= tiempo_secuencial/tiempo_paralelo;

        printf(" hilos = %d | tiempo_paralelo = %.5fs | speedup = %.5fs | suma= %.2f\n\n", 
        t, tiempo_paralelo,speedup, resultado);

    }

    printf("Versión paralela con mutex critical\n");

    for(int i = 0; i< can_pruebas; i++){
        int t = hilos[i];
        inicio = omp_get_wtime();
        resultado = suma_paralela_mutex(a, N, t);
        fin = omp_get_wtime();

        double tiempo_paralelo= fin-inicio;
        double speedup= tiempo_secuencial/tiempo_paralelo;

        printf(" hilos = %d | tiempo_paralelo = %.5fs | speedup = %.5fs | suma= %.2f\n\n", 
        t, tiempo_paralelo,speedup, resultado);

    }

    free(a);

    return 0;
}