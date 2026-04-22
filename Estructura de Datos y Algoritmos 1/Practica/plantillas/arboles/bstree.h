#ifndef __BSTREE_H__
#define __BSTREE_H__

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitanteExtra)(void *dato, void *extra);

typedef enum {
  BTREE_RECORRIDO_IN,  /** Inorden */
  BTREE_RECORRIDO_PRE, /** Preorden */
  BTREE_RECORRIDO_POST /** Postorden */
} BSTreeRecorrido;

typedef struct _BST_Nodo{
    void* data;
    struct _BST_Nodo *izq, *der;
}_BST_Nodo;

typedef struct _BST_Nodo *BSTree;

/**
 * Retorna un arbol de busqueda binaria vacio.
 */
BSTree bstree_crear();

/**
 * Destruye el arbol y sus datos.
 */
void bstree_destruir(BSTree, FuncionDestructora);

/**
 * Retorna 1 si el dato se encuentra y 0 en caso contrario.
 */
int bstree_buscar(BSTree, void *, FuncionComparadora);

/**
 * Inserta un dato no repetido en el arbol, manteniendo la propiedad del arbol
 * de busqueda binaria.
 */
BSTree bstree_insertar(BSTree, void *, FuncionCopiadora, FuncionComparadora);

/**
 * Recorrido DSF del arbol
 */
void bstree_recorrer(BSTree, BSTreeRecorrido, FuncionVisitanteExtra,
                     void *extra);

BSTree bstree_eliminar(BSTree arbol, void *dato,
FuncionComparadora, FuncionDestructora);


/**
 * retorna el minimo elemento del lado derecho del arbol
 */
BSTree bstree_minimo_derecho(BSTree arbol);

/**
 *  retorna el k-esimo menor elemento del ABB
 */
BSTree bstree_k_esimo_menor(BSTree arbol, int k);


/**
 * determina si un ABB es valido
 */

 int bstree_ABB_valido(BSTree arbol, FuncionComparadora );
#endif //__BSTREE_H__