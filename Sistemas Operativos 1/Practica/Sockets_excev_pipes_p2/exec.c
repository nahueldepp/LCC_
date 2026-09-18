#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
int main(void){

    pid_t pid= fork();

    if(pid == -1)
        exit(EXIT_FAILURE);
    
    if(pid==0){
        printf("Hola soy el hijo\n");
        printf("Hijo: PID=%d, PPID=%d\n",getpid(),getppid());
        execl("holamundo.o","holamundo.o", NULL);
        exit(0);
    }
    else{
        printf("Soy el padre, Mi pid es %d\n", getpid());
        printf("Mi hijo tiene pid %d\n", pid);
        wait(NULL); //si no se hace wait en el padre el hijo podria quedar zombie

    }
    return 0;
}