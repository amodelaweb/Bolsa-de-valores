#ifndef ORDEN_H_
#define ORDEN_H_

#define TAMNOMBRE 20

typedef struct Orden
{
   char empresa[TAMNOMBRE];
   int precio;
   int cantidad;
   char tip;
   char broker[TAMNOMBRE];
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
  char empresa[TAMNOMBRE];
  char brokers[TAMNOMBRE];
  int acciones ;
  int monto ;
}Respuesta;
/*mensaje broker -> stockMarket
el pipe name es el nonmbre del broker
*/
typedef struct Mns
{
  Orden orden;
  int pid;
  char pipename[TAMNOMBRE];
}Mensaje;

#endif
