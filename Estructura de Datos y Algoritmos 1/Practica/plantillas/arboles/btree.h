#ifndef __BTREE_H__
#define __BTREE_H__

/*---tipo de funciones---*/
typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef int (*Predicado)(void* dato);
typedef int (*FuncionComparadora) (void* dato1, void* dato2);
typedef void (*FuncionVisitante)(void* dato);
typedef void (*FuncionVisitanteInt)(int dato);
typedef void (*FuncionVisitanteExtra) (int dato, void *extra);
/*-----------------------*/

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

typedef struct _BTNodo{
  void* dato;
  struct _BTNodo* left;
  struct _BTNodo* right;
} BTNodo;

typedef struct _BTNodo *BTree;

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear();

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo, FuncionDestructora destruir);

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo);

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(void* dato, BTree left, BTree right, FuncionCopia copia);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit);

void btree_recorrer_pre_it(BTree arbol, FuncionVisitanteInt visit);

/**
 * retorna el núumero de nodos del árbol.
 */
int btree_nnodos(BTree arbol);

/**
 *retorna 1 si el n´umero dado se encuentra en el ´arbol, y 0 en caso contrario
 */
 int btree_buscar(BTree, void*, FuncionComparadora);

 
 /**
  * Retorna la copia de un arbol dado
  */
 BTree btree_copiar(BTree arbol, FuncionCopia);

 /**
 * retorna la altura de un arbol (distancia desde la raiz hata la hoja mas lejana)
 */
 int btree_altura(BTree arbol);


/**
 * retorna el número de nodos que se encuentran a una profundidad dada(se asume que existe ese nivel de profundidad)
 */

int btree_nnodos_profundidad(BTree arbol, int profundidad);

/**
 * retorna la profundiad del nodo que contiene el núemro dado, -1 si el número no se encuentra en el arbol
 */
int btree_profundidad_dato(BTree arbol, void* dato, FuncionComparadora);

/**
 * retorna la suma de todos los datos del arbol
 */
int btree_sumar(BTree arbol);

void btree_recorrer_extra(BTree, BTreeOrdenDeRecorrido, FuncionVisitanteExtra, void*);

/**
 * imprime los valores de una profundidad dada
 */
void btree_valores_nivel(BTree, FuncionVisitante, int profundiad);
/**
 * recursive breadth first search
 */
void btree_recorrer_rbfs(BTree arbol, FuncionVisitante visit);

/**
 * breadth first search usanco colas; 
 * 
 */
void btree_recorrer_bfs(BTree arbol, FuncionVisitante visit, 
    FuncionCopia fcopia, FuncionDestructora fdestruir);

    /**
 * btree_mirror, espeja los nodos del arbol
 */

BTree  btree_mirror(BTree arbol);


/**
 * determina si el arbol es completo o no (es decir  sus niveles tienen todos los nodos posibles, excepto quizas
 el ultimo nivel, que se encuentra lleno de izquierda a derecha.)
 */
int btree_es_completo(BTree);
#endif /* __BTREE_H__ */
