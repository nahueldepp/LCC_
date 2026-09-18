#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define TAM_MEMORIA 1024

int main() {
    key_t clave = ftok("shmfile", 65); // Clave única
    int shmid = shmget(clave, TAM_MEMORIA, 0666 | IPC_CREAT); // Crear segmento de memoria

    if (shmid < 0) {
        perror("Error al crear memoria compartida");
        exit(1);
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Proceso hijo
        sleep(1); // Espera a que el padre escriba
        char *datos_hijo = (char *) shmat(shmid, NULL, 0);
        printf("[Hijo] Leí de la memoria: %s\n", datos_hijo);
        shmdt(datos_hijo); // Desvincular
    } else {
        // Proceso padre
        char *datos_padre = (char *) shmat(shmid, NULL, 0);
        strcpy(datos_padre, "Hola desde el padre usando memoria compartida.");
        printf("[Padre] Escribí en la memoria compartida.\n");
        shmdt(datos_padre); // Desvincular

        wait(NULL); // Esperar al hijo

        // Eliminar la memoria compartida
        shmctl(shmid, IPC_RMID, NULL);
        printf("[Padre] Memoria compartida eliminada.\n");
    }

    return 0;
}