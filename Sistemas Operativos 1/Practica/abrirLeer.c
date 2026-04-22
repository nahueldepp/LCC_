#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (){

    int fd= open("archivo3.txt", O_RDONLY);

    if(fd == -1){
        perror("open\n");
        return 1;
    }

    char buffer[1024];

    ssize_t n = read(fd, buffer, 1024);

    if(n==-1){
        perror("read\n");
        return 1;
    }

    ssize_t m= write(1, buffer, n);

    close(fd);
    return 0;
}