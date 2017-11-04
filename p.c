#include "List.h"
#include <stdio.h>
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
int main(int argc, char const *argv[]) {
  list_t* lista = list(&f);
  int n = 3 ;
  add_order(lista,(const void *) n);
  n = 5 ;
  add_order(lista,(const void *) n);
  n = 1 ;
  add_order(lista,(const void *) n);
  n = 7 ;
  add_order(lista,(const void *) n);
  n = 2 ;
  add_order(lista,(const void *) n);

  print(lista,0);
  printf("=============\n");
  print(lista,1);

}
