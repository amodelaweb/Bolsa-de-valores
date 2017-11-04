#include "Utils.h"


Empresa* Empresa(int acciones ,char* nombre ){
  Empresa *empresa = (Empresa*)malloc(sizeof(struct Empresa)) ;
  empresa->acciones = acciones ;
  empresa->nombre = (char*)malloc((sizeof char)*TAMNOMBRE) ;
  return empresa ;
}
Broker* Broker(char* nombre , char* nompipe , int pid){
  Broker *broker = (Broker*)malloc(sizeof(struct InfBroker)) ;
  broker->Broker = acciones ;
  empresa->nombre = (char*)malloc((sizeof char)*TAMNOMBRE) ;
  return empresa ;
}
Orden* Orden (char* nombre_emp , int precio , int cant , char* nombreb , int tipo){

}
