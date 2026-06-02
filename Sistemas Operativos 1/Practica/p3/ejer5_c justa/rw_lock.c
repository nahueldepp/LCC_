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
    rwLock->ticket = 0;
    rwLock->escritorAct = 0;
    rwLock->turno = 0;
    pthread_mutex_init(&rwLock->mutex, NULL);

    return ;
}

void rw_lock_destroy(rw_lock* rwLock){
    pthread_mutex_destroy(&rwLock->mutex);
    return;
}



void reader_wait(rw_lock* rwLock){

    pthread_mutex_lock(&rwLock->mutex);
    unsigned long miTicket = rwLock->ticket++;

    while(rwLock->escritorAct || miTicket != rwLock->turno){
        pthread_cond_wait(&rwLock->SIGUIENTE, &rwLock->mutex);
    }

    rwLock->numLectores++;
    rwLock->turno++;
    
    
    pthread_mutex_unlock(&rwLock->mutex);
    return;

}

void reader_post(rw_lock* rwLock){


    return;
}


void write_wait(rw_lock* rwLock){

    pthread_mutex_lock(&rwLock->mutex);

    unsigned long miTicket = rwLock->ticket++;
    while(rwLock->escritorAct || miTicket != rwLock->turno || rwLock->numLectores >0){
        pthread_cond_wait(&rwLock->SIGUIENTE, &rwLock->mutex);
    }

    rwLock->escritorAct = 1;
    rwLock->turno++;
  
    pthread_mutex_unlock(&rwLock->mutex);
    return;

}

void write_post(rw_lock* rwLock){

    return;
}

void rw_post(rw_lock* rwLock){

    pthread_mutex_lock(&rwLock->mutex);

    if(rwLock->escritorAct)
        rwLock->escritorAct = 0;
    else
        rwLock->numLectores--;

    pthread_cond_broadcast(&rwLock->SIGUIENTE);
    
    pthread_mutex_unlock(&rwLock->mutex);

}