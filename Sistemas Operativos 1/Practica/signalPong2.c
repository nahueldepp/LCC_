#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

volatile sig_atomic_t otro;

void S_handler(int sig){
    printf("Ping\n");
    kill(otro, SIGUSR1); 
}

int main(void){

    struct sigaction act;
    pid_t pid;
    act.sa_handler = S_handler;
    act.sa_flags= 0;
    pid = fork();
    
    if(pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(pid == 0){
        otro = getpgid(pid);
        sigaction(SIGUSR1, &act, NULL);

    }
    else{
        kill(pid, SIGUSR1);
        sleep(1);
        otro = pid;
        sigaction(SIGUSR1,&act,NULL);
        wait(NULL);
    }
    return 0; 


}