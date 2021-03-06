#include "Utils.h"

void ImprimimrOrdenes();
void Procesar_Orden(Mensaje mensaje);
void avisar(Orden* broker1 , Orden* broker2 , int d , int p);
void avisar2(Orden* compra , Orden* venta , char *broker);

list_t* compras = NULL;
list_t* ventas = NULL;
list_t* brokers;

int fd1 ;

int main(int argc, char const *argv[])
{
  printf("%s\n", "\n Corriendo Bolsa de valores ...");
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
    close(fd);
    Procesar_Orden(mensaje);
    if(isEmpty(compras) != 1){
      printf("\n%s\n","\t===== COMRPAS =====" );
      printf("Empresa   Precio   Cantidad   Tipo  Broker\n" );
      print(compras,0);
    }
    if(isEmpty(ventas) != 1){
      printf("\n%s\n","\t=== VENTAS ====" );
      printf("Empresa   Precio   Cantidad   Tipo  Broker\n" );
      print(ventas,1);
    }
    printf("%s\n","Orden Procesada !" );

  }
}
//========================================================================
void ImprimimrOrdenes(){

}
//========================================================================
void Procesar_Orden(Mensaje mensaje){

  int band =0,resta = 0 , precio = 0;
  Broker* auxb = Broker_t(mensaje.pipename,mensaje.pid) ;
  Orden* auxo,*ocomp,*ovent,*mend1 ,*mend ;
  Respuesta* auxr ;
  if(get_node(brokers,(const void *)auxb) == NULL){
    add_order(brokers,(const void *) auxb);
  }else{
    free(auxb);
  }
  if((mensaje.orden).tip == 'C'){
    //compra
    ocomp = &mensaje.orden;
    mend1 = Orden_t((mensaje.orden).tip , (mensaje.orden).empresa , (mensaje.orden).cantidad  , (mensaje.orden).precio , (mensaje.orden).broker);
    if(isEmpty(ventas)){
      add_order(compras,mend1 );
      printf("%s\n","Se registro la compra !." );
    }else{
      last_t(ventas);
      while (ventas->window != NULL && band == 0) {
        ovent = (Orden *)(ventas->window)->value;
        if(ocomp->precio >= ovent->precio && strcmp(ocomp->empresa , ovent->empresa) == 0){
          resta = ovent->cantidad - ocomp->cantidad;
          if (resta == 0){
            band = 1;
            avisar(ovent , ocomp , ovent->cantidad,0);
            del_t(ventas);
            last_t(ventas);
          }else if(resta > 0){
            band = 1 ;
            ovent->cantidad = resta ;
            avisar(ovent , ocomp , ocomp->cantidad,0);
          }else{
            ocomp->cantidad = (resta)*-1;
            avisar(ovent , ocomp ,ovent->cantidad,0);
            del_t(ventas);
            last_t(ventas);
            free(mend1);
            mend1 = Orden_t((mensaje.orden).tip , (mensaje.orden).empresa , (mensaje.orden).cantidad  , (mensaje.orden).precio , (mensaje.orden).broker);
          }
        }else{
          back_t(ventas);
        }
      }
      if(band == 0){
        add_order(compras ,(const void *) mend1);
      }
    }
  }else{
    if((mensaje.orden).tip == 'V'){
      //venta
      ovent = &mensaje.orden;
      mend = Orden_t((mensaje.orden).tip , (mensaje.orden).empresa , (mensaje.orden).cantidad  , (mensaje.orden).precio , (mensaje.orden).broker);
      if(isEmpty(compras) == 1){
        add_order(ventas,mend);
      }else{
        home_t(compras);
        while (compras->window != NULL && band == 0) {
          ocomp = (Orden *)(compras->window)->value;
          if(ovent->precio <= ocomp->precio && strcmp(ocomp->empresa , ovent->empresa) == 0){
            resta = ocomp->cantidad - ovent->cantidad;
            if(resta == 0){
              band = 1 ;
              avisar(ovent , ocomp , ocomp->cantidad , 1);
              del_t(compras);
              home_t(compras);
            }else if (resta > 0){
              band = 1 ;
              ocomp->cantidad = resta ;
              avisar(ovent , ocomp , ovent->cantidad , 1);
            }else{
              ovent->cantidad = (resta)*-1 ;
              avisar(ovent , ocomp , ocomp->cantidad , 1);
              del_t(compras);
              home_t(compras);

              free(mend);
              mend = Orden_t((mensaje.orden).tip , (mensaje.orden).empresa , (mensaje.orden).cantidad  , (mensaje.orden).precio , (mensaje.orden).broker);
            }
          }else{
            next_t(compras);
          }
        }
        if(band == 0){
          add_order(ventas,(const void *) mend);
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
        avisar2(NULL,NULL,(mensaje.pipename));
      }else{
        //EXISTE
        precio = ocomp->precio ;
        (mensaje.orden).precio = precio ;
        band =0 ;
        ovent = &mensaje.orden;
        mend = Orden_t((mensaje.orden).tip , (mensaje.orden).empresa , (mensaje.orden).cantidad  , (mensaje.orden).precio , (mensaje.orden).broker);
        if(isEmpty(compras) == 1){
          add_order(ventas,mend);
        }else{
          home_t(compras);
          while (compras->window != NULL && band == 0) {
            ocomp = (Orden *)(compras->window)->value;
            if(ovent->precio <= ocomp->precio && strcmp(ocomp->empresa , ovent->empresa) == 0){
              resta = ocomp->cantidad - ovent->cantidad;
              if(resta == 0){
                band = 1 ;
                avisar(ovent , ocomp , ocomp->cantidad , 1);
                del_t(compras);
                home_t(compras);
              }else if (resta > 0){
                band = 1 ;
                ocomp->cantidad = resta ;
                avisar(ovent , ocomp , ovent->cantidad , 1);
              }else{
                ovent->cantidad = (resta)*-1 ;
                avisar(ovent , ocomp , ocomp->cantidad , 1);
                del_t(compras);
                home_t(compras);

                free(mend);
                mend = Orden_t((mensaje.orden).tip , (mensaje.orden).empresa , (mensaje.orden).cantidad  , (mensaje.orden).precio , (mensaje.orden).broker);
              }
            }else{
              next_t(compras);
            }
          }
          if(band == 0){
            add_order(ventas,(const void *) mend);
          }
        }
      }
    }
  }
}
//========================================================================
void avisar(Orden* broker1 , Orden* broker2 , int d , int p){

  int fd ,creado=0;
  int fd2,precio ;
  Broker* baux ;
  Respuesta *respuesta;

  if (p == 1){
    precio = broker2->precio;
  }else{
    precio = broker1->precio;
  }

  if(broker1 != NULL){

    baux = (Broker*)(get_node(brokers,(const void *) Broker_t(broker1->broker,1111) ))->value;
    if ( kill (baux->pid, SIGUSR1) == -1){
      perror("Kill : ");
      exit(1);
    }
    //ABRIR PIPE
    sleep(2);
    do
    {
      fd = open(broker1->broker, O_WRONLY|O_NONBLOCK );

      if ( fd == -1)
      {
        perror(" Cliente  Abriendo el segundo pipe. Se volvera a intentar ");
        sleep(5);
      }
      else
      {
        creado = 1;
      }
    } while (creado == 0);
    respuesta = Respuesta_t(broker1->tip,d, precio , broker1->empresa , broker2->broker);
    if(write(fd, respuesta, sizeof(struct Resp)) == -1){
      perror(" Write ");
      exit(2);
    }

    close(fd);
  }
  if(broker2 != NULL){

    baux = (Broker*)(get_node(brokers,(const void *) Broker_t(broker2->broker,1111) ))->value;
    respuesta = Respuesta_t(broker2->tip,d, precio , broker2->empresa , broker1->broker);

    if ( kill (baux->pid, SIGUSR1) == -1){
      perror("Kill : ");
      exit(1);
    }
    //ABRIR PIPE
    creado = 0 ;
    sleep(2);
    do
    {
      fd2 = open(broker2->broker, O_WRONLY|O_NONBLOCK );

      if ( fd2 == -1)
      {
        perror(" Cliente  Abriendo el segundo pipe. Se volvera a intentar ");
        sleep(5);
      }
      else
      {
        creado = 1;
      }
    } while (creado == 0);
    if(write(fd2, respuesta, sizeof(struct Resp)) == -1){
      perror(" Write ");
      exit(2);
    }
    close(fd2);
  }


}
//========================================================================
void avisar2(Orden* compra , Orden* venta , char *broker){
  int pventa = -1 , pcompra = -1 ,fd2,creado;
  Respuesta* respuesta ;
  Broker* baux ;
  respuesta = Respuesta_t('Q', pcompra, pventa , "" , "");
  if(compra != NULL){
    pcompra = compra->precio ;
    respuesta = Respuesta_t('Q', pcompra, pventa , compra->empresa , "");
  }
  if(venta != NULL){
    pventa = venta->precio ;
    respuesta = Respuesta_t('Q', pcompra, pventa , compra->empresa , "");
  }
  baux = (Broker*)(get_node(brokers,(const void *) Broker_t(broker,1111) ))->value;
  if ( kill (baux->pid, SIGUSR1) == -1){
    perror("Kill : ");
    exit(1);
  }


  //ABRIR PIPE
  creado = 0 ;
  sleep(2);
  do
  {
    fd2 = open(broker, O_WRONLY|O_NONBLOCK );

    if ( fd2 == -1)
    {
      perror(" Cliente  Abriendo el segundo pipe. Se volvera a intentar ");
      sleep(5);
    }
    else
    {
      creado = 1;
    }
  } while (creado == 0);

  if(write(fd2, respuesta, sizeof(struct Resp)) == -1){
    perror(" Write ");
    exit(2);
  }
  close(fd2);

}
//========================================================================
