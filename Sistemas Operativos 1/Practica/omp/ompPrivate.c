#include <stdio.h>
#include <omp.h>
#include <pthread.h>

int main()
{

    int i = 10;
#pragma omp parallel private(i) // define una variable i local
    {
        // variable i is not initialized
        printf("thread %d: i = %d\n", omp_get_thread_num(), i);
        i = 1000;
    }
    printf("private i = %d\n", i);
#pragma omp parallel firstprivate(i)
    {
        // variable i is initialized to its original value
        printf("thread %d: i = %d\n", omp_get_thread_num(), i);
        i = 1000;
    }
    printf("firstprivate i = %d\n", i);


    int a[]={1,2,3,4,5,6};
    int b[]={1,2,3,4,5,6};
    
#pragma omp parallel
    {
    #pragma omp for lastprivate(i)
            for (i = 0; i < 5; i++)
                a[i] = b[i] + b[i + 1];
    }
    a[i] = b[i]; // i = n-1

    printf("a[5] = %d\n", a[i]);
    return 0;
}