#ifndef __RW_LOCK__
#define __RW_LOCK__

#include <semaphore.h>

typedef struct Wr_lock{
    int numLectores;
    int escritorAct;
    unsigned long turno;
    unsigned long ticket;

    //lock que cubre la cuenta de lectores
    pthread_mutex_t mutex;

    pthread_cond_t SIGUIENTE;
}rw_lock;

void rw_lock_init(rw_lock* rwLock);

void rw_lock_destroy(rw_lock* rwLock);

void reader_wait(rw_lock* rwLock);

void reader_post(rw_lock* rwLock);

void write_wait(rw_lock* rwLock);

void write_post(rw_lock* rwLock);

void rw_post(rw_lock* rwLock);

#endif