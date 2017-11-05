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
Orden* Orden_t(char* nombre_emp , int precio , int cant , char* nombreb , char tipo);


#endif // !__UTILS_H
