#ifndef __LIST_H__
#define __LIST_H__

/*---tipo de funciones---*/
typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*FuncionComparadora) (void* dato1, void* dato2);
/*-----------------------*/


/*
 *Nodo de una lista doblemente enlazada
 */
struct _SNodo{
  void* dato;
  struct _SNodo* sig;
  struct _SNodo* ant;
};
typedef struct _SNodo* Nodo;

/**
 * Lista general doblemente enlazada con puntero al inicio y al final 
 */
struct _GLista{
  Nodo izq;
  Nodo der;
};
typedef struct _GLista* GLista;
/*
 * estructura de la lista que evaluaran las funciones
 */
struct _List{
  char* nombre;
  GLista glista;
};
typedef struct _List* Lista;

typedef enum{
    DLIST_RECORRIDO_HACIA_ADELANTE,
    DLIST_RECORRIDO_HACIA_ATRAS
} DListOrdenDeRecorrido;

typedef void (*FuncionVisitanteInt)  (int);

/*
 *crea una lista general vacia
 */
GLista glista_crear();

/**
 * retorna 1 si la lista esta vacia, 0 en caso contrario
 */
int glista_vacia(GLista lista);

/**
 * destruye una lista general
 */
void glista_destruir(GLista lista, FuncionDestructora destr);
/**
 * agrega un elemento a la izquierda en una lista general
 */
GLista glista_agregar_izq(GLista lista, void* dato, FuncionCopia copia);

/**
 * agrega un elemento a la derecha en una lista general
 */
GLista glista_agregar_der(GLista lista,void* dato, FuncionCopia copia);

/**
 * Elimina el elemento a la izquierda de la lista
 */
GLista glista_eliminar_izq(GLista lista, FuncionDestructora destr);

/**
 * Elimina el elemento de la derecha de la lista
 */
GLista glista_eliminar_der(GLista lista, FuncionDestructora destr);

/**
 * Crea una copia de una lista general
 */
GLista glista_copiar(GLista lista, FuncionCopia copia);

/**
 * Recorre la lista usando una FuncionVisitante
 */
void glista_recorrer(GLista lista, FuncionVisitante func, int sentidoLista);

/*
 * Crea una lista
 * dependiendo del operador crear una lista para DEFL o APPLY
 */
Lista lista_crear(char* tokens[], int numTokens,int tipoLista);

/*
 *Destruye una lista
 */
void lista_destruir(Lista lista);

/**
 * Crea una copia fisica de la lista dada
 */
Lista lista_copia(Lista lista);

/**
 * Compara dos listas
 */
int lista_comparar(Lista l1, Lista l2);

/**
 * compara el cuerpor de las listas
 * retorna 1 si son iguales, 0 en caso contrario
 */
int lista_comparar_cuerpo(Lista l1, Lista l2);
/**
 * retorna 1 si los extremos de la lista son iguales, 0 en caso contrario
 */
int lista_lados_iguales(Lista lista);

/**
 * imprime una lista 
 */
void lista_imprimir(Lista lista);

/**
 * Hashear un contacto por su nombre.
 */
unsigned lista_hashear(Lista lista);

unsigned lista_hashear2(Lista lista);

/*
 *Devuelve la longitud de una lista.
 */
int glista_longitud(GLista lista);



#endif /* __GLIST_H__ */
