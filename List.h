#ifndef LIST_H
#define LIST_H

//ESTRUCTURAS DE DATOS
typedef struct node {
  struct node *next ;
  struct node *back ;
  int value ;
} node_t;

typedef struct list{
  node_t *head ;
  node_t *last;
} list_t ;

//Funciones de la lista
list_t* list(int value);
void add(list_t list , int value) ;
void remove(list_t list , int value);
node_t* get_node(list_t list, int value);
//Funciones del nodo
node_t* node(int value);

#endif
