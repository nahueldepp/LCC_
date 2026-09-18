#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#define N 500000000ULL


int esPrimo_secuencial(long n)
{   
    if (n < 2) return 1;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;

    long rootn = (long)sqrtl((long double)n);
    for(long i= 3;i <= rootn; i++)
    {
        if(n%i == 0)
            return 0;
    }
    return 1;
}

int esPrimo_paralelo(long n ,int num_threads)
{   
    if (n < 2) return 1;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
       /*
       Chequeo secuencial barato.

       Esto ayuda mucho porque si n tiene un divisor chico,
       la versión secuencial gana cortando rápido.
       Entonces evitamos lanzar OpenMP para casos fáciles.
    */
    long limite_chico = 1000;

    for(long i = 3; i<= limite_chico && i<= n/2; i++){
        if(n%i == 0)
            return 0;
    }

    long limite = (long)sqrtl((long double)n);

    if(limite <= limite_chico)
        return 1;
    
    int esPrimo = 1;    
     /*
       Arrancamos después de los divisores chicos ya probados.
       Como limite_chico = 1000, el siguiente impar es 1001.
    */


    #pragma omp parallel for num_threads(num_threads) reduction(&&:esPrimo)
    for(unsigned long long i= 2; i <= limite; i++)
    {
        esPrimo = esPrimo && (n%i==0);
    }
    
    return esPrimo;
}


int main(void)
{
    long numeros[] = {
        1000000000000000000L,          // par grande
        1000000007L,                   // primo
        2147483647L,                   // primo, 2^31 - 1
        2305843009213693951L,          // primo, 2^61 - 1
        1000000007L * 1000000009L,     // semiprimo grande
        1000000033L * 1000000087L      // semiprimo grande
    };


    double  inicio,
            fin,
            tiempo_secuencial,
            tiempo_paralelo ,
            speedup;

    int resultado;


    printf("Chequeamos primos de manera secuencial...\n");

    for(int i = 0 ; i< 10; i++){

        inicio = omp_get_wtime();
        resultado = esPrimo_secuencial(numeros[i]);
        fin = omp_get_wtime();
        tiempo_secuencial = fin-inicio;
        
        printf("numero= %2ld |tiempo = %.5f |  %s\n",
            numeros[i],tiempo_secuencial, resultado? "Es Primo":"No Es Primo" );
    }

    // Declaramos las threads a probar 
    int hilos[] = {1,2,4,8,16};
    int cant_pruebas = sizeof(hilos)/sizeof(hilos[0]);
    printf("Chequeamos primos de manera paralela...\n");

    for(int i = 0; i<cant_pruebas ; i++){
        int t = hilos[i];
        for(int j = 0; j< 10; j++){

            inicio = omp_get_wtime();
            resultado = esPrimo_paralelo(numeros[j], t);
            fin = omp_get_wtime();
            
            tiempo_paralelo = fin-inicio;
            speedup = tiempo_secuencial / tiempo_paralelo;
    
            printf("hilos = %d |numero= %2ld | tiempo_paralelo = %.5fs | speedup = %.5fs | %s\n", 
                t,numeros[j], tiempo_paralelo, speedup, resultado? "Es Primo":"No Es Primo");
        }
    }

    return 0;

}