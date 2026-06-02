#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#define N_FILOSOFOS 5
#define ESPERA 50000
pthread_mutex_t tenedor[N_FILOSOFOS];
sem_t tenedores; 

pthread_mutex_t *izq(int i) { return &tenedor[i]; }
pthread_mutex_t *der(int i) { return &tenedor[(i + 1) % N_FILOSOFOS]; }
void pensar(int i)
{
    printf("Filosofo %d pensando...\n", i);
    usleep(random() % ESPERA);
}
void comer(int i)
{
    printf("Filosofo %d comiendo...\n", i);
    usleep(random() % ESPERA);
}
void tomar_tenedores(int i)
{
    pthread_mutex_lock(der(i));
    pthread_mutex_lock(izq(i));
}
void dejar_tenedores(int i)
{
    pthread_mutex_unlock(der(i));
    pthread_mutex_unlock(izq(i));
}
void *filosofo(void *arg)
{
    int i = arg - (void *)0;
    while (1)
    {
        //tomar_tenedores(i);
        sem_wait(&tenedores);
        comer(i);
        //dejar_tenedores(i);
        sem_post(&tenedores);
        pensar(i);
    }
}
int main()
{
    pthread_t filo[N_FILOSOFOS];
    int i;
    if(sem_init(&tenedores,0, N_FILOSOFOS-1) != 0){
        perror("sem_init\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < N_FILOSOFOS; i++)
        pthread_mutex_init(&tenedor[i], NULL);
    for (i = 0; i < N_FILOSOFOS; i++)
        pthread_create(&filo[i], NULL, filosofo, i + (void *)0);
    pthread_join(filo[0], NULL);
    sem_destroy(&tenedores);
    return 0;
}
