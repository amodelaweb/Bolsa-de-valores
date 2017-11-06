#include "List.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
int f(const void *a1 , const void *b1){
  int a = *(int *)a1;
  int b = *(int *)b1;

  if(a < b){
    return -1 ;
  }else{
    if(a > b){
      return 1 ;
    }else{
      return 0 ;
    }
  }
}

void print_t (const void *elemento){
  int a = *(int *)elemento;
  printf("%d\n", a);
}
int main(int argc, char const *argv[]) {
  list_t* lista = list(&f , &print_t);
  int n = 3 ;
  add_order(lista,(const void *)  (intptr_t) n);
  n = 5 ;
  add_order(lista,(const void *)  (intptr_t) n);
  n = 1 ;
  add_order(lista,(const void *)  (intptr_t) n);
  n = 7 ;
  add_order(lista,(const void *)  (intptr_t) n);
  n = 2 ;
  add_order(lista,(const void *)  (intptr_t) n);

  remove_element(lista,(const void *)7);

  print(lista,0);
  printf("=============\n");
  print(lista,1);

}
