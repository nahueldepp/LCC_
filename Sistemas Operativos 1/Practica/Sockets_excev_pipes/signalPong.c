#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>

pid_t otro;
void signal_handler(int sig){
    kill(otro, SIGUSR1);
    printf("ping\n"); 
}
void signal_handler2(int sig){printf("pong\n");}

int main(void){

    pid_t pid;

    pid = fork();

    if(pid < 0){
        perror("fork");
        exit(0);
    }

    if(pid == 0){
        otro = getpid();
        signal(SIGUSR1, signal_handler);
        while(1){}
    }
    else{//estoy en el padre
        sleep(1);
        otro = pid;
        signal(otro,signal_handler);
        kill(pid, SIGUSR1); 

        while(1){pause();}
    }
}