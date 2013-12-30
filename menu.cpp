#include<stdio.h>
#include<stdlib.h>

/*
Autor: Mauro Castillo V.
Descripcion: N primeros numeros impares
Fecha: 08/05/06
*/

int main()
{
    int opcion;
    do{
       system("cls"); 
       printf("1) Ingresar\n");
       printf("2) Imprimir\n");
       printf("3) Sumar\n");
       printf("9) Salir\n");
       printf("Ingrese opcion ");
       scanf("%d",&opcion);      
       if(opcion == 1)
       {
                 printf("llama a llenar");
                 system("pause");
       }
       if(opcion == 2)
       {
                 printf("llama a imprimir");
                 system("pause");
       }
       if(opcion == 3)
       {
                 printf("llama a sumar");
                 system("pause");
       }
    }while(opcion != 9);
    system("pause");
}
