#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    int rank, size;
    int valor;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(size < 2){
        if(rank == 0){

            printf("Se necesitan al menos dos procesos\n");
        }
        MPI_Finalize();
        return 0;
    }

    if(rank == 0){
        printf("Ingrese el valor entero: ");
        fflush(stdout);
        scanf("%d",&valor);

        printf("Proceso %d: envio valor %d al proceso %d\n",rank,valor, rank+1);
        MPI_Send(
            &valor, // dato a enviar
            1, //cantidad de elementos
            MPI_INT, //tipo de dato
            rank+1,//destino
            0, //etiqueta
            MPI_COMM_WORLD
        );
    }
    else{
        MPI_Recv(
            &valor,
            1,
            MPI_INT,
            rank-1,
            0,
            MPI_COMM_WORLD,
            MPI_STATUS_IGNORE
        );
        printf("Proceso %d: recibi valor %d del proceso %d\n",rank,valor, rank-1);
        if (rank < size - 1) {
            printf("Proceso %d: envio valor %d al proceso %d\n",
                   rank, valor, rank + 1);

            MPI_Send(
                &valor,
                1,
                MPI_INT,
                rank + 1,
                0,
                MPI_COMM_WORLD
            );
        }
        else{
            printf("Proceso %d: soy el ultimo proceso, el valor llego al final\n", rank);

        }
    }
    MPI_Finalize();


}