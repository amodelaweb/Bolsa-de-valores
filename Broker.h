#ifndef __Broker_H
#define __Broker_H

typedef struct Empresa
{
    char* nombre;
    int acciones;
} Empresa;
/*el pipename es el nombre del pipe de stockmarket
el nombre es el nombre del broker y tambien el nombre del pipename*/
typedef struct Datos
{
    int monto;
    Empresa* empresas;
    int tam ;
    char* nombre;
    char* pipename;
    int pid;
} Datos;
/*es necesario crear dos hilos*/
#endif // !__Broker_H
