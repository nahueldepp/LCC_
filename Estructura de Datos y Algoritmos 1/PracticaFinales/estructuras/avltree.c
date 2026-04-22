#include "avltree.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct avl_nodo{
    void* dato;
    struct avl_nodo* izq, *der;
    int altura;
}AVL_Nodo;

struct _AVL{
    struct AVL_Nodo* raiz;
    FuncionCopia copi;
    FuncionComparadora comp;
    FuncionDestructora destr;
};

AVL avl_crear(FuncionCopia copi, FuncionComparadora comp, FuncionDestructora destr){

    AVL arbol= malloc(sizeof(struct _AVL));
    arbol->copi= copi;
    arbol->comp=comp;
    arbol->destr= destr;
    arbol->raiz= NULL;
    
}

/**
 * avl_destruir: Destruye el arbol y sus datos.
 */
static void avl_nodo_destruir(AVL_Nodo* raiz, FuncionDestructora destr) {
  if (raiz != NULL) {
    // destruir los nodos en postorder
    avl_nodo_destruir(raiz->izq, destr);
    avl_nodo_destruir(raiz->der, destr);
    destr(raiz->dato);
    free(raiz);
  }
}
void avl_destruir(AVL arbol) {
  avl_nodo_destruir(arbol->raiz, arbol->destr);
  free(arbol);
}

/**
 * avl_buscar: Retorna 1 si el dato se encuentra y 0 en caso contrario
 */
static int avl_nodo_buscar(AVL_Nodo* raiz, FuncionComparadora comp,
  void* dato) {
  if (raiz == NULL)
    return 0;
  else if (comp(dato, raiz->dato) == 0) // raiz->dato == dato
    return 1;
  else if (comp(dato, raiz->dato) < 0) // dato < raiz->dato
    return avl_nodo_buscar(raiz->izq, comp, dato);
  else // raiz->dato < dato
    return avl_nodo_buscar(raiz->der, comp, dato);
}
int avl_buscar(AVL arbol, void* dato) {
  return avl_nodo_buscar(arbol->raiz, arbol->comp, dato);
}

/**
 * avl_nodo_altura: Funcion interna que retorna la altura del arbol.
 * La altura del arbol vacio se define como -1.
 */
static int avl_nodo_altura(AVL_Nodo* raiz) {
  return (raiz == NULL ? -1 : raiz->altura);
}

/**
 * avl_nodo_max_altura_hijos: Funcion interna que retorna la maxima altura de
 * los hijos.
 */
static unsigned int avl_nodo_max_altura_hijos(AVL_Nodo* raiz) {
  assert(raiz != NULL);
  int alturaIzq = avl_nodo_altura(raiz->izq);
  int alturaDer = avl_nodo_altura(raiz->der);
  return (alturaIzq < alturaDer ? alturaDer : alturaIzq);
}

/**
 * avl_nodo_factor_balance: Funcion interna que retorna el factor de balance de
 * un nodo.
 */
static int avl_nodo_factor_balance(AVL_Nodo* raiz) {
  assert(raiz != NULL);
  int factor = avl_nodo_altura(raiz->der) - avl_nodo_altura(raiz->izq);
  assert(-2 <= factor || factor <= 2);
  return factor;
}


/**
 * avl_nodo_rotacion_simple_izq: Funcion interna que realiza una rotacion simple
 * a izquierda y retorna la nueva raiz.
 */
static AVL_Nodo* avl_nodo_rotacion_simple_izq(AVL_Nodo* raiz){

    AVL_Nodo* hijoDer= raiz->der;
    
    raiz->der= hijoDer->izq;
    raiz->altura= 1 + avl_nodo_max_altura_hijos(raiz);
    hijoDer->izq= raiz;
    hijoDer->altura= 1 + avl_nodo_max_altura_hijos(hijoDer);
    return hijoDer;
}

/**
 * avl_nodo_rotacion_simple_izq: Funcion interna que realiza una rotacion simple
 * a izquierda y retorna la nueva raiz.
 */
static AVL_Nodo* avl_nodo_rotacion_simple_der(AVL_Nodo* raiz){

    AVL_Nodo* hijoIzq= raiz->izq;

    raiz->izq= hijoIzq->der;
    raiz->dato= 1+ avl_nodo_max_altura_hijos(raiz);
    hijoIzq->der= raiz;
    hijoIzq->altura= 1 + avl_nodo_max_altura_hijos(hijoIzq);

    return hijoIzq;

}

/**
 * avl_nodo_crear: Funcion interna que crea un nuevo nodo y lo retorna.
 * La altura de un nodo hoja es 0.
 */
static AVL_Nodo* avl_nodo_crear(void* dato, FuncionCopia copia) {
  AVL_Nodo* nuevoNodo = malloc(sizeof(AVL_Nodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = copia(dato);
  nuevoNodo->izq = nuevoNodo->der = NULL;
  nuevoNodo->altura = 0;
  return nuevoNodo;
}

/**
 * avl_insertar: Inserta un dato no repetido en el arbol, manteniendo la
 * propiedad de los arboles AVL.
 */
static AVL_Nodo* avl_nodo_insertar(AVL_Nodo* raiz, void* dato,
  FuncionCopia copia, FuncionComparadora comp) {
  if (raiz == NULL) // insertamos el nuevo elemento
    return avl_nodo_crear(dato, copia);
  else if (comp(dato, raiz->dato) < 0) { // el dato debe ir en el subarbol izq
    raiz->izq = avl_nodo_insertar(raiz->izq, dato, copia, comp);
    // chequear balance
    //pesado a la izquierda
    if (avl_nodo_factor_balance(raiz) == -2) {
      // casos 1 o 2
      //insersion interna a derecha
      if (avl_nodo_factor_balance(raiz->izq) == 1) // caso 2
        raiz->izq = avl_nodo_rotacion_simple_izq(raiz->izq);
      raiz = avl_nodo_rotacion_simple_der(raiz); // caso 1
    }
    raiz->altura = 1 + avl_nodo_max_altura_hijos(raiz);
    return raiz;
  }
  //
  else if (comp(raiz->dato, dato) < 0) { // el dato debe ir en el subarbol der
    raiz->der= avl_nodo_insertar(raiz->der,dato, copia, comp);
    //pesado a la derecha
    if(avl_nodo_factor_balance(raiz)==2){
        //insercion interna en el lado izquierdo
        if(avl_nodo_factor_balance(raiz->izq)==-1){
            avl_nodo_rotacion_simple_der(raiz->izq);
        }
        avl_nodo_rotacion_simple_izq(raiz);
    }
    return raiz;
  }
  else // no agregar elementos repetidos
    return raiz;
}
void avl_insertar(AVL arbol, void* dato) {
  arbol->raiz = avl_nodo_insertar(arbol->raiz, dato, arbol->copi, arbol->comp);
}