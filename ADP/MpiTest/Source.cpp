#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int random;
	bool lider = true;
	int otherNumbers, otherRanks;

	// Initialize the MPI environment
	MPI_Init(NULL, NULL);

	// Get the number of processes
	int world_size;

	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Status status;
	// Get the rank of the process
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	// Get the name of the processor
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name, &name_len);

	srand(time(NULL) + (world_rank * 63));
	random = rand() % 50;
	//random = 11;
	for (int i = 0; i < world_size; i++) {
		if (i != world_rank) {
			MPI_Send(&random, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Recv(&otherNumbers, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			if (random < otherNumbers) {
				lider = false;
			}
			else if (random == otherNumbers) {
				MPI_Send(&world_rank, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
				MPI_Recv(&otherRanks, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				if (world_rank < otherRanks) {
					lider = false;
				}
			}
		}
	}

	printf("Hello world numarul : %d , rank %d"
		" out of %d processors\n",
		random , world_rank, world_size);

	if (lider) {
		printf("Cel mai mare numar este %d al procesului %d ", random, world_rank);
	}


	// Print off a hello world message
	//printf("Hello world from processor %s, rank %d"
	//	" out of %d processors\n",
	//	processor_name, world_rank, world_size);

	// Finalize the MPI environment.
	MPI_Finalize();
}