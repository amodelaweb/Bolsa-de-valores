#ifndef __UTILS_H
#define __UTILS_H

#include "Broker.h"
#include "Orden.h"
#include "StockMarket.h"
#include <string.h>
#include <stdlib.h>

#define TAMNOMBRE 20

Empresa* Empresa_t(int acciones ,char* nombre );
Broker* Broker_t(char* nombre , char* nompipe , int pid);
Orden* Orden_t( char tipo , char* nombre_emp , int cant ,  int precio , char* nombreb);
Datos* Datos_t(int monto ,char* nombre , char* nombrepipe);

#endif // !__UTILS_H
