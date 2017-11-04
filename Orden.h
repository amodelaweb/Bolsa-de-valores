#ifndef ORDEN_H_
#define ORDEN_H_

typedef struct Orden
{
   char* empresa;
   int precio;
   int cantidad;
   char* broker;
   char tip;
} Orden;

#endif
