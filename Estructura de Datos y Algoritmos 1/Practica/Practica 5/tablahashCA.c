#include "tablahash.h"
#include "listas.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXLOADFACTOR 0.66
/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef GNode* CasillaHash;


/**
 * Estructura principal que representa la tabla hash.
 */
struct _TablaHash {
  CasillaHash *elems;
  unsigned numElems;
  unsigned capacidad;
  float loadFactor;
  FuncionCopiadora copia;
  FuncionComparadora comp;
  FuncionDestructora destr;
  FuncionHash hash;
};

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                          FuncionComparadora comp, FuncionDestructora destr,
                          FuncionHash hash,FuncionHash hash2) {

  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla != NULL);
  tabla->elems = malloc(sizeof(CasillaHash) * capacidad);
  assert(tabla->elems != NULL);
  tabla->numElems = 0;
  tabla->capacidad = capacidad;
  tabla->copia = copia;
  tabla->comp = comp;
  tabla->destr = destr;
  tabla->hash = hash;
  tabla->loadFactor=0;

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->elems[idx] == NULL;
    
  }
  printf("%p\n", tabla->elems[0]);

  return tabla;
}

/**
 * Retorna el numero de elementos de la tabla.
 */
int tablahash_nelems(TablaHash tabla) { return tabla->numElems; }

/**
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla) { return tabla->capacidad; }

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla) {

  // Destruir cada uno de los datos.
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx){
    if (tabla->elems[idx]){
      glist_destruir(tabla->elems[idx],tabla->destr);
      
    }
  }

  // Liberar el arreglo de casillas y la tabla.
  free(tabla->elems);
  free(tabla);
  return;
}

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 * IMPORTANTE: Las colisiones se manejan usando closed adressing, usando listas simplemente enlazadas
 */
void tablahash_insertar(TablaHash tabla, void *dato) {

  
  if(tabla->loadFactor >= MAXLOADFACTOR){
    tablahash_rehash(tabla);
  }

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  
  // Insertar el dato si la casilla estaba libre.
  if (tabla->elems[idx] == NULL) {
    tabla->numElems++;
    tabla->elems[idx]=glist_agregar_inicio(tabla->elems[idx], dato, tabla->copia);
    tabla->loadFactor= tabla->numElems/(float)tabla->capacidad;
    
    
  }
  // Sobrescribir el dato si el mismo ya se encontraba en la tabla.
  else if (tabla->comp(tabla->elems[idx]->data, dato) == 0) {
    tabla->destr(tabla->elems[idx]->data);
    tabla->elems[idx]->data = tabla->copia(dato);
    
  }
  // 
  else {
    GNode* temp= glist_buscar(tabla->elems[idx]->next, tabla->comp, dato);
    if(temp == NULL)
      tabla->elems[idx]->next= glist_agregar_inicio(tabla->elems[idx]->next, dato, tabla->copia);
    else{
      tabla->destr(temp->data);
      temp->data= tabla->copia(dato);
    }
  }
  return;
}


/**
 * duplica la capacidad de la tabla y reposiciona todos los elementos segun la funcion hash
 */
void tablahash_rehash(TablaHash tabla){

  CasillaHash* viejaTabla= tabla->elems;
  unsigned viejaCapacidad= tabla->capacidad;

  //se crea la nueva tabla
  unsigned nuevaCapacidad= 2* viejaCapacidad;
  CasillaHash* nuevaTabla= malloc(sizeof(CasillaHash)*(nuevaCapacidad));
  assert(nuevaTabla != NULL);
  tabla->capacidad= nuevaCapacidad;
  tabla->elems= nuevaTabla;
  tabla->loadFactor= tabla->numElems/(float)tabla->capacidad;
  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx) {
    tabla->elems[idx] = NULL;
  }
  
  for(int idx=0; idx < viejaCapacidad; idx++){
    if(viejaTabla[idx] != NULL){
      GNode* temp= viejaTabla[idx];
      while(temp!=NULL){
        tablahash_insertar(tabla, temp->data);
      }
    }
  }
  // Destruir cada uno de los datos de la vieja tabla.
  for (unsigned idx = 0; idx < viejaCapacidad; ++idx){
    if (viejaTabla[idx]->next != NULL){
      glist_destruir(viejaTabla[idx],tabla->destr);
      
    }
  }
  free(viejaTabla);
  return;
}

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void *tablahash_buscar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Retornar NULL si la casilla estaba vacia.
  if (tabla->elems[idx] == NULL)
    return NULL;
  
  else{
    GNode* nodoBuscado= glist_buscar(tabla->elems[idx], tabla->comp, dato);
    return nodoBuscado==NULL?NULL: nodoBuscado->data;
  }
    
}

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Retornar si la casilla estaba vacia.
  if (tabla->elems[idx] == NULL)
    return;
  // Vaciar la casilla si hay coincidencia.
  else{
    if(tabla->comp(tabla->elems[idx]->data, dato) == 0)
      tabla->numElems--;
    tabla->elems[idx]= glist_eliminar_nodo(tabla->elems[idx], dato, tabla->comp, tabla->destr);
    return;
  }
}
