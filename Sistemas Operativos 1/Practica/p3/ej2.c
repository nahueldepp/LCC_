#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/wait.h>

pthread_mutex_t  m = PTHREAD_MUTEX_INITIALIZER;

sem_t s1,s2;


void* rutina_A (void* arg){

    printf("a1\n");
    sem_post(&s2);
    sem_wait(&s1);
    printf("a2\n");
    
}
void* rutina_B(void* arg){
    sem_wait(&s2);
    printf("b1\n");
    sem_post(&s1);
    printf("b2\n");
}
int main(void){

    pthread_t A,B;
    sem_init(&s1, 0, 0); 
    sem_init(&s2, 0 ,0);
    if(pthread_create(&A, NULL,&rutina_A,NULL ) != 0){
        perror("pthread A\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&B, NULL,&rutina_B,NULL ) != 0){
        perror("pthread A\n");
        exit(EXIT_FAILURE);
    }

    pthread_join(A,NULL);
    pthread_join(B,NULL);
    sem_destroy(&s1);
    sem_destroy(&s2);
    return 0;
}