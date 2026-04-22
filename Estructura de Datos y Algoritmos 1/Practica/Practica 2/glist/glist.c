#include "glist.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Devuelve una lista vacía.
 */
GList glist_crear() { return NULL; }

/**
 * Destruccion de la lista.
 * destroy es una función que libera el dato almacenado.
 */
void glist_destruir(GList list, FuncionDestructora destroy) {
  GNode *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    destroy(nodeToDelete->data);
    free(nodeToDelete);
  }
}

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList list) { return (list == NULL); }

/**
 * Agrega un elemento al inicio de la lista.
 * copy es una función que retorna una copia física del dato.
 */
GList glist_agregar_inicio(GList list, void *data, FuncionCopia copy) {
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->next = list;
  newNode->data = copy(data);
  return newNode;
}

/**
 * Agrega un elemento al final de la lista y devuelve un puntero al elemento
 */
GNode* glist_agregar_final(GList final, void *dato, FuncionCopia copiar){
  GNode* newNode= malloc(sizeof(GNode));
  newNode->data= copiar(dato);
  newNode->next= NULL;
  final->next= newNode;
  return newNode;
}

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */

void glist_recorrer(GList list, FuncionVisitante visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}


/**
 *Dada una lista general, retorna una nueva lista con los elementos que cumplen con el predicado.
 */
GList glist_filtrar(GList lista, FuncionCopia c, Predicado p){

  GList nuevaLista= glist_crear();

  for(GNode* node= lista; node != NULL; node= node->next ){
    if((node->data) && p(node->data)){
      
      nuevaLista= glist_agregar_inicio(nuevaLista, node->data,c);
    }
  }
  assert(nuevaLista != NULL);
  return nuevaLista;
}

/**
 * Retorna una lista vacia ordenada
 */
SGList sglist_crear(){ return NULL;}


/**
 * destruye una ista ordenada
 */
void sglist_destruir(SGList lista, FuncionDestructora funDes){

  GNode *nodoAeliminar;
  while(lista != NULL){
    nodoAeliminar= lista;
    lista= lista->next;
    funDes(nodoAeliminar->data);
    free(nodoAeliminar);
    nodoAeliminar= lista;
  }
}


/**
 * Determina si una lista ordenada esta vacia
 */
int sglist_vacia(SGList lista){
  return (lista == NULL);
}

/**
 * aplica la funcion visitante a cada elemento de la lista ordenada
 */
void sglist_recorrer(SGList lista, FuncionVisitante visitante ){

  for(GNode *nodo= lista; nodo; nodo= nodo->next ){
    visitante(nodo->data);
  }
}

/**
 * Inserta un nuevo dato en la lista ordenada.
 *  La funcion comparacion determina el criterio de ordenacion:
 *  Retorna un entero negativo si el primer argumento es menor que el segundo, 0 si son iguales
 *  y un entero positivo si el primer argumento es mayor que el segundo
 */
SGList sglist_insertar(SGList lista, void* data, FuncionCopia copia, FuncionComparadora comparar){

  GNode* nuevoNodo= malloc(sizeof(GNode));
  nuevoNodo->data= copia(data);

  if(lista == NULL || (comparar(data, lista->data) < 0) ){
    nuevoNodo->next= lista;
    return nuevoNodo;
  }

  GList temp= lista;
  GList tempAnterior;
  for(; (temp !=NULL) && (comparar(data, temp->data) > 0) ; ){
    tempAnterior= temp;
    temp= temp->next;
    
  }
  tempAnterior->next= nuevoNodo;
  nuevoNodo->next= temp;

  return lista;
}


/**
 *  busca un dato en la lista ordenada, retornando 1 si lo encuentra y 0 en caso contrario 
 * (aprovechar que la lista esta ordenada para hacer esta busqueda mas efciente).
 */
int sglist_buscar(GList lista, void* data, FuncionComparadora comparar){

  if(lista == NULL)
    return 0;
  else
    return !(comparar(lista->data,data) == 0);

  int valor=
    sglist_buscar(lista->next, data, comparar);
    return valor;
}

SGList sglist_arr(void **arreglo, int longArr, FuncionCopia funCopia, FuncionComparadora funComparar){

  SGList nuevaLista= sglist_crear();
  
  for(int i = 0; i < longArr; i++){
    
    nuevaLista= sglist_insertar(nuevaLista,arreglo[i],(FuncionCopia)funCopia,(FuncionComparadora)funComparar);
  }
  return nuevaLista;
}

