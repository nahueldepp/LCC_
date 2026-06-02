#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define M 5
#define N 5
#define SZ 8

/*Problema de consumidor productor usando semaforos  */

sem_t ocupados, libres, mutex;

/*
 * El buffer guarda punteros a enteros, los
 * productores los consiguen con malloc() y los
 * consumidores los liberan con free()
 */
int *buffer[SZ];
int pos=0;
void enviar(int *p)
{
	sem_wait(&libres);
    
    sem_wait(&mutex);
    buffer[pos % SZ]= p;
    pos++;
    sem_post(&mutex);

    sem_post(&ocupados);
	return;
}

int * recibir()
{
    int* p;
	sem_wait(&ocupados);

    sem_wait(&mutex);
    pos--;
    p= buffer[pos % SZ];
    sem_post(&mutex);

    sem_post(&libres);

	return p;
}

void * prod_f(void *arg)
{
	int id = arg - (void*)0;
	while (1) {
		sleep(random() % 3);

		int *p = malloc(sizeof *p);
		*p = random() % 100;
		printf("Productor %d: produje %p->%d\n", id, p, *p);
		enviar(p);
	}
	return NULL;
}

void * cons_f(void *arg)
{
	int id = arg - (void*)0;
	while (1) {
		sleep(random() % 3);

		int *p = recibir();
		printf("Consumidor %d: obtuve %p->%d\n", id, p, *p);
		free(p);
	}
	return NULL;
}

int main()
{
    sem_init(&libres, 0, SZ);
    sem_init(&ocupados, 0, 0);
    sem_init(&mutex, 0, 1);
	pthread_t productores[M], consumidores[N];
	int i;


	for (i = 0; i < M; i++)
		pthread_create(&productores[i], NULL, prod_f, i + (void*)0);

	for (i = 0; i < N; i++)
		pthread_create(&consumidores[i], NULL, cons_f, i + (void*)0);

	pthread_join(productores[0], NULL); /* Espera para siempre */
    sem_destroy(&mutex);
    sem_destroy(&libres);
    sem_destroy(&ocupados);
	return 0;
}
