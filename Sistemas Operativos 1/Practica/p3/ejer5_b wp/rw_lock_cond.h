#ifndef __RW_LOCK__
#define __RW_LOCK__
#include <pthread.h>
#include <semaphore.h>

typedef struct Wr_lock{
    int numLectores;
    int EscritorAct;
    int numEscritoresEsp;
    //lock que cubre la cuenta de lectores
    pthread_mutex_t mutex;

    pthread_cond_t P_ESCRITURA, P_LECTURA;
}rw_lock;

void rw_lock_init(rw_lock* rwLock);

void rw_lock_destroy(rw_lock* rwLock);

void reader_wait(rw_lock* rwLock);

void reader_post(rw_lock* rwLock);

void write_wait(rw_lock* rwLock);

void write_post(rw_lock* rwLock);

#endif