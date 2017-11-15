#ifndef __UTILS_H
#define __UTILS_H

#include "Broker.h"
#include "Orden.h"
#include "List.h"
#include "StockMarket.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TAMNOMBRE 20
#define maxchar 35;

/* Constructores */
Empresa* Empresa_t(int acciones ,char* nombre );
Broker* Broker_t(char* nombre , char* nompipe , int pid);
Orden* Orden_t( char tipo , char* nombre_emp , int cant ,  int precio , char* nombreb);
Datos* Datos_t(int monto ,char* nombre , char* nombrepipe);
/* Comparadores para lista */
int comparator_venta(const void *a1 , const void *b1);
int comparator_compra(const void *a1 , const void *b1);
/* Utilidades */
void print_t(const void *elemento);
void to_lowercase(char* str);

#endif // !__UTILS_H
