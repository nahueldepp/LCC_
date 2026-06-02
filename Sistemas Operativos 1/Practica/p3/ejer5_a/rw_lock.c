#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "rw_lock.h"

/*
Esta resolucion del problema se denomina Lightswitch, ya que el primer hilo lector que entre
toma el lock de la sección critica y el ultimo que sale lo suelta*/

void rw_lock_init(rw_lock* rwLock){

    rwLock->numLectores = 0;
    sem_init(&rwLock->mutex, 0, 1);
    sem_init(&rwLock->bufferLibre, 0, 1);

    return ;
}

void rw_lock_destroy(rw_lock* rwLock){
    sem_destroy(&(rwLock->bufferLibre));
    sem_destroy(&(rwLock->mutex));
    return;
}



void reader_wait(rw_lock* rwLock){

    sem_wait(&rwLock->mutex);
    //si numLectores es 0 cuando hacemos un wait, luego es el primer lector en entrar
    if(rwLock->numLectores == 0)
        sem_wait(&rwLock->bufferLibre);
    rwLock->numLectores++;
    sem_post(&rwLock->mutex);
    return;

}

void reader_post(rw_lock* rwLock){

    sem_wait(&rwLock->mutex);
    rwLock->numLectores--;
    if(rwLock->numLectores == 0)
        sem_post(&rwLock->bufferLibre);
    sem_post(&rwLock->mutex);

    return;
}


void write_wait(rw_lock* rwLock){

    sem_wait(&rwLock->bufferLibre);
    return;

}

void write_post(rw_lock* rwLock){

    sem_post(&rwLock->bufferLibre);
    return;
}