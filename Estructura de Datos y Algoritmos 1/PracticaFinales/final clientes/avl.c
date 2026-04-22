#include "avl.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * avl_crear: Retorna un arbol AVL vacio
 */
AVL avl_crear(FuncionCopiadora copia, FuncionComparadora comp,
  FuncionDestructora destr) {
  AVL arbol = malloc(sizeof(struct _AVL));
  assert(arbol != NULL);
  arbol->raiz = NULL;
  arbol->copia = copia;
  arbol->comp = comp;
  arbol->destr = destr;
  return arbol;
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
static AVL_Nodo* avl_nodo_rotacion_simple_izq(AVL_Nodo* raiz) {
  AVL_Nodo* hijoDer = raiz->der;
  assert(hijoDer != NULL);
  // actualizar punteros
  raiz->der = hijoDer->izq;
  hijoDer->izq = raiz;
  // actualizar alturas
  raiz->altura = 1 + avl_nodo_max_altura_hijos(raiz);
  hijoDer->altura = 1 + avl_nodo_max_altura_hijos(hijoDer);
  return hijoDer;
}

/**
 * avl_nodo_rotacion_simple_der: Funcion interna que realiza una rotacion simple
 * a derecha y retorna la nueva raiz.
 */
static AVL_Nodo* avl_nodo_rotacion_simple_der(AVL_Nodo* raiz) {
  
  AVL_Nodo* hijoIzq= raiz->izq;
  assert(hijoIzq != NULL);
  //cambio de punteros
  raiz->izq= hijoIzq->der;
  hijoIzq->der= raiz;
  //modificacion de alturas
  raiz->altura= 1 + avl_nodo_max_altura_hijos(raiz);
  hijoIzq->altura= 1 + avl_nodo_max_altura_hijos(hijoIzq);

  return hijoIzq;
}

/**
 * avl_nodo_crear: Funcion interna que crea un nuevo nodo y lo retorna.
 * La altura de un nodo hoja es 0.
 */
static AVL_Nodo* avl_nodo_crear(void* dato, FuncionCopiadora copia) {
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
  FuncionCopiadora copia, FuncionComparadora comp) {
  if (raiz == NULL) // insertamos el nuevo elemento
    return avl_nodo_crear(dato, copia);
  else if (comp(dato, raiz->dato) < 0) { // el dato debe ir en el subarbol izq
    raiz->izq = avl_nodo_insertar(raiz->izq, dato, copia, comp);
    // chequear balance
    if (avl_nodo_factor_balance(raiz) == -2) {
      // casos 1 o 2
      if (avl_nodo_factor_balance(raiz->izq) == 1) // caso 2
        raiz->izq = avl_nodo_rotacion_simple_izq(raiz->izq);
      raiz = avl_nodo_rotacion_simple_der(raiz); // caso 1
    }
    raiz->altura = 1 + avl_nodo_max_altura_hijos(raiz);
    return raiz;
    
  }
  else if (comp(dato,raiz->dato) > 0) { // el dato debe ir en el subarbol der
    //pesado a la derecha
    raiz->der = avl_nodo_insertar(raiz->der, dato, copia, comp);
    if(avl_nodo_factor_balance(raiz) == 2){
      //se la insercion fue interna
      if(avl_nodo_factor_balance(raiz->der)== -1)
      raiz->der= avl_nodo_rotacion_simple_der(raiz->der);
      raiz= avl_nodo_rotacion_simple_izq(raiz);
    }
    raiz->altura = 1 + avl_nodo_max_altura_hijos(raiz);
    
    return raiz;
  }
  
    return raiz;
}
void avl_insertar(AVL arbol, void* dato) {
  arbol->raiz = avl_nodo_insertar(arbol->raiz, dato, arbol->copia, arbol->comp);
}

/**
 * avl_validar: Retorna 1 si el arbol cumple la propiedad de los arboles AVL,
 * y 0 en caso contrario.
 * avl_nodo_validar_abb: Funcion interna que retorna 1 si el arbol cumple la
 * propiedad de los arboles BB, y 0 en caso contrario.
 * avl_nodo_validar_altura_y_balance: Funcion interna que retorna 1 si la
 * altura y el factor de balance de los nodos son correctos, y 0 en caso
 * contrario.
 */
static int avl_nodo_validar_abb(AVL_Nodo* raiz, void* min, void* max,
  FuncionComparadora comp) {
  // si la raiz es vacia, retornar exitosamente
  if (raiz == NULL)
    return 1;
  else {
    // sino, validar intervalo
    if (min != NULL && comp(raiz->dato, min) <= 0)
      return 0;
    if (max != NULL && comp(max, raiz->dato) <= 0)
      return 0;
    // y validar subarboles recursivamente
    return (avl_nodo_validar_abb(raiz->izq, min, raiz->dato, comp) &&
      avl_nodo_validar_abb(raiz->der, raiz->dato, max, comp));
  }
}
static int avl_nodo_validar_altura_y_balance(AVL_Nodo* raiz) {
  // si la raiz es vacia, retornar exitosamente
  if (raiz == NULL)
    return 1;
  // sino, validar subarboles recursivamente
  int ret1 = avl_nodo_validar_altura_y_balance(raiz->izq);
  int ret2 = avl_nodo_validar_altura_y_balance(raiz->der);
  if (ret1 && ret2) {
    // si ambos subarboles son validos, validar altura y balance de raiz
    int altura = 1 + avl_nodo_max_altura_hijos(raiz);
    int balance = avl_nodo_factor_balance(raiz);
    if ((raiz->altura == altura) && (balance >= -1) && (balance <= 1))
      return 1;
  }
  // en cualquier otro caso, retornar falso
  return 0;
}
int avl_validar(AVL arbol) {
  return (avl_nodo_validar_altura_y_balance(arbol->raiz) &&
    avl_nodo_validar_abb(arbol->raiz, NULL, NULL, arbol->comp));
}

/**
 * avl_recorrer: Recorrido DSF del arbol
 */
static void avl_nodo_recorrer(AVL_Nodo* raiz, AVLRecorrido orden,
  FuncionVisitante visita) {
  if (raiz != NULL) {
    if (orden == AVL_RECORRIDO_PRE)
      visita(raiz->dato);
    avl_nodo_recorrer(raiz->izq, orden, visita);
    if (orden == AVL_RECORRIDO_IN)
      visita(raiz->dato);
    avl_nodo_recorrer(raiz->der, orden, visita);
    if (orden == AVL_RECORRIDO_POST)
      visita(raiz->dato);
  }
}
void avl_recorrer(AVL arbol, AVLRecorrido orden, FuncionVisitante visita) {
  avl_nodo_recorrer(arbol->raiz, orden, visita);
}

/**
 * Retorna un puntero al minimo elemento de un arbol
 */
static AVL_Nodo* avl_nodo_minimo(AVL_Nodo* root){

  assert(root != NULL);
  
  AVL_Nodo* minimo;
  for(minimo= root; minimo->izq !=NULL; minimo= minimo->izq);
  return minimo;
}

static AVL_Nodo* avl_nodo_eliminar(AVL_Nodo* root, void*dato, FuncionComparadora comp, FuncionDestructora destr, FuncionCopiadora copi){
  if (root == NULL)
    return root;
    
  else if (comp(dato, root->dato) < 0){
    // dato < raiz->dato
    root->izq= avl_nodo_eliminar(root->izq, dato,comp, destr,copi);
    // chequear balance
  }
  
  else if(comp(dato, root->dato)>0) // raiz->dato < dato
    root->der= avl_nodo_eliminar(root->der, dato,comp, destr,copi);
  else if(comp(dato,root->dato)==0){
    //El nodo a eliminar tiene 2 hijos
    if(root->der && root->izq){
      AVL_Nodo* minimo= avl_nodo_minimo(root->der);
      destr(root->dato);
      root->dato= copi(minimo->dato);
      root->der=avl_nodo_eliminar(root->der,root->dato,comp, destr, copi);
      return root;
    }
    //el nodo es una hoja o tiene un hijo
    else{
      AVL_Nodo* sucesor= root->der ==NULL?root->izq:root->der;
      destr(root->dato);
      free(root);
      return sucesor;
    }

  }

  if (avl_nodo_factor_balance(root) == -2) {
      // casos 1 o 2
      if (avl_nodo_factor_balance(root->izq) == 1) // caso 2
        root->izq = avl_nodo_rotacion_simple_izq(root->izq);
      root = avl_nodo_rotacion_simple_der(root); // caso 1
    }
  else if(avl_nodo_factor_balance(root) == 2){
      //se la insercion fue interna
      if(avl_nodo_factor_balance(root->der)== -1)
      root->der= avl_nodo_rotacion_simple_der(root->der);
      root= avl_nodo_rotacion_simple_izq(root);
    }
  root->altura = 1 + avl_nodo_max_altura_hijos(root);
  return root;
}

void avl_eliminar(AVL arbol, void* dato){

  arbol->raiz= avl_nodo_eliminar(arbol->raiz,dato,arbol->comp,arbol->destr,arbol->copia);
}



