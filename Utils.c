#include "Utils.h"

Empresa* Empresa_t(int acciones ,char* nombre ){
  Empresa *empresa = (Empresa*)malloc(sizeof(struct Empresa)) ;
  empresa->acciones = acciones ;
  empresa->nombre = (char*)malloc((sizeof (char))*TAMNOMBRE) ;
  memset(empresa->nombre, 0, sizeof empresa->nombre);
  strncpy(empresa->nombre, nombre, sizeof empresa->nombre - 1);
  return empresa ;
}
Broker* Broker_t(char* nombre , char* nompipe , int pid){
  Broker *broker = (Broker*)malloc(sizeof(struct InfBroker)) ;
  broker->Broker = (char*)malloc((sizeof (char))*TAMNOMBRE) ;
  memset(broker->Broker, 0, sizeof broker->Broker);
  strncpy(broker->Broker, nombre, sizeof broker->Broker - 1);
  broker->pipe = (char*)malloc((sizeof (char))*TAMNOMBRE) ;
  memset(broker->pipe, 0, sizeof broker->pipe);
  strncpy(broker->pipe, nompipe, sizeof broker->pipe - 1);
  broker->pid = pid;
  return broker ;
}
Orden* Orden_t(char* nombre_emp , int precio , int cant , char* nombreb , char tipo){
  Orden *orden = (Orden*)malloc(sizeof(struct Orden)) ;
  orden->empresa = (char*)malloc((sizeof (char))*TAMNOMBRE) ;
  memset(orden->empresa, 0, sizeof orden->empresa);
  strncpy(orden->empresa, nombre_emp, sizeof orden->empresa - 1);
  orden->precio = precio ;
  orden->cantidad = cant ;
  orden->broker = (char*)malloc((sizeof (char))*TAMNOMBRE) ;
  memset(orden->broker, 0, sizeof orden->broker);
  strncpy(orden->broker, nombreb, sizeof orden->broker - 1);
  orden->tip = 'C';
  orden->tip = 'V';
  return orden ;
}

/*crear constructor datos*/
/*typedef struct Datos
{
    int monto;
    Empresa* empresas ;//
    char* nombre;
    char* pipename;
} Datos;*/
