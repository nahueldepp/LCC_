#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define CLIENTES 50
#define ASIENTOS 20

pthread_mutex_t mutex;
unsigned numClientes=0; 
int BarberoOcupado=0;
pthread_cond_t HAY_CLIENTES;
pthread_cond_t SIGUIENTE;

sem_t esperandoCorte, esperandoPago;
void me_cortan(int i){
    printf("Soy el cliente %d, me estan cortando el pelo\n",i);
    sleep(random()%3);
    return;
}
void pagando(int i){
    printf("Soy el cliente %d.Estoy pagando...\n",i );
    sleep(random()%3);
    return;
}

void cortando(){

    printf("Cortando...\n");
    sleep(random()%3);
    return;
}
void me_pagan(){

    printf("Me estan pagando\n");
    sleep(random()%3);

}


void* atendido(void* arg){
    int i = arg - (void*)0;

        pthread_mutex_lock(&mutex);
        if(numClientes == ASIENTOS){
            printf("soy el cliente %d, Estaba todo ocupado, me fui\n", i);
            pthread_mutex_unlock(&mutex);
            return NULL;
        }
        numClientes++;
        while(BarberoOcupado)
            pthread_cond_wait(&SIGUIENTE, &mutex);
        pthread_cond_broadcast(&HAY_CLIENTES);
        
        numClientes--;
        pthread_mutex_unlock(&mutex);
        
        me_cortan(i);
        sem_wait(&esperandoCorte);
        pagando(i);
        sem_post(&esperandoPago);
  

}

void* atender(void* arg){

    while(1){

        pthread_mutex_lock(&mutex);
        while(numClientes == 0)
            pthread_cond_wait(&HAY_CLIENTES,&mutex);
        BarberoOcupado = 1;
        pthread_mutex_unlock(&mutex);
        
        cortando();
        sem_post(&esperandoCorte);
        sem_wait(&esperandoPago);
        me_pagan();
        BarberoOcupado = 0;
        pthread_cond_signal(&SIGUIENTE);
    }


}


int main(void){


    pthread_t cliente[CLIENTES];
    pthread_t barbero;

    pthread_mutex_init(&mutex,NULL);
    sem_init(&esperandoCorte,0, 1);
    sem_init(&esperandoPago,0, 1);
    pthread_create(&barbero, NULL,atender,NULL );

    for(int i = 0; i< CLIENTES; i++)
        pthread_create(&cliente[i], NULL, atendido, i + (void*)0);

    pthread_join(barbero,NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}