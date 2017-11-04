#include "List.h"
#include <stdlib.h>
//Funciones de la lista
list_t* list(){
  list_t *lista =  (list_t*)malloc(sizeof(struct list));
  lista->head = NULL ;
  lista->last = NULL ;
  return lista ;
}
//==========================================================
void add(list_t* list , int value) {

  if(list->head != NULL){
    node_t* aux = Add(list->last,value);
    list->last = aux ;
  }else{
    list->head = node(value) ;
    list->last = list->head ;
  }
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

node_t* Add(node_t*node1, int value){
  if(node1->next == NULL){
    node1->next = node(value);
    return node1->next ;
  }else{
    return NULL ;
  }
}
