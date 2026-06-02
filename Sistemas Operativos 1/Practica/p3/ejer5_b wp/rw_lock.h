#ifndef __RW_LOCK__
#define __RW_LOCK__

#include <semaphore.h>

typedef struct Wr_lock{
    int numLectores;
    //lock que cubre la cuenta de lectores
    sem_t mutex;
    /*
    lock que cubre el buffer ya sea tomado por el primer lector o un escritor
    si bufferLibre es tomado por un lector, se esperara a que lean todos los lectores,
    luego el ultimo ector soltara el lock
    */
    sem_t bufferLibre;
   //semaforo para turnstile
    sem_t turnstile;
    
}rw_lock;

void rw_lock_init(rw_lock* rwLock);

void rw_lock_destroy(rw_lock* rwLock);

void reader_wait(rw_lock* rwLock);

void reader_post(rw_lock* rwLock);

void write_wait(rw_lock* rwLock);

void write_post(rw_lock* rwLock);

#endif