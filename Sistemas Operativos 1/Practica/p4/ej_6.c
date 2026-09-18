#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <omp.h>

#define UMBRAL 10000

void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int particionar(int a[], int N) {
    int i, j = 0;
    int p = a[0];

    swap(&a[0], &a[N - 1]);

    for (i = 0; i < N - 1; i++) {
        if (a[i] <= p) {
            swap(&a[i], &a[j++]);
        }
    }

    swap(&a[j], &a[N - 1]);

    return j;
}

void qsort_sec(int a[], int N) {
    if (N < 2)
        return;

    int p = particionar(a, N);

    qsort_sec(a, p);
    qsort_sec(a + p + 1, N - p - 1);
}

/* ---------------- PTHREAD ---------------- */

typedef struct {
    int *a;
    int N;
} Args;

void qsort_pthread(int a[], int N);

void *qsort_pthread_wrapper(void *arg) {
    Args *args = (Args *) arg;
    qsort_pthread(args->a, args->N);
    return NULL;
}

void qsort_pthread(int a[], int N) {
    if (N < 2)
        return;

    int p = particionar(a, N);

    if (N < UMBRAL) {
        qsort_sec(a, p);
        qsort_sec(a + p + 1, N - p - 1);
        return;
    }

    pthread_t hilo_izq;

    Args args_izq;
    args_izq.a = a;
    args_izq.N = p;

    pthread_create(&hilo_izq, NULL, qsort_pthread_wrapper, &args_izq);

    qsort_pthread(a + p + 1, N - p - 1);

    pthread_join(hilo_izq, NULL);
}

/* ---------------- OPENMP SECTIONS ---------------- */

void qsort_sections(int a[], int N) {
    if (N < 2)
        return;

    int p = particionar(a, N);

    if (N < UMBRAL) {
        qsort_sec(a, p);
        qsort_sec(a + p + 1, N - p - 1);
        return;
    }

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            qsort_sections(a, p);
        }

        #pragma omp section
        {
            qsort_sections(a + p + 1, N - p - 1);
        }
    }
}

/* ---------------- OPENMP TASKS ---------------- */

void qsort_task_rec(int a[], int N) {
    if (N < 2)
        return;

    int p = particionar(a, N);

    if (N < UMBRAL) {
        qsort_sec(a, p);
        qsort_sec(a + p + 1, N - p - 1);
        return;
    }

    #pragma omp task
    qsort_task_rec(a, p);

    #pragma omp task
    qsort_task_rec(a + p + 1, N - p - 1);

    #pragma omp taskwait
}

void qsort_tasks(int a[], int N) {
    #pragma omp parallel
    {
        #pragma omp single
        {
            qsort_task_rec(a, N);
        }
    }
}

/* ---------------- AUXILIARES ---------------- */

void llenar_random(int a[], int N) {
    for (int i = 0; i < N; i++) {
        a[i] = random();
    }
}

int esta_ordenado(int a[], int N) {
    for (int i = 1; i < N; i++) {
        if (a[i - 1] > a[i]) {
            return 0;
        }
    }

    return 1;
}

void copiar(int dst[], int src[], int N) {
    memcpy(dst, src, N * sizeof(int));
}

int main(int argc, char *argv[]) {
    int N = 1000000;

    if (argc >= 2) {
        N = atoi(argv[1]);
    }

    int num_threads = 4;

    if (argc >= 3) {
        num_threads = atoi(argv[2]);
    }

    omp_set_num_threads(num_threads);

    printf("N = %d\n", N);
    printf("hilos OpenMP = %d\n", num_threads);
    printf("UMBRAL = %d\n\n", UMBRAL);

    int *original = malloc(N * sizeof(int));
    int *a = malloc(N * sizeof(int));

    if (original == NULL || a == NULL) {
        fprintf(stderr, "Error reservando memoria\n");
        return 1;
    }

    srandom(0);
    llenar_random(original, N);

    double t0, t1;

    copiar(a, original, N);
    t0 = omp_get_wtime();
    qsort_sec(a, N);
    t1 = omp_get_wtime();
    printf("Secuencial:        %.6f s | ordenado = %s\n",
           t1 - t0, esta_ordenado(a, N) ? "si" : "no");

    copiar(a, original, N);
    t0 = omp_get_wtime();
    qsort_pthread(a, N);
    t1 = omp_get_wtime();
    printf("pthread_create:    %.6f s | ordenado = %s\n",
           t1 - t0, esta_ordenado(a, N) ? "si" : "no");

    copiar(a, original, N);
    t0 = omp_get_wtime();
    qsort_sections(a, N);
    t1 = omp_get_wtime();
    printf("OpenMP sections:   %.6f s | ordenado = %s\n",
           t1 - t0, esta_ordenado(a, N) ? "si" : "no");

    copiar(a, original, N);
    t0 = omp_get_wtime();
    qsort_tasks(a, N);
    t1 = omp_get_wtime();
    printf("OpenMP tasks:      %.6f s | ordenado = %s\n",
           t1 - t0, esta_ordenado(a, N) ? "si" : "no");

    free(original);
    free(a);

    return 0;
}