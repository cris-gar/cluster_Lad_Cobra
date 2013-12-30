Aplicación para operaciones básicas en una matriz de 900x900 usando cluster vía Ethernet en una Red LAN.
=================

Configuración Clúster MPI en Ubuntu.

Primero necesitamos 3 máquinas, con sistema operativo GNU/Linux. Para este caso usaremos Ubuntu 13.10. A su vez, el nombre de usuario de cada nodo, deben llamarse EXACTAMENTE IGUAL. Usaremos el nombre "cluster" (sin comillas). Al mismo tiempo definiermos cada nodo con un nombre de máquina propio.

- Nombre equipo maestro: n13  Ip maestro: 10.1.10.113
- Nombre equipo esclavo: n14  Ip maestro: 10.1.10.114
- Nombre equipo esclavo: n15  Ip maestro: 10.1.10.115


# Nodo Esclavo

## Paso 1: actualización de SO e instalación de programas a utilizar

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
## Paso 2: Creación de carpeta a compartir

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

## Paso 3: Montaje de carpeta maestra.

- Montar carpeta maestra compartida y en cada nodo cliente ejecutar:

```
sudo mount 10.1.10.113:/mpi /mpi

```

```
sudo gedit /etc/fstab
```

- Y escribir

```
10.1.10.113:/mpi /mpi nfs
```
- Luego

```
sudo mount –a
```


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
## Paso 2: Creación de carpeta a compartir

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
- Y escribimos lo siguiente


```
127.0.0.1 localhost

# “ip” “usuario” “equipo”
10.1.10.113 cluster n13 # nodo maestro
10.1.10.014 cluster n14 # nodo esclavo 1
10.1.10.015 cluster n15 # nodo esclavo 2

# The following lines are desirable for IPv6 capable hosts
::1 ip6-localhost ip6-loopback
```
- Luego
```
sudo gedit /etc/exports
```
- Y escribimos lo suiguiente

```
# /etc/exports: the access control list for filesystems which may
be exported
# to NFS clients. See exports(5).
gss/krb5i(rw,sync,fsid=0,crossmnt,no_subtree_check)
# /srv/nfs4/homes gss/krb5i(rw,sync,no_subtree_check )
/mpi *(rw,sync)
```
## Paso 4: Compartición de directorio con nodos esclavo.
 
``` 
 sudo service nfs-kernel-server restart
```
 
 __ ESPERAR A QUE LOS ESCLAVOS MONTEN LA CARPETA __


- Luego

```
ssh-keygen -t rsa
```
- Posicionarse en carpeta .ssh

```
cd /home/cluster/.ssh
```
```
cat id_rsa.pub >> authorized_keys
ssh-copy-id 10.1.10.114
ssh-copy-id 10.1.10.115
```

- Confirmar si el proceso es correcto
 
```
ssh 10.1.10.114
```

_Al ingresar al nodo esclavo este no debe pedir
contraseña._

## Paso 6: Ejecutar Código.

-Ingresar a carpeta maestra

```
cd /mpi
```

-Compilar

```
mpicc <nomArchivo>.c -o <nomAliasArchivo>
```

-Ejecutar programa

```
mpirun -np <numero de hilos> --hostfile /home/hostfile ./<nomAliasArchivo>
```


- Para revisar el estado de distribuición de carga, recomendamos utilizar htop. Se puede instalar como:

```
sudo apt-get install htop
```
