#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <sys/un.h>
#include <time.h>
#include <pthread.h>


#define RADIO 600
unsigned nPuntos = 10000;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
unsigned puntosDentro = 0;//variable que usaran los hilos


/*Dado una cantidad de puntos ,
devuelve el valor de pi calculado por el metodo montecarlo
Se asume un cuadrado con su centro en el (0,0) y se calcula la cantidad de puntos
, con lo cual queremos que x^2+y^2 <= 1*/
void* puntos_circ(void* arg){


    unsigned puntosDentroAux = 0;
    double x ,y;
    for(unsigned i = 0; i < nPuntos; i++){
        /*Definimos x,y entre -1 y 1*/
        x = ((double)rand() / RAND_MAX)*2.0 -1.0;
        y = ((double)rand() / RAND_MAX)*2.0 -1.0;
        if(x*x + y*y <=1)
            puntosDentroAux++;

    }

    pthread_mutex_lock(&mutex);//bloqueamos la operación
    puntosDentro += puntosDentroAux;//sumamos los puntos dentro calculados por el hilo
    pthread_mutex_unlock(&mutex); //desbloqueamos la operación

    return NULL;
}


int main(void){
    
    srand(time(NULL));
    pthread_t hilo1;
    int res_create = pthread_create(&hilo1, NULL, puntos_circ, NULL);
    if(res_create){
        perror("hilo1");
        exit(EXIT_FAILURE);
    }

    printf("MAIN JOINING...\n");
    int res_join = pthread_join(hilo1, NULL);
    if(res_join){
        perror("join");
        exit(EXIT_FAILURE);
    }

    double aprox_pi = (4 * puntosDentro)/(double) nPuntos;
    printf("puntos dentro: %d\n", puntosDentro);
    printf("El valor de pi aproximado es : >%lf<\n",aprox_pi);

    pthread_mutex_destroy(&mutex);
    return 0;
}