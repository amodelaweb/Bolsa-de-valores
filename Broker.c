#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "Broker.h"
#include "Orden.h"
#include "List.h"

#define tamchar = 20;

/*hilos*/
/*se encarga de recibir las respuestas asincronas*/
void *respuestaAsin(void *datos);
/*se encargar de recibir los comandos del usuario*/
void *manejoUsuario(void *datos);
/*se encarga de leer los datos del archivo*/
list_t* leerDatos(char* arch);
/*se encarga que los datos esten correctos para despues enviarlos
si son correctos retorna 1*/
int validarEntrada(char* arch);
/*envia los datos al stockMarket*/
int enviarDatos(char* arch);
char* recibirDatos();

Datos datos;

int main(int argc, char const * argv[])
{
    char* comando;
    pthread_t thread1, thread2;
    int continuar;
    /*fin de variables*/
    datos.nombre = malloc(sizeof(char) * 20);
    datos.pipename = malloc(sizeof(char) * 20);

    
    if(argc < 5)
    {
        printf("faltan datos \n");
        printf("Orden de datos: nombre pipename recursos_iniciales monto \n");
        exit(1);
    }

    strcpy(datos.nombre,argv[1]);
    strcpy(datos.pipename,argv[2]);
    datos.monto = atoi(argv[4]);
    datos.empresas = leerDatos(argv[3]);

    printf("Datos ingresados correctamente\n");

    /*crear hilo recepcion respuesta  asincrona*/
    /* crear hilo para comandos */

    if (pthread_create(&thread1, NULL, respuestaAsin, (void *)&datos) != 0)
    {
        perror("ERROR\n");
        exit(2);
    }
    if (pthread_create(&thread2, NULL, manejoUsuario, (void *)&datos) != 0)
    {
        perror("ERROR\n");
        exit(2);
    }

    continuar = 1;
    while(continuar)
    {
        scanf(comando);
        validarEntrada(comando);
        enviarDatos(comando);
        prinf(recibirDatos(comando));
    }
    

}
void *respuestaAsin(void *datos)
{

}

void *manejoUsuario(void * Datos)
{
    int continuar;

    char *comando = sizeof(char) * tamchar; 
    continuar = 1;
    while (continuar)
    {
        scanf(comando);
        if(strcmp(comando,"salir") == 0)
        {
            /*antes de cerrar se muestra con que saldo quedo y el numero de acciones de cadaempresa*/
            exit(1);
        }
        else
        {
            validarEntrada(comando);
            enviarDatos(comando);
            prinf(recibirDatos(comando));
        }
    }
}
list_t* leerDatos(char* arch)
{
    // archivo
    FILE *archivo;
    char* caracteres = malloc(sizeof(char) * 30);
    // token
    char str[80] = "This is - www.tutorialspoint.com - website";
    const char s[2] = "-";
    char *token;

    Empresa empresa;
    list_t list = list();
    

    archivo = fopen(arch, "r");
    /*revisar perror*/
    if (archivo == NULL)
    {
        printf("eror abrir archivo");
        exit(1);
    }     
    else
    {
        printf("\nEl contenido del archivo de prueba es \n\n");
        while (feof(archivo) == 0)
        {
            fgets(caracteres, 30, archivo);
            printf("%s", caracteres);
            //
            empresa ;
            /* get the first token */
            token = strtok(str, s);

            /* walk through other tokens */
            while (token != NULL)
            {
                printf(" %s\n", token);
                empresa
                token = strtok(NULL, s);
            }
            add_order(list, (const void *)(Empresa)empresa);
        }
        system("PAUSE");
    }
    fclose(archivo);
}

int validarEntrada(char* comando)
{

}
int enviarDatos(char *arch)
{

}
char* recibirDatos()
{

}
