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
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>


#define TAMNOMBRE 20
#define maxchar 20

/* Constructores */
Empresa* Empresa_t(int acciones ,char* nombre );
Broker* Broker_t(char* nombre , int pid);
Orden* Orden_t( char tipo , char* nombre_emp , int cant ,  int precio , char* broker);
Datos* Datos_t(int monto ,char* nombre , char* nombrepipe);
Mensaje* Mensaje_t(Orden* orden,int pid,char* pipename);
Respuesta* Respuesta_t(char tipo, int acciones , int monto,char* empresa , char* broker);
/* Comparadores para lista */
int comparator_orden(const void *a1 , const void *b1);
int comparator_broker(const void *a1 , const void *b1);
/* Utilidades */
void print_t(const void *elemento);
void printb_t(const void *elemento);
void to_lowercase(char* str);
void add_empresa(Datos* broker,Empresa* empresa);
#endif // !__UTILS_H
