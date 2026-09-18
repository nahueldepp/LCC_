#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <sys/un.h>
#include <time.h>
#include <pthread.h>


#define VISITANTES 100000

/*Versión sin race condition de el jardin ornamental. Poco optima*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int cuenta = 0;

void* contar_visitantes(void* arg){

    for(int i = 0; i < VISITANTES/2; i++){
        pthread_mutex_lock(&mutex);
        cuenta++;//operación no atomica ->Se genera una race condition, se puede solucionar usando mutex
        pthread_mutex_unlock(&mutex);
    }
    printf("Visitantes molinete: %d\n", cuenta);
    return NULL;
}

int main(void){

    pthread_t molinete1, molinete2;

    pthread_create(&molinete1,NULL, contar_visitantes, NULL);
    pthread_create(&molinete2,NULL, contar_visitantes, NULL);

    
    pthread_join(molinete1, NULL);
    pthread_join(molinete2, NULL);
    printf("Joining main...\n");

    printf(">>Visitantes totales<< <%d>\n",cuenta);
    pthread_mutex_destroy(&mutex);
    return EXIT_SUCCESS;
}