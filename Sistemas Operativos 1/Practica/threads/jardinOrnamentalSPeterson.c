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
#define visitantes_moli 40

int contador = 0;
int flag[2] = {0, 0};  // 0 -> sin intencion de entrar a RC, 1 -> con intencion
int turno = 0;  // 0: te toca ir.

void* molinete(void* proceso) {
    for (int x = 0; x < visitantes_moli / 2; ++x) {

        // LOCK
        flag[0] = 1;
        turno=2;            // molinete 1 intención de entrar a RC
        while (flag[1] == 1 && turno==2) {  // prioridad=otro :)
            ;                   // PAUSA.
        }

        contador++;  // -> region critica.

        // UNLOCK
        flag[0] = 0;  // ya terminé

        printf("[%d] m1 - Ha ingresado otro más (%p) \n", contador, proceso);
    }

    // return NULL;
}

void* molinete2(void* proceso) {
    for (int x = 0; x < visitantes_moli / 2; ++x) {
        // int otro = 1 - proceso;

        // LOCK
        flag[1] = 1;
        turno = 1;
        while (flag[0] == 1 && turno==1) {  // prioridad=otro :)
            ;                   // PAUSA.
        }

        contador++;  // -> region critica.

        // UNLOCK
        flag[1] = 0;

        printf("[%d] m2 - Ha ingresado otro más (%p) \n", contador, proceso);
    }
}

int main() {
    pthread_t moli_1, moli_2;

    pthread_create(&moli_1, NULL, molinete, NULL);
    pthread_create(&moli_2, NULL, molinete2, NULL);

    pthread_join(moli_1, NULL);
    pthread_join(moli_2, NULL);

    printf("[VISITANTES TOTAL] %d \t", contador);

    return 0;
}


//AUNSENCIA DE INANICION: quiero tomar un lock, eventualmene lo hago (no soy block simpre) ==> ausencia de deadlock  (pero al revés NO).