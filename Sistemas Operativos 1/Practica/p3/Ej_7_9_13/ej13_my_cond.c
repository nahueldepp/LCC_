#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct _my_cond_t {
    sem_t sem;
    pthread_mutex_t m;
    int count_wait;
} my_cond_t;

void my_cond_init(my_cond_t *cond) {
    sem_init(&(cond->sem), 0, 0);
    pthread_mutex_init(&(cond->m), NULL);
    cond->count_wait = 0;
}

void my_cond_wait(my_cond_t *cond, pthread_mutex_t *mutex) {
    pthread_mutex_lock(&(cond->m));
    cond->count_wait = cond->count_wait + 1;
    pthread_mutex_unlock(&(cond->m));
    pthread_mutex_unlock(mutex);
    sem_wait(&(cond->sem));
    pthread_mutex_lock(mutex);
}

void my_cond_signal(my_cond_t *cond) {
    pthread_mutex_lock(&(cond->m));
    if (cond->count_wait > 0){ 
        sem_post(&(cond->sem));
        cond->count_wait = cond->count_wait - 1;
    }
    pthread_mutex_unlock(&(cond->m));
}

void my_cond_broadcast(my_cond_t *cond){
    pthread_mutex_lock(&(cond->m));
    for (int i = 1; i <= cond->count_wait; i++)
        sem_post(&(cond->sem));
    cond->count_wait = 0;
    pthread_mutex_unlock(&(cond->m));
}

void my_cond_destroy(my_cond_t *cond) {
    pthread_mutex_destroy(&(cond->m));
    sem_destroy(&(cond->sem));
}

/*
la implementacion prevista por la catedra presenta multiples problemas:

    - El primer inconveniente que presenta esta relacionado con la funcion signal.
    En una implementacion correcta de variables de condicion, una llamada a la funcion signal cuando no hay ningun hilo bloqueado por wait no tiene efecto alguno.
    Sin embargo, en esta implementacion, al llamar a signal cuando no hay hilo bloqueado, se le aplica un post al semaforo correspondiente.
    Esto causara un problema grave: El proximo hilo que intente hacer wait no quedara bloqueado porque el semaforo no estara en cero.

    - El segundo problema es de falta de atomicidad en la funcion wait.
    Dado que antes de llamar a sem_wait la funcion desbloquea el mutex, podria pasar que antes de llamar a sem_wait, otro hilo tome el mutex.
    Esto es algo que no deberia pasar en una implementacion correcta, ya que el objetivo es ceder el mutex al proximo hilo.

    - El tercer problema es la falta e imposibilidad de implementacion de broadcast.
    Dado que con la implementacion prevista no tenemos conteo alguno sobre cuantos hilos estan bloqueados por wait, es imposible saber cuantos hilos debemos despertar.
*/