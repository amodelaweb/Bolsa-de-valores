#ifndef __UTILS_H
#define __UTILS_H

#include "Broker.h"
#include "Orden.h"
#include "stockMarket.h"
#include <String.h>

#define TAMNOMBRE 20

Empresa* Empresa(int acciones ,char* nombre );
Broker* Broker(char* nombre , char* nompipe , int pid);
Orden* Orden (char* nombre_emp , int precio , int cant , char* nombreb , int tipo);


#endif // !__UTILS_H
