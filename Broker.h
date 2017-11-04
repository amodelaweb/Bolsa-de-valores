#ifndef __Broker_H
#define __Broker_H

#include "List.h"
typedef struct Empresa
{
    char nombre[20];
    int acciones;
} Empresa;

typedef struct Datos
{
    int monto;
    list_t *empresas;
    char *nombre;
    char *pipename;

} Datos;

/*e snecesario crear dos hilos*/
#endif // !__Broker_H
