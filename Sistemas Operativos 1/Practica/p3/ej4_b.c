#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define M 5
#define N 5
#define SZ 8


/*Problema consumidor-productor usando variables de condición */

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t LUGAR_LIBRE = PTHREAD_COND_INITIALIZER;
pthread_cond_t ELEMENTO_DISPONIBLE = PTHREAD_COND_INITIALIZER;
/*
* El buffer guarda punteros a enteros, los
* productores los consiguen con malloc() y los
* consumidores los liberan con free()
*/
int *buffer[SZ];
int pos=0;
int numElem = 0;

/*Retorna  1 si el buffer esta lleno, 0 en caso contrario*/
int isFull(){
    return numElem == SZ; 
}

/*Retoena 1 si el buffer esta vacio, 0 si no lo esta*/
int isEmpty(){
    return numElem == 0;
}

void enviar(int *p)
{
    pthread_mutex_lock(&mutex);
    while(isFull()){
        pthread_cond_wait(&LUGAR_LIBRE, &mutex);
    }
    buffer[pos % SZ] = p;
    pos++;
    numElem++;
    pthread_cond_signal(&ELEMENTO_DISPONIBLE);
    pthread_mutex_unlock(&mutex);
	
	return;
}

int * recibir()
{
	int* p;
    pthread_mutex_lock(&mutex);
    
    while(isEmpty()){
        pthread_cond_wait(&ELEMENTO_DISPONIBLE, &mutex);
    }
    pos--;
    p = buffer[pos % SZ];
    numElem--;
    pthread_cond_signal(&LUGAR_LIBRE);
    pthread_mutex_unlock(&mutex);

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
	pthread_t productores[M], consumidores[N];
	int i;
	for (i = 0; i < M; i++)
		pthread_create(&productores[i], NULL, prod_f, i + (void*)0);

	for (i = 0; i < N; i++)
		pthread_create(&consumidores[i], NULL, cons_f, i + (void*)0);

	pthread_join(productores[0], NULL); /* Espera para siempre */
	return 0;
}
