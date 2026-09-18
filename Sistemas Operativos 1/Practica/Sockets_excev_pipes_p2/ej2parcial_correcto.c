#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void){

    int i;
    int status;
    int fd[2];
    pipe(fd);
    
    for (i = 0; i < 3; i++) {
        pid_t pid = fork();
    
        if (pid == 0) {
            close(fd[0]);
            char buff[5] = "HOLA\n";
            int k = 0;
            k = write(fd[1], &buff, 5);
    
            if (k > 0)
                printf("Soy el hijo %d y salude a mi padre %d\n",
                       getpid(), getppid());
            exit(0);
        }
        else {
            char buff2[5];
            int r;
            r = read(fd[0], buff2, 5);
            
            if (r > 0)
            printf("Soy el padre %d, mi hijo %d me dijo %s",
                getpid(), pid, buff2);
                
                wait(&status);
            }
        }
    close(fd[1]);
}