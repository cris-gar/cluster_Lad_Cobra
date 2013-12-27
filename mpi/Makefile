
CPP = gcc
RUN = mpirun

FLAGMPI = -np

MPI_INCLUDE = /usr/lib/openmpi/include 

NTHREADS = 4

cluster: cluster.c
	$(CPP)  cluster.c -o cluster -I/usr/lib/openmpi/include

	
run: cluster
	$(RUN) -np 8 --hostfile /home/hostfile ./cluster

clear:
	rm -f *.o	
