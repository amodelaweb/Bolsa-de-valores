#ifndef ORDEN_H_ 
#define ORDEN_H_

typedef struct Orden
{
   char empresa[20];
   int precio;
   int cantidad;
   char broker[20];
   char tipo[1];
} Orden;

#endif
