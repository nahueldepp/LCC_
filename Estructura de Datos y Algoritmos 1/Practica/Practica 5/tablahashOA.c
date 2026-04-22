#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXLOADFACTOR 0.66
/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  void *dato;
} CasillaHash;

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
  FuncionHash hashH; // hash primaria
  FuncionHash hashS; // hash de paso
};


/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                          FuncionComparadora comp, FuncionDestructora destr,
                          FuncionHash hashH, FuncionHash hashS) {

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
  tabla->hashH = hashH;// hash primaria
  tabla->hashS= hashS;
  tabla->loadFactor= 0;

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->elems[idx].dato = NULL;
  }

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
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx)
    if (tabla->elems[idx].dato != NULL)
      tabla->destr(tabla->elems[idx].dato);

  // Liberar el arreglo de casillas y la tabla.
  free(tabla->elems);
  free(tabla);
  return;
}



/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 * Usando direccionamiento abierto (closed hashing/open adresing)
 * usando doble hashing
 */
void tablahash_insertar(TablaHash tabla, void *dato) {
  assert(dato != NULL);
  
  if(tabla->loadFactor >= MAXLOADFACTOR){
    tablahash_rehash(tabla);
  }
  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned hashval= tabla->hashH(dato);
  unsigned desplazamiento= tabla->hashS(dato);
  unsigned idx = hashval % tabla->capacidad;
  
  
  unsigned j= 1;
  //doble hashing
  while(tabla->elems[idx].dato != NULL && (tabla->comp(tabla->elems[idx].dato, dato) != 0)){
    idx= (hashval + j*desplazamiento) % tabla->capacidad;
    printf("%d\n", idx);
    j++;
  }

  // Insertar el dato si la casilla estaba libre.
  if (tabla->elems[idx].dato == NULL) {
    tabla->numElems++;
    tabla->elems[idx].dato = tabla->copia(dato);
    tabla->loadFactor= tabla->numElems/(float)tabla->capacidad;
    return;
  }
  // Sobrescribir el dato si el mismo ya se encontraba en la tabla.
  else{
    tabla->destr(tabla->elems[idx].dato);
    tabla->elems[idx].dato = tabla->copia(dato);
    return;
  }
  
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
    tabla->elems[idx].dato = NULL;
  }
  
  for(int idx=0; idx < viejaCapacidad; idx++){
    if(viejaTabla[idx].dato != NULL){
      tablahash_insertar(tabla, viejaTabla[idx].dato);
      tabla->destr(viejaTabla[idx].dato);
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
  unsigned hashval= tabla->hashH(dato);
  unsigned desplazamiento= tabla->hashS(dato);
  unsigned idx = hashval % tabla->capacidad;
  
  unsigned j= 1;
  void* encontrado= NULL;
  //doble hashing
  while(tabla->elems[idx].dato!=NULL && !encontrado){
    if((tabla->comp(tabla->elems[idx].dato,dato)==0))
      encontrado= tabla->elems[idx].dato;
    idx= (hashval + j*desplazamiento) % tabla->capacidad;
    j++;
  }
  printf("pos: %d\n", idx);
  return encontrado;
}

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato) {


  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned hashval= tabla->hashH(dato);
  unsigned desplazamiento= tabla->hashS(dato);
  unsigned idx = hashval % tabla->capacidad;
  
  unsigned j= 0;
  void* encontrado= NULL;
  //doble hashing
  while(tabla->elems[idx].dato!=NULL && !encontrado){
    idx= (hashval + j*desplazamiento) % tabla->capacidad;
    if((tabla->comp(tabla->elems[idx].dato,dato)==0)){
      encontrado= tabla->elems[idx].dato;
    }
    j++;
  }
  // Retornar si la casilla estaba vacia.
  if (encontrado == NULL)
    return;
  // Vaciar la casilla si hay coincidencia.
  else if (tabla->comp(tabla->elems[idx].dato, dato) == 0) {
    tabla->numElems--;
    tabla->destr(tabla->elems[idx].dato);
    tabla->elems[idx].dato = NULL;
    return;
  }
}
