#include <stdio.h>
#include <mpi.h>


int main(int argc, char* argv[]){

    int my_id, num_procs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    int suma_local = my_id;
    int to_send = my_id;
    int buf;
    int next = (my_id+1) % num_procs; 
    int prev = my_id == 0 ? num_procs-1:my_id-1;
    
    for(int i = 0; i < num_procs - 1; i++){

        MPI_Send(&to_send, 1, MPI_INT, next,0, MPI_COMM_WORLD);
        MPI_Recv(&buf, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        suma_local += buf;
        to_send = buf;
    }


    printf("[Proceso %d] | suma_total = %d \n", my_id, suma_local);

    MPI_Finalize();
}