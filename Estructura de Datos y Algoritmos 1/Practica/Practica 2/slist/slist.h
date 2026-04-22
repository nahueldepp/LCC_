#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>

typedef void (*FuncionVisitante) (int dato);
typedef int (*FuncionComparacion) (int dato1, int dato2);
typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);

typedef struct _SNodo {
  int dato;
  struct _SNodo *sig;
} SNodo;

typedef struct _SList{
  SNodo* primero;
  SNodo* ultimo;
}SList2;

typedef SNodo *SList;

/**
 * Devuelve una lista vacía.
 */
SList slist_crear();

/*
  * Devuelve una lista vacia usando la estructura SList2
 */
SList2 slist2_crear();



/**
 * Destruccion de la lista.
 */
void slist_destruir(SList lista);

/**
 * Determina si la lista es vacía.
 */
int slist_vacia(SList lista);

/**
 * Agrega un elemento al final de la lista.
 */
SList slist_agregar_final(SList lista, int dato);

/**
 * Agrega un elemento al final de la lista usando el tipo de estructura SList2
 */
SList2 slist2_agregar_final(SList2 lista, int dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
SList slist_agregar_inicio(SList lista, int dato);

/*
 * Agrega un elemento al inicio de la lista.
 */
SList2 slist2_agregar_inicio(SList2 lista, int dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void slist_recorrer(SList lista, FuncionVisitante visit);

/*
 *Devuelve la longitud de una lista.
 */
int slist_longitud(SList lista);

/*
 * Devuelve la concatenacion de dos listas modificando la primera 
 */
SList slist_concatenar(SList lista1, SList lista2 );

/*
 * Inserta un dato en una lista en una posicion dada
 */
SList slist_insertar(SList lista, int pos, int dato);

/*
 *borra de una lista un dato apuntado en una posicion arbitraria 
 */
SList slist_eliminar(SList lista,int pos);


/*
 *determina si un elemento esta en una lista dada, si la lista contiene el elemento devuelve 1, 0 en caso contrario 
 */
int slist_contiene( SList lista, int dato); 

/*
  * devuelve la posición de la primera ocurrencia de un elemento si el mismo está en la lista dada, y -1 en caso que no esté.
 */
int slist_indice(SList lista, int dato);

/*
 *Devuelve una nueva lista con los elementos comunes (independientemente de la posicion)
  de dos listas dadas por parámetro. Las listas originales no se modifican.
 */
SList slist_intersecar(SList lista1, SList lista2);

/*
 * trabaja como slist_intersecar pero recibe un parametro extra que es un puntero a funcion de comparacion 
 que permite definir la nocion de igualdad al ser usada al comparar elementos
 */
SList slist_custom(SList lista1,SList lista2, FuncionComparacion fun); 

/*
 * ordena una lista de acuerdo al criterio dado por una funcion de comparacion
 (0 si los valores son iguales, 1 si el primer valor es mayor que el segundo y -1 si el primer valor es menor que el segundo)
  pasada por parametro.
 */
SList slist_ordenar(SList lista, FuncionComparacion funComp);

/*
 * dadas dos listas, intercale sus elementos en la lista resultante. Por ejemplo,
 dadas las listas [1, 2, 3, 4] y [5, 6], debe obtener la lista [1, 5, 2, 6, 3, 4].
 La lista mas corta debe pasarse como segundo valor
 */
SList slist_intercalar(SList lista, SList listaAinsertar);


/*
 * divide una lista a la mitad. En caso de longitud impar (2n + 1), la primer lista
 tendra longitud n+1 y la segunda n. Retorna un puntero al primer elemento de la segunda mitad,
 siempre que sea no vacia
 */
SList slist_partir(SList lista); 

/**
 * Dada una lista, deterina si existe en ciclo en la misma, en el caso que no exista, devuelve NULL
 * caso contrario devuelve el puntero de inicio del ciclo
 */
SNodo* slist_ciclo(SList lista);

#endif /* __SLIST_H__ */
