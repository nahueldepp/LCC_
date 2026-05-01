#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MSG "Hola manola\n"

void* escribir_mensaje(void* msg){

    char* c;
    c = msg;

    setbuf(stdout, NULL);//Unbuffer:  When an output stream is unbuffered,
       //information appears on the destination file or terminal as soon as written;
    while( *c != '\0'){
        putc(*c, stdout);
        c++;
    }
    return NULL;

}
int main(void){

    pthread_t thread;

    int err= pthread_create(&thread, NULL, escribir_mensaje, (void*)MSG );
    if(err != 0){
        perror("pthread_create");
        exit(EXIT_FAILURE);

    }
    pthread_join(thread,NULL);

    /*En este ejemplo*/

    return 0;
}