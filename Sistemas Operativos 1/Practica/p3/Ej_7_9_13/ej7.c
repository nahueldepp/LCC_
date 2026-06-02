/*

a)
un deadlock puede ocurrir si el agente libera dos recursos y uno de los fumadores (hilos) toma uno de los recursos liberados y otro toma el segundo.
ya que hay 3 fumadores los cuales necesitan 2 recursos de 3 se puede afirmar que habra dos hilos que esten esperando a ambos 2 recursos liberados por agente
un ejemplo de esto seria que el agente libere tabaco y fosforos y que el fumador1 tome el tabaco y fumador2 tome fosforos, impidiendo el progreso del programa

b)
no, no hay orden posible donde se evite el problema del item anterior.
esto se debe a que sin importar el orden de liberacion, siempre existira la posibilidad que dos procesos tomen uno de los liberados.

*/

// c)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int buffer[3] = {0};

sem_t tabaco, papel, fosforos, otra_vez;
sem_t f1, f2, f3;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void agente(){
	while (1){
		sem_wait(&otra_vez);
		int caso = random() % 3;
		if (caso != 0) sem_post(&fosforos);
		if (caso != 1) sem_post(&papel);
		if (caso != 2) sem_post(&tabaco);
	}
}

void fumar(int fumador){
	printf("Fumador %d: Puf! Puf! Puf!\n", fumador);
	sleep(1);
}

void* inter_tabaco(){
	while (1){
		sem_wait(&tabaco);
		pthread_mutex_lock(&m);
		buffer[0] = 1;
		if (buffer[1]) {sem_post(&f1); buffer[1] = 0; buffer[0] = 0;}
		if (buffer[2]) {sem_post(&f2); buffer[2] = 0; buffer[0] = 0;}
		pthread_mutex_unlock(&m);
	}
}


void* inter_papel(){
	while (1){
		sem_wait(&papel);
		pthread_mutex_lock(&m);
		buffer[1] = 1;
		if (buffer[0]) {sem_post(&f1); buffer[0] = 0; buffer[1] = 0;}
		if (buffer[2]) {sem_post(&f3); buffer[2] = 0; buffer[1] = 0;}
		pthread_mutex_unlock(&m);
	}
}

void* inter_fosforos(){
	while (1){
		sem_wait(&fosforos);
		pthread_mutex_lock(&m);
		buffer[2] = 1;
		if (buffer[1]) {sem_post(&f3); buffer[1] = 0; buffer[2] = 0;}
		if (buffer[0]) {sem_post(&f2); buffer[0] = 0; buffer[2] = 0;}
		pthread_mutex_unlock(&m);
	}
}

void* fumador1(){
	while(1){
		sem_wait(&f1);
		fumar(1);
		sem_post(&otra_vez);
	}
}

void* fumador2(){
	while(1){
		sem_wait(&f2);
		fumar(2);
		sem_post(&otra_vez);
	}
}

void* fumador3(){
	while(1){
		sem_wait(&f3);
		fumar(3);
		sem_post(&otra_vez);
	}
}

int main(){
	pthread_t fum1, fum2, fum3, inter1, inter2, inter3, inter;
	sem_init(&tabaco, 0, 0);
	sem_init(&papel, 0, 0);
	sem_init(&fosforos, 0, 0);
	sem_init(&otra_vez, 0, 1);
	
	sem_init(&f1, 0, 0);
	sem_init(&f2, 0, 0);
	sem_init(&f3, 0, 0);

	pthread_create(&inter1, NULL, inter_tabaco, NULL);
	pthread_create(&inter2, NULL, inter_papel, NULL);
	pthread_create(&inter3, NULL, inter_fosforos, NULL);
	
	pthread_create(&fum1, NULL, fumador1, NULL);
	pthread_create(&fum2, NULL, fumador2, NULL);
	pthread_create(&fum3, NULL, fumador3, NULL);

	agente();
}




