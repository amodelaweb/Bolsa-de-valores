#ifndef LIST_H
#define LIST_H

//ESTRUCTURAS DE DATOS
typedef struct node {
  struct node *next ;
  struct node *back ;
  const void* value;
} node_t;

typedef struct list{
  node_t *head ;
  node_t *last;
  node_t *window;
  int (*comparator) (const void* e1 , const void* e2);
  void (*print_t) (const void *elemento);
} list_t ;

//Funciones de la lista
list_t* list(int (*comparator) (const void* e1 , const void* e2) , void (*print_t) (const void *elemento));
void add(list_t* list , const void* value) ;
void add_order(list_t* list , const void* value) ;
int isEmpty(list_t* list);
void remove_element(list_t* list , const void* value);
node_t* get_node(list_t* list, const void* value);
void print(list_t* list,int mode);
//Funciones del nodo
node_t* node(const void* value);
node_t* Add(node_t*node1, const void* value);
void next_t(list_t* list);
void back_t(list_t* list);
void home_t(list_t* list);
void last_t(list_t* list);
void del_t(list_t* list);
void pop(list_t* list);

#endif
