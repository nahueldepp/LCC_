#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


int main(void){
    pid_t   pidPadre = getpid();
    pid_t   pid_1 = fork();
    pid_t   pid_2 = fork();
    
    if(pid_1 == -1 || pid_2== -1)
        exit(EXIT_FAILURE);

    if(pid_1 == 0 && pid_2 == 0){
        printf("Hola soy hijo del hijo 1, mi pid es: %d", getpid());
        printf("mi padre tiene pid: %d\n", getppid());
    }
    else if(pid_1== 0){
        printf("Hola soy el hijo 1, mi pid es: %d, el de mi hijo es: %d y el de mi padre: %d\n", getpid(), pid_2, getppid());
        wait(0);
    }
    else if(pid_2 == 0 ){
        printf("Hola soy el hijo 2, mi pid es: %d", getpid());
        printf("mi padre tiene pid: %d\n", getppid());
    }
    else{
        printf( "Hola soy el padre, mi pid es: %d y el de mis hijos: h1: %d h2:%d \n",pidPadre, pid_1, pid_2);
        sleep(5);
        wait(0);
    }
    
    return 0;
    
}
