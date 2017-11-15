#include "Utils.h"

list_t* compras = list(&comparator_orden , &print_t);
list_t* ventas = list(&comparator_orden , &print_t);

void ImprimimrOrdenes();

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
  int fd;
  mode_t fifo_mode = S_IRUSR | S_IWUSR
  unlink(argv[1]);
  // Creacion del pipe inicial, el que se recibe como argumento del main
  if (mkfifo (argv[1], fifo_mode) == -1) {
    perror("Server mkfifo : ");
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

    //FUNCION INICIALIZADORA
  }
}

void ImprimimrOrdenes(){

}
