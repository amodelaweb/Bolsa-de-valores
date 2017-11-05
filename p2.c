#include "Utils.h"

int main(int argc, char const *argv[]) {
  char* nombre = "nombre";
  Empresa* empresa = Empresa_t(4,nombre);
  Broker* broker = Broker_t(nombre,nombre,123);
  Orden* orden = Orden_t(nombre,1,2,nombre,1);
  printf("%s\n",empresa->nombre );
  return 0;
}
