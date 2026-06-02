#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "rw_lock_cond.h"

#define M 50
#define N 50
#define ARRLEN 10240

rw_lock rwMutex;
int arr[ARRLEN];

void * escritor(void *arg)
{
	int i;
	int num = arg - (void*)0;
	while (1) {
		sleep(random() % 3);
		write_wait(&rwMutex);
		printf("Escritor %d escribiendo\n", num);
		for (i = 0; i < ARRLEN; i++)
			arr[i] = num;
		write_post(&rwMutex);	
	}
	return NULL;
}

void * lector(void *arg)
{
	int v, i;
	int num = arg - (void*)0;
	while (1) {

		sleep(random() % 3);
		reader_wait(&rwMutex);
		v = arr[0];
		for (i = 1; i < ARRLEN; i++) {
			if (arr[i] != v)
				break;
		}
		if (i < ARRLEN)
		printf("Lector %d, error de lectura\n", num);
		else
		printf("Lector %d, dato %d\n", num, v);
		reader_post(&rwMutex);
		
	}
	return NULL;
}

int main()
{
	pthread_t lectores[M], escritores[N];
	int i;
	rw_lock_init(&rwMutex);
	for (i = 0; i < M; i++)
		pthread_create(&lectores[i], NULL, lector, i + (void*)0);

	for (i = 0; i < N; i++)
		pthread_create(&escritores[i], NULL, escritor, i + (void*)0);

	pthread_join(lectores[0], NULL); /* Espera para siempre */
	return 0;
}
