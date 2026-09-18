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
#define N_MOLINETES 2
typedef struct {
    long cuentaMolinete;
    long visitantesMolinete;
    
}Molinete;


void* contar_visitantes(void* arg){

    Molinete* dato = (Molinete* ) arg;
    for(int i = 0; i < VISITANTES/2; i++){
        dato->cuentaMolinete++;//operación no atomica ->Se genera una race condition, se puede solucionar usando mutex
    }
    printf("Visitantes molinete: %ld\n", dato->cuentaMolinete);
    return NULL;
}

int main(void){

    pthread_t molinetes[N_MOLINETES];
    Molinete  datos[N_MOLINETES];

    long cuentaTotal = 0;
    long visitantesPorMolinete = VISITANTES / N_MOLINETES;
    long resto = VISITANTES % N_MOLINETES;

    for(unsigned i = 0; i < N_MOLINETES; i++){
        datos[i].cuentaMolinete =0;
        datos[i].visitantesMolinete = visitantesPorMolinete;
        if(i == N_MOLINETES-1){
            datos[i].visitantesMolinete += resto;
        } 
        int ret_val = pthread_create(molinetes+i,NULL,contar_visitantes,datos+i);
        if(ret_val){
            perror("pthread_create\n");
            exit(EXIT_FAILURE);
        }
    }

  
    printf("Joining main...\n");

    for(unsigned i = 0; i < N_MOLINETES; i++){

        int ret_val = pthread_join(molinetes[i],NULL);
        if(ret_val){
            perror("pthread_create\n");
            exit(EXIT_FAILURE);
        }
        cuentaTotal += datos[i].cuentaMolinete;
    }

    printf(">>Visitantes totales<< <%ld>\n",cuentaTotal);
    
    return EXIT_SUCCESS;
}