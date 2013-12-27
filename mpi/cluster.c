//============================================================================
// Name        : cluster.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#define pico 900
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int main(void) {
	int A[pico][pico];
	int B[pico][pico];
	int C[pico][pico];

	int i;
	int j;

	for (i=0;i<pico;i++)
		{
			for ( j = 0;  j < pico; j++) {

				int aleatorio1 = rand () % 10;
				int aleatorio2 = rand () % 10;
				A[i][j] = aleatorio1;
				B[i][j] = aleatorio2;
				C[i][j] = A[i][j]+B[i][j];
				printf("%d  ",C[i][j]);
			}
			printf("\n");
		}





	printf("entiendan la wea!\n");
	return 0;
}
