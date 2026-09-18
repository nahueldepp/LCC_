#include <stdio.h>
#include <omp.h>
#include <pthread.h>

int main(void){
    #pragma omp parallel //gcc -fopenmp nombre.c -o omp_program
    {
        int id = omp_get_thread_num();
        int nt = omp_get_num_threads();
        printf("id: %d nt: %d\n", id, nt);
    }
    
    return 0;
}