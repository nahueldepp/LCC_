
#include <stdlib.h>
#include <unistd.h>
#include "rw_lock_cond.h" 

/*
Solución al problema de starvation de los escritores en el metodo anterior.
Aqui usando variables condicionales nos encargamos de darle prioridad a los escritores.
Esto puede ocacionar starvation de los lectores */

void rw_lock_init(rw_lock* rwLock){
    rwLock->numLectores = 0;
    rwLock->EscritorAct=0;
    rwLock->numEscritoresEsp=0;
    pthread_mutex_init(&rwLock->mutex, NULL);

    return ;
}

void rw_lock_destroy(rw_lock* rwLock){
    pthread_mutex_destroy(&rwLock->mutex);
    return;
}



void reader_wait(rw_lock* rwLock){

    pthread_mutex_lock(&rwLock->mutex);

    while( rwLock->EscritorAct || rwLock->numEscritoresEsp>0){
        pthread_cond_wait(&rwLock->P_LECTURA, &rwLock->mutex);
    }
    rwLock->numLectores++;
    pthread_mutex_unlock(&rwLock->mutex);
    return;

}

void reader_post(rw_lock* rwLock){

    pthread_mutex_lock(&rwLock->mutex);
    if(rwLock->numEscritoresEsp)
        pthread_cond_signal(&rwLock->P_ESCRITURA);
    rwLock->numLectores--;
    pthread_mutex_unlock(&rwLock->mutex);
    return;
}


void write_wait(rw_lock* rwLock){

    pthread_mutex_lock(&rwLock->mutex);
    rwLock->numEscritoresEsp++;
    while(rwLock->EscritorAct || rwLock->numLectores>0){
        pthread_cond_wait(&rwLock->P_ESCRITURA, &rwLock->mutex);
    }
    rwLock->EscritorAct = 1;   
    rwLock->numEscritoresEsp--;
    pthread_mutex_unlock(&rwLock->mutex);
    return;

}

void write_post(rw_lock* rwLock){
    
    pthread_mutex_lock(&rwLock->mutex);
    rwLock->EscritorAct = 0;
    rwLock->numEscritoresEsp--;
    if(rwLock->numEscritoresEsp != 0)
    //si hay hilos queriendo escribir, despierto solo uno
        pthread_cond_signal(&rwLock->P_ESCRITURA);
    else
        //si hay hilos queriendo leer permito la lectura
        pthread_cond_broadcast(&rwLock->P_LECTURA);
        

   
    pthread_mutex_unlock(&rwLock->mutex);
    return;
}