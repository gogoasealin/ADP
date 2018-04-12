#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
	int v[100];
	int vectorToCalculate[10];
	int suma = 0;
	int count = 10;
	int sumaPrimita;
	int procesCount = 0;

	for (int i = 0; i < 100; i++) {
		v[i] = i+1;
	}

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

	if (world_rank == 0) {
		int k;
		int world_rank_count = 1;
		for (int i = 1; i < world_size; i++) {
			for (int j = 0; j < count; j++) {
			    k = j + (10 * world_rank_count);
				vectorToCalculate[j] = v[k];
				//printf(" pe pozitia %d este %d \n", j, vectorToSend[j]);		
			}
			world_rank_count++;
			MPI_Send(&vectorToCalculate, count, MPI_INT, i, 0, MPI_COMM_WORLD);
		}

		for (int j = 0; j < count; j++) {
			vectorToCalculate[j] = v[j];
		}

		//for (int i = 0; i < count; i++) {
		//	printf(" pe pozitia %d este %d \n", i, vectorToCalculate[i]);
		//}

		for (int i = 0; i < count; i++) {
			suma = suma + vectorToCalculate[i];
			//printf("Suma actuala %d \n", suma);
		}
		printf("suma trimisa de %d este %d ", world_rank, suma);
		for (int i = 1; i < 4; i++) {
			MPI_Recv(&sumaPrimita, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			suma += sumaPrimita;
		}
		printf("Suma totala este %d \n", suma);
	}
	else {
		MPI_Recv(&vectorToCalculate, count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		for (int i = 0; i < count; i++) {
			printf(" pe pozitia %d este %d \n", i, vectorToCalculate[i]);
		}
		for (int i = 0; i < count; i++) {
			suma = suma + vectorToCalculate[i];
		//	printf("Suma actuala %d \n", suma);
		}
		printf("suma trimisa de %d este %d ", world_rank, suma);
		MPI_Send(&suma, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		printf("process %d, has end ", world_rank);
	}


	// Print off a hello world message
	//printf("Hello world from processor %s, rank %d"
	//	" out of %d processors\n",
	//	processor_name, world_rank, world_size);

	// Finalize the MPI environment.
	MPI_Finalize();
}