#include "List.h"

int main(int argc, char const *argv[]) {
  list_t* lista = list();
  add(lista,5);
  add(lista,4);
  add(lista,3);
  return 0;
}
