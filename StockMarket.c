#include "Utils.h"

list_t* compras = list(&comparator_orden , &print_t);
list_t* ventas = list(&comparator_orden , &print_t);
list_t* brokers = list(&comparator_broker , &printb_t);

void ImprimimrOrdenes();
void Procesar_Orden(Mensaje mensaje);
void avisar(char* broker1 , char* broker2 , Respuesta *r);

int main(int argc, char const *argv[])
{

  /*inicializar listas de:
  -compras
  -ventas
  -brokers
  */
  if (argc != 2){
    printf("\n Uso: ./%s Nombre_Pipe",argv[0]);
    exit(1);
  }
  int fd , n;
  mode_t fifo_mode = S_IRUSR | S_IWUSR;
  Mensaje mensaje;
  unlink(argv[1]);
  // Creacion del pipe inicial, el que se recibe como argumento del main
  if (mkfifo (argv[1], fifo_mode) == -1) {
    perror("StockMarket mkfifo : ");
    exit(1);
  }

  while(1){
    creado = 0 ;
    do {
      fd = open (c, O_RDONLY);
      if (fd == -1) {
        perror("pipe");
        printf(" Se volvera a intentar despues\n");
        //sleep(5);
      } else creado = 1;
    } while (creado == 0);
    do{
      n = read(fd,mensaje,sizeof(struct Mns));
    }while(n < 0);
    close(fd);
    Procesar_Orden(mensaje);
  }
}
//========================================================================
void ImprimimrOrdenes(){

}
//========================================================================
void Procesar_Orden(Mensaje mensaje){
  int band =0,resta = 0;
  Broker* auxb = Broker_t(mensaje.pipename,mensaje.pid) ;
  if(get_node(brokers,(const void *)auxb) == NULL){
    add_order(brokers,(const void *) auxb);
  }else{
    free(auxb);
  }
  if((mensaje.orden)->tip = 'C'){
    //compra
    if(isEmpty(ventas)){
      add_order(compras,(const void *) mensaje.orden);
    }else{
      last_t(ventas);
      while (ventas->window != NULL && band == 0) {
        if((mensaje.orden)->precio <= (compras->window)->precio ){
          band = 1;
        }
        back_t(ventas);
      }
      if(band == 0){
        add_order(compras ,(const void *) mensaje.orden);
      }
    }
  }else{
    if((mensaje.orden)->tip = 'V'){
      //venta
      if(isEmpty(compras)){
        add_order(ventas,(const void *) mensaje.orden);
      }else{
        home_t(compras);
        while (compras->window != NULL && band == 0) {
          if((mensaje.orden)->precio <= (compras->window)->precio ){
            band = 1;
            resta = (compras->window)->cantidad - (mensaje.orden)->cantidad;
            if(resta == 0){
              //NOTIFICAR A LOS DOS BROKERS
              del_t(compras);
            }else if (resta > 0){
              //LAS COMPRAS TIENEN MAS QUE LAS VENTAS
            }else{
              //notificar las ventas tiene mas que compra
              del_t(compras);

              //MENOR QUE CERO
            }
          }
          next_t(compras);
        }
        if(band == 0){
          add_order(ventas,(const void *) mensaje.orden);
        }
      }
    }
  }

}
//========================================================================
void avisar(char* broker1 , char* broker2 , Respuesta *r){

}
//========================================================================
