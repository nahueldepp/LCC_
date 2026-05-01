#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <sys/un.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>


/*seek_wrire:: void* -> void* 
escribe el valor v en la posición de un archivo*/
void seek_write(int fd,off_t offset,const char v){

    lseek(fd, offset, SEEK_SET);//setea el offset del archivo a offset bytes
    int n = write(fd, &v, 1);

    if(n<0){
        perror("write");
        exit(EXIT_FAILURE);
    }

    return;

}
char seek_read(int fd,off_t offset){
    char c;
    lseek(fd, offset, SEEK_SET);//setea el offset del archivo a offset bytes
    int n = read(fd, &c, 1);

    if(n<0){
        perror("read()");
        exit(EXIT_FAILURE);
    }

    return c;

}


int main(void){

    char path[] = "basura.txt";

    int pos = 3;

    int fd = open(path, O_RDWR);


    pid_t pid;

    pid = fork();
    if(pid == 0 ){
        char c = seek_read(fd, pos);
        printf("soy el hijo, lei: %c\n",c);

        seek_write(fd, pos, '+');
    }
    else{
        char c = seek_read(fd, pos);

        printf("Soy el padre, lei: %c\n", c);

        seek_write(fd, pos, '-');
        wait(0);
    }

    close(fd);

    return 0;
}
