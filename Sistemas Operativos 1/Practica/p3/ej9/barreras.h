#ifndef __BARRERA_H__
#define __BARRERA_H__

#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>


typedef struct bar{
    int numThreads;
    int count;
    sem_t mutex;
    sem_t turnstile;
    sem_t turnstile2;
    
}barrier_t;

void barrier_init(barrier_t* barrier, int n );

void barrier_wait(barrier_t* barrier,int n);

void barrier_destroy(barrier_t* barrier);




#endif