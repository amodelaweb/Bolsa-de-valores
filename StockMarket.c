#include "Utils.h"

void ImprimimrOrdenes();
void Procesar_Orden(Mensaje mensaje);
void avisar(Orden* broker1 , Orden* broker2 , int d);
void avisar2(Orden* compra , Orden* venta , char *broker);

list_t* compras;
list_t* ventas;
list_t* brokers;

int fd1 ;

int main(int argc, char const *argv[])
{

  compras = list(&comparator_orden , &print_t);
  ventas = list(&comparator_orden , &print_t);
  brokers = list(&comparator_broker , &printb_t);
  /*inicializar listas de:
  -compras
  -ventas
  -brokers
  */
  if (argc != 2){
    printf("\n Uso: %s Nombre_Pipe\n",argv[0]);
    exit(1);
  }
  int fd , n, creado;
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
      fd = open (argv[1], O_RDONLY );
      if (fd == -1) {
        perror("pipe");
        printf(" Se volvera a intentar despues\n");
        //sleep(5);
      } else{
        creado = 1;
      }
    } while (creado == 0);

    do{
      n = read(fd,&mensaje,sizeof(Mensaje));
    }while(n <= 0);


    do{
      fd1 = open(mensaje.pipename,O_WRONLY | O_NONBLOCK);
      perror(" Market abriendo pipe de respuesta : ");
      printf(" Se volvera a intentar despues\n");
      //sleep(5); //los unicos sleeps que deben colocar son los que van en los ciclos para abrir los pipes.
    }while(fd1 < 0 );

    Procesar_Orden(mensaje);
    print(compras,0);
    printf("%s\n","Orden Procesada !" );
    close(fd);
  }
}
//========================================================================
void ImprimimrOrdenes(){

}
//========================================================================
void Procesar_Orden(Mensaje mensaje){
  int band =0,resta = 0 , precio = 0;
  Broker* auxb = Broker_t(mensaje.pipename,mensaje.pid) ;
  Orden* auxo,*ocomp,*ovent ;
  Respuesta* auxr ;
  if(get_node(brokers,(const void *)auxb) == NULL){
    printf("%s\n","ES ESTO PA " );
    add_order(brokers,(const void *) auxb);
    printf("%s\n","despues" );
  }else{
    free(auxb);
  }
  if((mensaje.orden).tip == 'C'){
    //compra
    ocomp = &mensaje.orden;
    Orden* mend = Orden_t((mensaje.orden).tip , (mensaje.orden).empresa , (mensaje.orden).cantidad  , (mensaje.orden).precio , (mensaje.orden).broker);
    if(isEmpty(ventas)){
      add_order(compras,(const void *)mend );
      printf("%s\n","Se registro la compra !." );
    }else{
      last_t(ventas);
      while (ventas->window != NULL && band == 0) {
        printf("MAYBE ES AQUI\n");
        ovent = (Orden *)(ventas->window)->value;
        printf(" NO LO SE RICK\n");
        if(ocomp->precio >= ovent->precio && strcmp(ocomp->empresa , ovent->empresa) == 0){
          printf("PARECE FALSO :V \n");
          resta = ovent->cantidad - ocomp->cantidad;
          if (resta == 0){
            printf("SINO SE ES LA C\n");
            band = 1;
            avisar(ovent , ocomp , 0);
            printf(" ES DEL ? \n");
            del_t(ventas);
            printf("NOP\n");
          }else if(resta > 0){
            printf("O LA D\n");
            band = 1 ;
            ovent->cantidad = resta ;
            avisar(ovent , ocomp , 0);
          }else{
            printf("NO C BRO PARECE FALSO \n");
            ocomp->cantidad = (resta)*-1;
            avisar(ovent , ocomp , 0);
            del_t(ventas);
          }
        }else{
          printf("ESTO ES MUY EXTRAÑO\n");
          back_t(ventas);
        }
      }
      printf("SI LLEGASTE AQUI\n");
      if(band == 0){
        add_order(compras ,(const void *) ocomp);
      }
    }
  }else{
    if((mensaje.orden).tip == 'V'){
      //venta
      ovent = &mensaje.orden;
      Orden* mend = Orden_t((mensaje.orden).tip , (mensaje.orden).empresa , (mensaje.orden).cantidad  , (mensaje.orden).precio , (mensaje.orden).broker);
      if(isEmpty(compras) == 1){
        add_order(ventas,(const void *) mend);
      }else{
        home_t(compras);
        while (compras->window != NULL && band == 0) {
          ocomp = (Orden *)(compras->window)->value;
          if(ovent->precio <= ocomp->precio && strcmp(ocomp->empresa , ovent->empresa) == 0){
            resta = ocomp->cantidad - ovent->cantidad;
            if(resta == 0){
              band = 1 ;
              avisar(ovent , ocomp , 1);
              del_t(compras);
            }else if (resta > 0){
              band = 1 ;
              ovent->cantidad = resta ;
              avisar(ovent , ocomp , 1);
            }else{
              ovent->cantidad = (resta)*-1 ;
              avisar(ovent , ocomp , 1);
              del_t(compras);
              home_t(compras);
            }
          }else{
            next_t(compras);
          }
        }
        if(band == 0){
          add_order(ventas,(const void *) ovent);
        }
      }
    }else if((mensaje.orden).tip == 'Q'){
      home_t(compras);
      last_t(ventas);
      ocomp = NULL ;
      ovent = NULL ;
      while(compras->window != NULL && band == 0){
        if(strcmp(((Orden*)((compras->window)->value))->empresa , (mensaje.orden).empresa) == 0){
          band = 1 ;
          ocomp = ((Orden*)((compras->window)->value)) ;
        }else{
          next_t(compras);
        }
      }
      band = 0 ;
      while(ventas->window != NULL && band == 0){
        if(strcmp(((Orden*)((ventas->window)->value))->empresa , (mensaje.orden).empresa) == 0){
          band = 1 ;
          ovent = ((Orden*)((ventas->window)->value)) ;
        }else{
          back_t(ventas);
        }
      }

      avisar2(ocomp,ovent,(mensaje.pipename));

    }else if ((mensaje.orden).tip == 'T'){
      home_t(compras);
      ocomp = NULL ;
      while(compras->window != NULL && band == 0){
        if(strcmp(((Orden*)((compras->window)->value))->empresa , (mensaje.orden).empresa) == 0){
          band = 1 ;
          ocomp = ((Orden*)((compras->window)->value)) ;
        }else{
          next_t(compras);
        }
      }
      if(ocomp == NULL){
        //NO EXISTE EMPRESA
      }else{
        band = 0 ;
        precio = ocomp->precio ;
        (mensaje.orden).precio = precio ;
        ovent = &mensaje.orden;
        Orden* mend = Orden_t((mensaje.orden).tip , (mensaje.orden).empresa , (mensaje.orden).cantidad  , (mensaje.orden).precio , (mensaje.orden).broker);
        if(isEmpty(compras) == 1){
          add_order(ventas,(const void *) mend);
        }else{
          home_t(compras);
          while (compras->window != NULL && band == 0) {
            ocomp = (Orden *)(compras->window)->value;
            if(ovent->precio <= ocomp->precio && strcmp(ocomp->empresa , ovent->empresa) == 0){
              resta = ocomp->cantidad - ovent->cantidad;
              if(resta == 0){
                band = 1 ;
                avisar(ovent , ocomp , 1);
                del_t(compras);
              }else if (resta > 0){
                band = 1 ;
                ovent->cantidad = resta ;
                avisar(ovent , ocomp , 1);
              }else{
                ovent->cantidad = (resta)*-1 ;
                avisar(ovent , ocomp , 1);
                del_t(compras);
                home_t(compras);
              }
            }else{
              next_t(compras);
            }
          }
          if(band == 0){
            add_order(ventas,(const void *) ovent);
          }
        }

      }
    }
  }
}
//========================================================================
void avisar(Orden* broker1 , Orden* broker2 , int d){
  int fd1,fd2,precio ;
  Broker* baux ;
  Respuesta *respuesta;

  if (d == 1){
    precio = broker1->precio;
  }else{
    precio = broker2->precio;
  }
  if(broker1 != NULL){
    respuesta = Respuesta_t('C',broker1->cantidad, precio , broker1->empresa , broker2->broker);
    baux = (Broker*)(get_node(brokers,(const void *) Broker_t(broker1->broker,1111) ))->value;
    if ( kill (baux->pid, SIGUSR1) == -1){
      perror("Kill : ");
      exit(1);
    }
    sleep(5);

    write(fd1, respuesta, sizeof(struct Resp));


  }
  /*if(broker2 != NULL){
  baux = (Broker*)(get_node(brokers,(const void *) Broker_t(broker2->broker,1111) ))->value;
  respuesta = Respuesta_t('C',broker2->cantidad, precio , broker2->empresa , broker1->broker);
  if ( kill (baux->pid, SIGUSR1) == -1){
  perror("Kill2 : ");
  exit(1);
}
do{
fd2 = open(broker2->broker, O_WRONLY|O_NONBLOCK);
perror(" Market abriendo pipe de respuesta : ");
printf(" Se volvera a intentar despues\n");
sleep(5); //los unicos sleeps que deben colocar son los que van en los ciclos para abrir los pipes.
}while(fd2 < 0 );

write(fd2, respuesta, sizeof(struct Resp));

}
*/

}
//========================================================================
void avisar2(Orden* compra , Orden* venta , char *broker){
  int pventa = -1 , pcompra = -1 ,fd2;
  Respuesta* respuesta ;
  Broker* baux ;
  if(compra != NULL){
    pcompra = compra->precio ;
  }
  if(venta != NULL){
    pventa = venta->precio ;
  }
  do{
    fd2 = open(broker, O_WRONLY|O_NONBLOCK);
    perror(" Market abriendo pipe de respuesta : ");
    printf(" Se volvera a intentar despues\n");
    //sleep(5); //los unicos sleeps que deben colocar son los que van en los ciclos para abrir los pipes.
  }while(fd2 < 0 );
  baux = (Broker*)(get_node(brokers,(const void *) Broker_t(broker,1111) ))->value;
  respuesta = Respuesta_t('Q', pcompra, pventa , compra->empresa , "");
  write(fd2, respuesta, sizeof(struct Resp));
  if ( kill (baux->pid, SIGUSR1) == -1){
    perror("Kill : ");
    exit(1);
  }
}
//========================================================================
