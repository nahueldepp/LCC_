
/*
el algoritmo de peterson falla porque asuimos consistenci secuencial , cada CPU tiene un cache  y en un algun momento difieren - no estan sincro entonces no son visibles al otro procesador

puede suceder que checkeo la cond del while, antes de que se asigne la misma pra q sea True

--barreras de memoria(ayuda a evitar lo anterior) mfence

-ALGORITMO DE LA PANADERIA: LAMPORT.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <omp.h>

#define MAX_HILOS 4              // Cantidad maxima de hilos
#define ITERACIONES 20   // Cantidad de veces que cada hilo entra a la región crítica

volatile int contador = 0;

volatile int choosing[MAX_HILOS] = {0};   // indica si un hilo está eligiendo número
volatile int number[MAX_HILOS] = {0};     // número asignado a cada hilo (su "ticket")

int main() {
    
    int id;
    #pragma omp parallel shared(contador, choosing, number) private(id)
    {

        id = omp_get_thread_num();
        int num_hilos = omp_get_num_threads();
        for (int i = 0; i < ITERACIONES; i++) {
            // Paso 1: elegir número
            choosing[id] = 1;
            int max = 0;
                for (int i = 0; i < num_hilos; i++) {
                    if (number[i] > max)
                    max = number[i];
                }
            
            number[id] = 1 + max;
            choosing[id] = 0;
    
        // Paso 2: esperar a que otros hilos terminen de elegir y que mi turno sea el más bajo
        for (int j = 0; j < num_hilos; j++) {
            if (j == id) continue;
            
            while (choosing[j]) ;  // Esperar a que el otro hilo elija su número
            while (number[j] != 0 &&
                (number[j] < number[id] || (number[j] == number[id] && j < id)))
                ;  // Esperar turno
            }
            
            // Región crítica
            contador++;
            printf("[%d] Hilo %d entra a la sección crítica\n", contador, id);
            usleep(10000);  // pequeña espera para que se note en la salida
            
            // Salir de la región crítica
            number[id] = 0;
        }
    }
    printf("Valor final del contador: %d\n", contador);

    return 0;
}