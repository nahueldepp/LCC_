#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 200
int A[N][N], B[N][N], C[N][N];

void mult_secuencial(int A[N][N], int B[N][N], int C[N][N])
{
    int i, j, k;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            for (k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
}
void mult_paralela(int A[N][N], int B[N][N], int C[N][N], int num_hilos)
{
    int i, j, k;
#pragma omp parallel for num_threads(num_hilos) colapse(2)
    for (i = 0; i < N; i++)
    {

        for (j = 0; j < N; j++)
        {

            int suma = 0;
            for (k = 0; k < N; k++)
            {

                suma += A[i][k] * B[k][j];
            }
            C[i][j] = suma;
        }
    }
}

int main()
{
    int i, j;
#pragma omp parallel for colapse(2)
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++)
        {
            A[i][j] = random() % 1000;
            B[i][j] = random() % 1000;
        }
    }

    double inicio, fin;

    inicio = omp_get_wtime();
    mult_secuencial( A, B, C);
    fin = omp_get_wtime();

    double tiempo_sec = fin - inicio;

    printf("Secuencial: %.6f segundos\n", tiempo_sec);

    int hilos[] = {1, 2, 4, 8, 16};
    int cant_hilos = sizeof(hilos) / sizeof(hilos[0]);

    for (int i = 0; i < cant_hilos; i++)
    {
        int t = hilos[i];

        inicio = omp_get_wtime();
        mult_paralela( A, B, C, t);
        fin = omp_get_wtime();

        double tiempo_par = fin - inicio;
        double speedup = tiempo_sec / tiempo_par;

        printf("OpenMP %2d hilos: %.6f segundos | speedup = %.2f\n",
               t, tiempo_par, speedup);
    }
    return 0;
}
