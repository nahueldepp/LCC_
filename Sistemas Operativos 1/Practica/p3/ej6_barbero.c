#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>



#define CLIENTES 18
#define SILLAS 10


unsigned long clientesEsperando;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t clientes;
sem_t barberoLibre;
sem_t corteHecho;
sem_t pagoRealizado;

sem_t esperandoCorte, esperandoPago;


void me_cortan(int i){
    printf("Soy el cliente %d, me estan cortando el pelo\n",i);
    sleep(random()%3);
    return;
}
void pagando(int i){
    printf("Soy el cliente %d. Realizo pago\n",i );
    sleep(random()%3);
    return;
}

void cortando(){

    printf("Cortando...\n");
    sleep(random()%3);
    return;
}
void me_pagan(){

    printf("Barbero: Pago recibido\n");
    sleep(random()%3);

}

void* cliente(void* arg){

    int i = arg - (void*)0;

    pthread_mutex_lock(&mutex);
    if(clientesEsperando == SILLAS){
        printf("Cliente %d: Barberia llena, me voy\n", i);
        pthread_mutex_unlock(&mutex);
        return NULL;
    }
    clientesEsperando++;
    printf("Cliente %d: Me siento a esperar\n", i);
    //ahora hay clientes para atender, despierto al barbero
    
    pthread_mutex_unlock(&mutex);
    
    sem_post(&clientes);
    //lo espero
    sem_wait(&barberoLibre);
    pthread_mutex_lock(&mutex);
    clientesEsperando--;
    pthread_mutex_unlock(&mutex);

    //me siento en la silla del peluquero 
    sem_wait(&corteHecho);
    me_cortan(i);
    sem_post(&pagoRealizado);
    pagando(i);
    
    
    return NULL;

}

void* barbero(void* arg){

    while(1){
        
        sem_wait(&clientes);
 
        printf("Barbero: Atiendo un cliente\n");
        sem_post(&barberoLibre);
        
        
        cortando();
        sem_post(&corteHecho);
        sem_wait(&pagoRealizado);
        me_pagan();
        
        
    }

}

int main(void){

    pthread_t barbero_thread;
    pthread_t cliente_thread[CLIENTES];
    
    sem_init(&clientes, 0, 0);
    sem_init(&barberoLibre, 0, 0);
    sem_init(&corteHecho, 0, 0);
    sem_init(&pagoRealizado, 0, 0);

    pthread_create(&barbero_thread, NULL, barbero, (void*)0);
    for(int i = 0; i < CLIENTES; i++)
        pthread_create(&cliente_thread[i],NULL,cliente, i +(void*)0);

    sem_destroy(&clientes);
    sem_destroy(&barberoLibre);
    sem_destroy(&corteHecho);
    sem_destroy(&pagoRealizado);

    pthread_join(barbero_thread, NULL);
    
    return 0;
}