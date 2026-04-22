#ifndef __GLIST_H__
#define __GLIST_H__

/*---tipo de funciones---*/
typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*Predicado)(void* dato);
typedef int (*FuncionComparadora) (void* dato1, void* dato2);
/*-----------------------*/

typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode* GList;
typedef GList SGList;



/**
 * Devuelve una lista vacía.
 */
GList glist_crear();

/**
 * Destruccion de la lista.
 */
void glist_destruir(GList lista, FuncionDestructora destruir);


/**
 * Determina si la lista es vacía.Devuelve 1 en si esta vacia, 0 en caso contrario
 */
int glist_vacia(GList lista);


/**
 * Agrega un elemento al inicio de la lista.
 */
GList glist_agregar_inicio(GList lista, void *dato, FuncionCopia copiar);

/**
 * Agrega un elemento al final de la lista.
 */
GList glist_agregar_final(GList final, void *dato, FuncionCopia copiar);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList lista, FuncionVisitante visitar);


/**
 *Dada una lista general, retorne una nueva lista con los elementos que cumplen con el predicado.
 */
GList glist_filtrar(GList lista, FuncionCopia c, Predicado p);


/**
 * Retorna una lista vacia ordenada
 */
SGList sglist_crear();

/**
 * destruye una ista ordenada
 */
void sglist_destruir(SGList lista, FuncionDestructora funDes);

/**
 * Determina si una lista ordenada esta vacia
 */
int sglist_vacia(SGList lista);

/**
 * aplica la funcion visitante a cada elemento de la lista ordenada
 */
void sglist_recorrer(SGList lista, FuncionVisitante visitante );

/**
 * Inserta un nuevo dao en la lista ordenada.
 *  La funcion comparacion determina el criterio de ordenacion:
 *  Retorna un entero negativo si el primer argumento es menor que el segundo, 0 si son iguales
 *  y un entero positivo si el primer argumento es mayor que el segundo
 */
SGList sglist_insertar(SGList lista, void* data, FuncionCopia copia, FuncionComparadora comparar);


/**
 * Cuenta la cantidad de elementos, retorna el alrgo de la lista
 */

/**
 *  busca un dato en la lista ordenada, retornando 1 si lo encuentra y 0 en caso contrario 
 * (aprovechar que la lista esta ordenada para hacer esta busqueda mas e ciente).
 */
int sglist_buscar(GList lista, void* data, FuncionComparadora comparar);

/**
 *que construye una lista ordenada a partir de un arreglo de elementos y su longitud.
 */
SGList sglist_arr(void **arreglo, int longArr, FuncionCopia funCopia, FuncionComparadora funComparar);
#endif /* __GLIST_H__ */
