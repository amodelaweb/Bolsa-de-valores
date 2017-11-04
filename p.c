#include "List.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
  list_t* lista = list();
  add(lista,5);
  add(lista,4);
  add(lista,3);
  add(lista,2);
  print(lista,0);
  printf("=============\n");
  print(lista,1);
  return 0;
}
