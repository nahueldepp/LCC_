#include <stdio.h>
#include <mpi.h>

#define N 21

int main(int argc, char* argv[] ){

    int arr[N];
    for(int i = 0; i<N; i++){
        arr[i] = 1; 
    }
    int rank, num_procs;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    int base, elementos_locales, inicio;
    base = N / num_procs;
    inicio = rank*base;
    elementos_locales = base; 
    
    if(rank == num_procs-1){
        //al ultimo proceso le agrego los elementos sobrantes
        int resto = N%num_procs;
        elementos_locales += resto; 
    }

    int suma_local= 0;

    for(int i = inicio; i < inicio+elementos_locales; i++){
        suma_local += arr[i];
    }

    int suma_total = 0;
    MPI_Reduce(&suma_local, &suma_total,1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("La suma total es: %d\n",suma_total);
    }
    MPI_Finalize();

}