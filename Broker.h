#ifndef __Broker_H
#define __Broker_H

typedef struct Empresa
{
    char* nombre;
    int acciones;
} Empresa;

typedef struct Datos
{
    int monto;
    Empresa* empresas;
    char* nombre;
    char* pipename;
} Datos;
/*es necesario crear dos hilos*/
#endif // !__Broker_H
