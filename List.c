#include "List.h"
#include <stdlib.h>
//Funciones de la lista
list_t* list(int value){
  list_t *lista =  (list_t*)malloc(sizeof(struct list));
  lista->head = node(value) ;
  lista->last = lista->head ;
  return lista ;
}
//==========================================================
void add(list_t* list , int value) {
  list->la
}
//==========================================================
void remove(list_t* list , int value){

}
//==========================================================
node_t* get_node(list_t* list, int value){

}
//Funciones del nodo
node_t* node(int value){
  node_t *nodo =  (node_t*)malloc(sizeof(struct node));
  nodo->value = value ;
  nodo->next = NULL ;
  nodo->back = NULL ;
  return nodo ;
}
