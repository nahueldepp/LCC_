
#include <pthread.h>  //POSIX. incluir en gcc -pthread / -lpthread (w/MACROS)
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t mutex_v1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_v2 = PTHREAD_MUTEX_INITIALIZER;
/*Aquie se dan las siguientes condeciones(condiciones de Coffman)*/
/*
Hay exclusión mutua
Hold and wait: un proceso se bloquea recursos y hace al otro esperar a que los libere
No preeemtion, funcion y funcion2 no liberan los recursos despues de usarlos
Hay espera circular, es decir que existe un ciclo donde cada uno de los proces espera a que termine el otro de liberar recursos
en este caso, si funcion llega primero funcion2 espera
Todo esto causa que si funcion bloquea mutex_vi y luego funcion2 bloquea a mutex_v2 (por ejemplo) al ambos no liberar niguno
causa que otro proceso quede esperando al la liberación del otro recurso en un ciclo eterno (deadlock)
La diferencia con un livelock aca es que ninguno de los thread ejecuta la región cretica*/
void* funcion(void *arg){
    pthread_mutex_lock(&mutex_v1);//1- pide a v1
    printf("T1 - M1\n");
    sleep(1);
    printf("T1 - M2\n");
    pthread_mutex_lock(&mutex_v2);//3-pide a v2, pero esta tomado por hilo2, asi q espera
    
    
    // -- region critica --
    
    printf("T1 \n");

    pthread_mutex_unlock(&mutex_v1);
    pthread_mutex_unlock(&mutex_v2);
}

void* funcion2(void* arg) {
    pthread_mutex_lock(&mutex_v2);//2-pide v2
    printf("T2 - M2\n");
    sleep(1);
    printf("T2 - M1\n");
    pthread_mutex_lock(&mutex_v1);//4-pide a v1, pero esta tomado por hilo1, asi q espera (deadlock)

    // -- region critica --

    printf("T2 \n");

    pthread_mutex_unlock(&mutex_v2);
    pthread_mutex_unlock(&mutex_v1);
}

int main(){
    pthread_t hilo1,hilo2;

    pthread_create(&hilo1,NULL,funcion,NULL);
    pthread_create(&hilo2, NULL, funcion2, NULL);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    return 0;
}