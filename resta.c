    /**********************************************************************************************
    * Matrix Multiplication Program using MPI.
    *
    * Viraj Brian Wijesuriya - University of Colombo School of Computing, Sri Lanka.
    *
    * Works with any type of two matrixes [A], [B] which could be multiplied to produce a matrix [c].
    *
    * Master process initializes the multiplication operands, distributes the muliplication
    * operation to worker processes and reduces the worker results to construct the final output.
    *
    ************************************************************************************************/
    
#include<stdio.h>
#include<mpi.h>
#define NUM_ROWS_A 512 //Filas de la matriz [A]
#define NUM_COLUMNS_A 512 //Columnas de la matriz [A]
#define NUM_ROWS_B 512 //Filas de la matriz [B]
#define NUM_COLUMNS_B 512 //Columnas de la matriz [B]
#define MASTER_TO_SLAVE_TAG 1 //Etiqueta para mensajes enviados del maestro a esclavos
#define SLAVE_TO_MASTER_TAG 4 //Etiqueta para mensajes enviados de esclavos a maestro
    
void makeAB(); // Fabrica las [A] y [B] matrices
void printArray(); //Imprime la salida en una matriz [C];
int rank; //Rango de procesos   
int size; //Número de procesos
int i, j, k; //Variables auxiliares    
double mat_a[NUM_ROWS_A][NUM_COLUMNS_A]; // Declara entrada en [A]  
double mat_b[NUM_ROWS_B][NUM_COLUMNS_B]; // Declara entrada en [B]  
double mat_result[NUM_ROWS_A][NUM_COLUMNS_B]; //Declara una salida [C]   
double start_time; //mantiene tiempo de inicio   
double end_time; // mantiene tiempo de fin
int low_bound; // Límite inferior del número de filas de A asociadas a un esclavo 
int upper_bound; // Límite superior del número de filas de A asociadas a un esclavo   
int portion; // porción del número de filas de [A] asociadas a un esclavo

