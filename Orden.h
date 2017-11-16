#ifndef ORDEN_H_
#define ORDEN_H_

typedef struct Orden
{
   char* empresa;
   int precio;
   int cantidad;
   char tip;
   char* broker;
  } Orden;
/*
tipo:
  -c :compra
  -v :venta
  -q :consulta
broker: representa al nombre del del broker involucrado
*/
typedef struct Resp
{
  char tipo;
  char* empresa;
  char* brokers;
  int acciones ;
  int monto ;
}Respuesta;
/*mensaje broker -> stockMarket
el pipe name es el nonmbre del broker
*/
typedef struct Mns
{
  Orden* orden;
  int pid;
  char* pipename;
}Mensaje;

#endif
