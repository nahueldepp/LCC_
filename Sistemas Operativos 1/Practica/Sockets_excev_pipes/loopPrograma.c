#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main (int argc, char** argv){

    pid_t pid;
    while (1){
        pid= fork();

        if(pid==-1){
            perror("fork\n");
            exit(EXIT_FAILURE);
        }
        if(pid == 0){
            execl(argv[1], argv[1], NULL);
            exit(0);
        }
        else{
            printf("Padre...\n");
            //char* p= malloc(1024L*1024*1024);
            //sleep(10);
            wait(NULL);
        }
    }
}