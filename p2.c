#include "Utils.h"

int main(int argc, char const *argv[]) {
  char* nombre = (char*)malloc((sizeof (char))*TAMNOMBRE) ;
  strcpy(nombre,"NomBr:,A");
  //Empresa* empresa = Empresa_t(4,nombre);
  //Broker* broker = Broker_t(nombre,nombre,123);
  //Orden* orden = Orden_t('C',nombre,1,2,nombre);
  //Orden* orden1 = Orden_t('V',nombre,3,4,nombre);
  //Orden* orden2 = Orden_t('C',nombre,5,6,nombre);
  //printf("-------%s\n",orden->empresa );
  //list_t* lista = list(&comparator_venta , &print_t);
  //add_order(lista,(const void *) orden);
  //add_order(lista,(const void *) orden1);
  //add_order(lista,(const void *) orden2);

  to_lowercase(nombre);
  printf("%s\n",nombre );
  //print(lista,0);
  //printf("=============\n");
  //print(lista,1);

  return 0;
}
