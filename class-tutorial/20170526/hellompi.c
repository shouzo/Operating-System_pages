#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int n;
    int total;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &n);
    MPI_Comm_size(MPI_COMM_WORLD, &total);
    printf("This is %d of %d\n", n+1, total);

    MPI_Finalize();
    return 0;
}
