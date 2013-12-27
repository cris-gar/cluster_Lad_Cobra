cluster_Lad_Cobra
=================

ubicarse en la carpeta CDD

Compilamos el codigo con la siguiente sentencia

mpicc <nomArchivo>.c -o <nomAliasArchivo>

luego de compilar ejecutamos

mpirun -np <numero de hilos> --hostfile /home/hostfile ./<nomAliasArchivo>

para revisar todos los nodos instalar htop
```
sudo apt-get install htop
```
