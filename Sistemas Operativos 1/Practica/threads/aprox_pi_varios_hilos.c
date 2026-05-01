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

/*
Calcula pi usando el metodo montecarlo dado una cantidad de puntos y threads
Al dividir los datos que ocupara cada thread, estas escribiran sus resultados en zonas distintas de memoria
por lo cual no usaran todas la misma sección crítica y no hara falta proteger la carga de cantidad de puntos*/
/*Esto lo hizo chatgpt ni en pedo lo hago yo solo xd*/

typedef struct {
    long cantDePuntos;//la cantidad de puntos que le toca a cada thread
    long cantDePuntosDentro;//por cada thread
    unsigned int seed; //semilla para generar datos aleatorios por cada thread
}DatosThread;

/*Conviene usar rand_r ya que cada hilo posee su propia semilla*/

double random_double(unsigned int *seed) {
    
    return (double) rand_r(seed) / RAND_MAX;
}

void* puntos_circ(void* arg){

    DatosThread* dato = (DatosThread*)arg;
    long npuntos = dato->cantDePuntos;
    unsigned puntosDentroAux = 0;
    double x ,y;
    for(unsigned i = 0; i < npuntos; i++){
        /*Definimos x,y entre -1 y 1*/
        //rand_r recibe la dirección de la semilla
        x = random_double(&dato->seed)*2.0 -1.0;
        y = random_double(&dato->seed)*2.0 -1.0;
        if(x*x + y*y <=1)
            puntosDentroAux++;

    }
    dato->cantDePuntosDentro = puntosDentroAux;

    return NULL;
}



int main(int argc, char* argv[]){

    if(argc != 3){
        printf("Uso: %s >Cantidad de puntos< >Cantidad de threads<\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    long cantidadTotalPuntos = atol(argv[1]);
    long cantidadTotalThreads = atol(argv[2]);

    pthread_t threads[cantidadTotalThreads];
    DatosThread datos[cantidadTotalThreads];

    long puntosPorthread= cantidadTotalPuntos / cantidadTotalThreads; //me devuelve un entero
    long resto = cantidadTotalPuntos % cantidadTotalThreads;

    for(long i=0; i < cantidadTotalThreads; i++){
        datos[i].cantDePuntos = puntosPorthread;
        datos[i].cantDePuntosDentro = 0;
        datos[i].seed = time(NULL)*i;
        if( i == cantidadTotalThreads-1){
            datos[i].cantDePuntos += resto;
        }
        int res_create = pthread_create(threads+i,NULL,puntos_circ,&datos[i]);
        if(res_create){
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    long totalDentro = 0;

    for(long i = 0; i< cantidadTotalThreads; i++){
        int ret_join = pthread_join(threads[i],NULL);
        if(ret_join){
            perror("join\n");
            exit(EXIT_FAILURE);
        }
        totalDentro += datos[i].cantDePuntosDentro;

    }

    double pi = (4.0*totalDentro)/cantidadTotalPuntos;
    printf("La aproximación de pi es: pi = [%lf]\n", pi);
    return EXIT_SUCCESS;
}