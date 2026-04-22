#ifndef _DLIST_H_
#define _DLIST_H_

#include <stddef.h>

/*
 *Nodo en una lista doblemente enlazada
 */
typedef struct _DNodo{
    int dato;
    struct _DNodo* sig;
    struct _DNodo* ant;
}DNodo;


/*
 * mantiene un puntero al inicio de la lista y una al final
 */
typedef struct{
    DNodo* primero;
    DNodo* ultimo;
}DList;


typedef enum{
    DLIST_RECORRIDO_HACIA_ADELANTE,
    DLIST_RECORRIDO_HACIA_ATRAS
} DListOrdenDeRecorrido;

typedef void (*FuncionVisitante)  (int);

/*
 * crea una lista vacia
 */
DList dlist_crear();

/*
 *Destruye una lista
 */
void dlist_destruir(DList lista);
/*
 * Agrega un elemento al inicio
 */
DList dlist_agregar_inicio(DList lista, int dato);

/*
 *Agrega un elemento al final
 */
DList dlist_agregar_final(DList lista, int dato);

/*
 *recorre la lista dada una funcion
 */
void dlist_recorrer(DList lista, FuncionVisitante func, int sentidoLista);


/*
 *Devuelve la longitud de una lista.
 */
int slist_longitud(DList lista);



#endif