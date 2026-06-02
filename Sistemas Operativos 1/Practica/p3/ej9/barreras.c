#include "barreras.h"
#include <stdio.h>
void barrier_init(barrier_t* barrier, int n )
{
    barrier->numThreads = n;
    barrier->count = 0;
    sem_init(&barrier->mutex, 0, 1);
    sem_init(&barrier->turnstile,0, 0 );
    sem_init(&barrier->turnstile2, 0, 1);
    return;
}

void barrier_wait(barrier_t* barrier, int n){

    sem_wait(&barrier->mutex);
    barrier->count++;
    if(barrier->count == barrier->numThreads){
        sem_post(&barrier->turnstile);
        sem_wait(&barrier->turnstile2);
    }
    printf("p1-barrera[%d]count: %d\n",n, barrier->count);
    sem_post(&barrier->mutex);

    sem_wait(&barrier->turnstile);
    sem_post(&barrier->turnstile);
    
    sem_wait(&barrier->mutex);
    barrier->count--;
    if(barrier->count == 0){
        sem_wait(&barrier->turnstile);
        sem_post(&barrier->turnstile2);
    }
    sem_post(&barrier->mutex);
    sem_wait(&barrier->turnstile2);
    sem_post(&barrier->turnstile2);

    return;
}

void barrier_destroy(barrier_t* barrier){
    sem_destroy(&barrier->turnstile);
    sem_destroy(&barrier->mutex);
    return;
}

