#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h> 

int main(void){


    char* buffer[100];
    int fd[2];

    pipe(fd);

    pid_t pid = fork();

    if(pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(pid == 0){ //estoy en el hijo
        //el hijo recibe el mensaje
        close(fd[1]); //cerramos el extremo de escritura
        char buffer[100];

        int num_read = read(fd[0], buffer, sizeof(buffer));
        write(1, buffer, num_read);
        printf("%s", buffer);
        close(fd[0]);
        exit(0);
    }
    else{//padre
        //quiero mandar un mensaje al hijo y que este lo imprima
        close(fd[0]);//cerramos el extremo de lectura
        char* msg = "Hola mundo\n";
        write(fd[1],msg, strlen(msg)+1);
        close(fd[1]);
        wait(0);
    }
    return 0;
}