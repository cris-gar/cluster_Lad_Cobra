Aplicación para operaciones básicas en una matriz de 900x900 usando cluster vía Ethernet.
=================

Configuración Clúster MPI en Ubuntu.

Primero necesitamos 3 máquinas, con sistema operativo GNU/Linux. Para este caso usaremos Ubuntu 13.10. A su vez, el nombre de usuario de cada nodo, deben llamarse EXACTAMENTE IGUAL. Usaremos el nombre "cluster" (sin comillas). Al mismo tiempo definiermos cada nodo con un nombre de máquina propio.

- Nombre equipo maestro: n13  Ip maestro: 10.1.10.113
- Nombre equipo esclavo: n14  Ip maestro: 10.1.10.114
- Nombre equipo esclavo: n15  Ip maestro: 10.1.10.115
 

# Nodo maestro #

## Paso 1: actualización de SO e instalación de programas a utilizar ##

```
sudo apt-get update
```
```
sudo apt-get upgrade
```
```
sudo apt-get install gcc g++
```
``` 
sudo apt-get install openmpi-bin openmpi-common
```
```
libopenmpi1.3 libopenmpi-dev
```
```
sudo apt-get install ssh
```
```
sudo apt-get install nfs-kernel-server nfs-common portmap
```
```
sudo apt-get install build-essential
```
## Paso 2: Creación de carpeta a compartir ## 

- Posicionarse en carpeta cluster

```
cd /home/ cluster
```

```
mkdir .ssh
```

```
sudo chmod 777 .ssh
```

```
cd ../../
```

```
sudo mkdir /mpi
```

```
sudo chmod 777 /mpi
```

```
cd /mpi
```

```
sudo chown user /mpi
```

## Paso 3: Editar ficheros hosts y exports ##

```
sudo gedit /etc/hosts
```





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
