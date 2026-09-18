#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void){

    int i;
    int status;

    int fd[2];
    
    for(int i = 0; i<3 ; i++){
        pipe(fd);
        pid_t pid = fork();
        if(pid == 0){
            close(fd[0]);
            char buff[5] = "HOLA\n";
            int k = 0; 
            k = write(fd[1], &buff, 5); 

            if(k>0){
                printf("Soy el hijo %d y salude a mi padre %d\n", getpid(), getppid());
            }
            exit(0);
        }
        else{
            close(fd[1]);
            char buff2[5];
            int r = read(fd[0],buff2, 5);
            if(r>0){
                printf("Soy el padre %d, mi hijo %d me dijo %s\n", getpid(), pid, buff2);
            }
            wait(&status);
        }
    }
    return 0;
}