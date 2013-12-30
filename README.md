
Aplicación para operaciones básicas en una matriz de 900x900 usando cluster vía Ethernet.
=================

Configuración Clúster MPI en Ubuntu.

Primero necesitamos 3 máquinas, con sistema operativo GNU/Linux. Para este caso usaremos Ubuntu 13.10. A su vez, el nombre de usuario de cada nodo, deben llamarse EXACTAMENTE IGUAL. Usaremos el nombre "cluster" (sin comillas). Al mismo tiempo definiermos cada nodo con un nombre de máquina propio.

-


ubicarse en la carpeta CDD

Compilamos el codigo con la siguiente sentencia
```
mpicc <nomArchivo>.c -o <nomAliasArchivo>
```
luego de compilar ejecutamos
```
mpirun -np <numero de hilos> --hostfile /home/hostfile ./<nomAliasArchivo>
```
para revisar todos los nodos instalar htop
```
sudo apt-get install htop
```
