#include <stdio.h>
#include <omp.h>
#include <pthread.h>

int main(void)
{

    int a[100000];
#pragma omp parallel
    {
#pragma omp for
        for (long unsigned i = 0; i < 100000; i++)
        {
            a[i] = 2 * i;
        }
    }

    int i = 10;
#pragma omp parallel private(i)
    {
        // variable i is not initialized
        printf("thread %d: i = %d\n", omp_get_thread_num(), i);
        i = 1000;
    }
    printf("private i = %d\n", i);
    return 0;
}