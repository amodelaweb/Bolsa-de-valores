#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "Broker.h"
#include "Orden.h"
#include "List.h"
/*se encarga de leer los datos del archivo*/
list_t* leerDatos(char* arch);
/*se encarga que los datos esten correctos para despues enviarlos
si son correctos retorna 1*/
int validarEntrada(char* arch);
/*envia los datos al stockMarket*/
int enviarDatos(char* arch);
char* recibirDatos();


int main(int argc, char const * argv[])
{
    int monto;
    list_t* empresas ;
    char* nombre;
    char* pipename;
    empresas = leerDatos(argv[3]);
    char* comando;

    int continuar;
    if(argc < 5)
    {
        printf("faltan datos \n");
        printf("Orden de datos: nombre pipename recursos_iniciales monto \n");
        exit(1);
    }

    strcpy(nombre,argv[1]);
    strcpy(pipename,argv[2]);
    monto = atoi(argv[4]);

    printf("Datos ingresados correctamente\n");
    continuar = 1;
    while(continuar)
    {
        scanf(comando);
        validarEntrada(comando);
    }
    

}

list_t* leerDatos(char* arch)
{

}

int validarEntrada(char* comando)
{

}
char* recibirDatos()
{

}