MPI_Status status; //  Almacenaje de estado de un  MPI_Recv
MPI_Request request; // Captura de solicitud de un MPI_Isend

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv); // Inicializa operaciones MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtén el rango
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtén el número de procesos

    /* maestro inicializa la carga*/
    if (rank == 0) {
    	makeAB();
    	start_time = MPI_Wtime();
    	for (i = 1; i < size; i++) {//"Para cada esclavo que no sea el maestro
    		portion = (NUM_ROWS_A / (size - 1)); // clacula porción sin el maestro
    		low_bound = (i - 1) * portion;
    		if (((i + 1) == size) && ((NUM_ROWS_A % (size - 1)) != 0)) {// Si las filas en [A] no pueden serigualmente divididas entre esclavos
    			upper_bound = NUM_ROWS_A; // Último esclavo, se queda con las filas sobrantes
    		} else {
    			upper_bound = low_bound + portion; //las filas de [A] son equitativamente divisibles entre esclavos
    		}
    		// Envía el límite inferior primero sin bloquear, al esclavo  deseado
    		MPI_Isend(&low_bound, 1, MPI_INT, i, MASTER_TO_SLAVE_TAG, MPI_COMM_WORLD, &request);
    		// Luego, en vía el l{imite superior sin bloquear al eslavo deseado
    		MPI_Isend(&upper_bound, 1, MPI_INT, i, MASTER_TO_SLAVE_TAG + 1, MPI_COMM_WORLD, &request);
    		// Finalmente envía el la porción asignada de filas de [A] sin bloquear al eslavo deseado
    		MPI_Isend(&mat_a[low_bound][0], (upper_bound - low_bound) * NUM_COLUMNS_A, MPI_DOUBLE, i, MASTER_TO_SLAVE_TAG + 2, MPI_COMM_WORLD, &request);
    	}
    }
    
    // Transmite a [B] a todos los esclavos
    MPI_Bcast(&mat_b, NUM_ROWS_B*NUM_COLUMNS_B, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    /* Carga hecha por los esclavos*/
    if (rank > 0) {
    	// Recibe límite inferior del maestro.
    	MPI_Recv(&low_bound, 1, MPI_INT, 0, MASTER_TO_SLAVE_TAG, MPI_COMM_WORLD, &status);
    	// Luego, recibe límite superior desde el maestro
    	MPI_Recv(&upper_bound, 1, MPI_INT, 0, MASTER_TO_SLAVE_TAG + 1, MPI_COMM_WORLD, &status);
   	 // Finalmente recibe la porción de filas de [A] a ser procesadas por el maestro
    	MPI_Recv(&mat_a[low_bound][0], (upper_bound - low_bound) * NUM_COLUMNS_A, MPI_DOUBLE, 0, MASTER_TO_SLAVE_TAG + 2, MPI_COMM_WORLD, &status);
    	for (i = low_bound; i < upper_bound; i++) {// Itera a através de un conjunto de filas dadas de [A]
    		for (j = 0; j < NUM_COLUMNS_B; j++) {// Itera a através de un conjunto de culomnas dadas de [B]
    				mat_result[i][j] = (mat_a[i][j] - mat_b[i][j]);
    		}
    	}
    
    	//Envía de vuelta el límite inferior primero, sin bloquear, al maestro
    	MPI_Isend(&low_bound, 1, MPI_INT, 0, SLAVE_TO_MASTER_TAG, MPI_COMM_WORLD, &request);
    	//Envía de vuelta el límite superior primero, sin bloquear, al maestro
    	MPI_Isend(&upper_bound, 1, MPI_INT, 0, SLAVE_TO_MASTER_TAG + 1, MPI_COMM_WORLD, &request);
    	//Finalmente envía la porcion procesada de datos sin bloquear al maestro
    	MPI_Isend(&mat_result[low_bound][0], (upper_bound - low_bound) * NUM_COLUMNS_B, MPI_DOUBLE, 0, SLAVE_TO_MASTER_TAG + 2, MPI_COMM_WORLD, &request);
    }

    /* El maestro recibe la carga*/
    if (rank == 0) {
    	for (i = 1; i < size; i++) {// Hasta que todos los esclavos hayan devuelto los datos procesados
    		//Recibe límite inferior de un esclavo
    		MPI_Recv(&low_bound, 1, MPI_INT, i, SLAVE_TO_MASTER_TAG, MPI_COMM_WORLD, &status);
    		//Recibe límite superior de un esclavo
    		MPI_Recv(&upper_bound, 1, MPI_INT, i, SLAVE_TO_MASTER_TAG + 1, MPI_COMM_WORLD, &status);
    		//Recibe datos procesados de un esclavo
    		MPI_Recv(&mat_result[low_bound][0], (upper_bound - low_bound) * NUM_COLUMNS_B, MPI_DOUBLE, i, SLAVE_TO_MASTER_TAG + 2, MPI_COMM_WORLD, &status);
    	}
    	end_time = MPI_Wtime();
    	printf("\nRunning Time = %f\n\n", end_time - start_time);
    	printArray();
    }
    MPI_Finalize(); // Finaliza operaciones MPI
    return 0;
}

void makeAB()
{
    for (i = 0; i < NUM_ROWS_A; i++) {
    	for (j = 0; j < NUM_COLUMNS_A; j++) {
    		mat_a[i][j] =1;
    	}
    }
    for (i = 0; i < NUM_ROWS_B; i++) {
    	for (j = 0; j < NUM_COLUMNS_B; j++) {
    		mat_b[i][j] = 2;
    	}
    }
}

void printArray()
{
    /*for (i = 0; i < NUM_ROWS_A; i++) {
    	printf("\n");
    	for (j = 0; j < NUM_COLUMNS_A; j++)
    		printf("%8.2f ", mat_a[i][j]);
    }
    printf("\n\n\n");
    for (i = 0; i < NUM_ROWS_B; i++) {
    	printf("\n");
    	for (j = 0; j < NUM_COLUMNS_B; j++)
    		printf("%8.2f ", mat_b[i][j]);
    }
    printf("\n\n\n");*/
    for (i = 0; i < NUM_ROWS_A; i++) {
    	printf("\n");
    	for (j = 0; j < NUM_COLUMNS_B; j++)
    		printf("%8.2f ", mat_result[i][j]);
    }
    printf("\n\n");
}


