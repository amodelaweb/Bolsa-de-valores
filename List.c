#include "List.h"
#include <stdlib.h>
#include <stdio.h>
//Funciones de la lista
list_t* list(int (*comparator) (const void* e1 , const void* e2)){
  list_t *lista =  (list_t*)malloc(sizeof(struct list));
  lista->head = NULL ;
  lista->last = NULL ;
  lista->comparator = comparator ;
  return lista ;
}
//==========================================================
void add(list_t* list , const void* value) {

  if(list->head != NULL){
    node_t* aux = Add(list->last,value);
    list->last = aux ;
  }else{
    list->head = node(value) ;
    list->last = list->head ;
  }
}
//==========================================================
void remove_element(list_t* list , const void* value){
  if(list->head !=NULL){
    node_t* aux = list->head ;
    if (list->comparator(&(list->head)->value,&value) == 0){
      if(list->head == list->last){
        list->last = NULL ;
      }
      list->head = aux->next;
      (list->head)->back = NULL ;
      free(aux);
    }else{

      aux = get_node(list , value);
      if(aux != NULL){
        (aux->back)->next = aux->next;
        if(aux->next != NULL)
        (aux->next)->back = aux->back ;
        if(aux == list->last){
          list->last = aux->back;
        }
        free(aux);
      }
    }
  }
}
//==========================================================
node_t* get_node(list_t* list, const void* value){
  int band = 0 ;
  if(list->head != NULL){
    node_t* aux = list->head;
    while (aux != NULL && band == 0) {
      aux = aux->next;
      if(aux != NULL){
        if(list->comparator(&aux->value,&value) == 0){
          band = 1 ;
        }
      }
    }
    return aux  ;
  }
  return NULL ;
}
//==========================================================
void print(list_t* list,int mode){
  if(list->head != NULL){
    if(mode == 0){
      node_t* aux = list->head;
      print_t(aux->value );
      while (aux->next != NULL) {
        aux = aux->next;
        print_t(aux->value );
      }
    }else{
      node_t* aux = list->last;
      print_t(aux->value);
      while (aux->back != NULL) {
        aux = aux->back;
        print_t( aux->value );
      }
    }
  }
}
//==========================================================
void add_order(list_t* list , const void* value){
  if(list->head!=NULL){
    node_t* aux = list->head ;
    node_t* aux2 ;
    if (list->comparator(&value , &aux->value) < 0){
      list->head = node(value);
      (list->head)->next = aux ;
      aux->back = list->head;
      list->last = aux ;
    }else{
      while(list->comparator(&value,&aux->value) > 0 && (aux->next != NULL)) {
        aux = aux->next;
      }
      if(list->comparator(&value,&aux->value) > 0){
        aux->next = node(value);
        (aux->next)->back = aux ;
        list->last = aux->next ;
      }else{
        aux2 = aux->back ;
        aux->back = node(value);
        (aux->back)->back = aux2 ;
        (aux->back)->next = aux ;
        aux2->next = aux->back ;
      }
    }
  }else{
    list->head = node(value) ;
    list->last = list->head ;
  }
}
int isEmpty(list_t* list){
  if(list->head == NULL){
    return 1 ;
  }else{
    return 0 ;
  }
}
//Funciones del nodo
node_t* node(const void* value){
  node_t *nodo =  (node_t*)malloc(sizeof(struct node));
  nodo->value = value ;
  nodo->next = NULL ;
  nodo->back = NULL ;
  return nodo ;
}
//==========================================================
node_t* Add(node_t*node1, const void* value){
  if(node1->next == NULL){
    node1->next = node(value);
    (node1->next)->back = node1;
    return node1->next ;
  }else{
    return NULL ;
  }
}
//==========================================================
