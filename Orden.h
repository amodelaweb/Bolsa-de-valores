#ifndef ORDEN_H_
#define ORDEN_H_

typedef struct Orden
{
   char* empresa;
   int precio;
   int cantidad;
   char* broker; // borrar
   char tip;
} Orden;
typedef struct Resp
{
  char tipo;
  int acciones ;
  int monto ;
  int confirmacion;
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
