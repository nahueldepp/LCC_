#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>



void* imprimir_mensaje(void* arg){
    printf("Hellow word\n");
    return NULL;
}
int main(void){

    pthread_t hilo;
    /*Se crea un hilo (subproceso) ligado al proceso padre*/
    pthread_create(&hilo, NULL,imprimir_mensaje, NULL);

    pthread_join(hilo, NULL);//con esto indicamos al hilo que va a ser esperado por el proceso principal junto con su valor de retorno
    //(si este es pedido)

    return 0;
}