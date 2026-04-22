#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>



/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                          FuncionComparadora comp, FuncionDestructora destr,
                          FuncionHash hash) {

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
 * Crea un nuevo array con el doble de capacidad reinsertado los elementos en el mismo
 */
void tablahash_rehash(TablaHash tabla){

  //se guarda la vieja tabla para su uso posterios
  CasillaHash* viejoArr= tabla->elems;
  unsigned viejaCapacidad= tabla->capacidad;
  //se modifica la capacidad de la tabla y se crea e inicializa una nueva
  tabla->capacidad= tabla->capacidad*2;
  tabla->elems= malloc(sizeof(CasillaHash)* tabla->capacidad);
  tabla->numElems=0;
  for(unsigned i=0; i<tabla->capacidad; i++){

    tabla->elems[i].dato= NULL;
  }

  //se insertan los elementos en la nueva tabla de hash
  for(unsigned idx=0; idx < viejaCapacidad; idx++){

    if(viejoArr[idx].dato!=NULL){
      tablahash_insertar(tabla,viejoArr[idx].dato);
      tabla->destr(viejoArr[idx].dato);
    }
  }
  free(viejoArr);

  return;

}

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 * Para tratar las colisiones se Linear Probing
 */
void tablahash_insertar(TablaHash tabla, void *dato) {

  //se calcula el balancefactor
  float balanceFactor= (tabla->numElems+1)/(float)tabla->capacidad;
  if(balanceFactor >= 0.75){
    tablahash_rehash(tabla);
  }
  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Insertar el dato si la casilla estaba libre.
  if (tabla->elems[idx].dato == NULL) {
    tabla->numElems++;
    tabla->elems[idx].dato = tabla->copia(dato);
    return;
  }
  // Sobrescribir el dato si el mismo ya se encontraba en la tabla.
  else if (tabla->comp(tabla->elems[idx].dato, dato) == 0) {
    tabla->destr(tabla->elems[idx].dato);
    tabla->elems[idx].dato = tabla->copia(dato);
    return;
  }
  // No hacer nada si hay colision.
  else {
    int posLibre= 0;
    for(unsigned i = idx + 1 ; i< tabla->capacidad && !posLibre<0;i++){
      if(tabla->elems[i].dato == NULL){
        tabla->elems[i].dato= tabla->copia(dato);
        posLibre=1;
      }
    }
    return;
  }
}

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void *tablahash_buscar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Retornar NULL si la casilla estaba vacia.
  if (tabla->elems[idx].dato == NULL)
    return NULL;
  // Retornar el dato de la casilla si hay concidencia.
  else if (tabla->comp(tabla->elems[idx].dato, dato) == 0)
    return tabla->elems[idx].dato;
  // Retornar NULL en otro caso.
  else{
    void* encontado= NULL;
    int casillaNula=0;
    for(unsigned i= idx+1; i<tabla->capacidad && !casillaNula && !encontado ; i++ ){
      //al ser linear probing, si se encuentra una casilla nula a partir del indice dado entonces el elemento no se encuentra
      if (tabla->elems[i].dato == NULL)
        casillaNula=1;
      // 
      else if (tabla->comp(tabla->elems[i].dato, dato) == 0)
        encontado= tabla->elems[i].dato;
    }
    return encontado;
  }
    return NULL;
}

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Retornar si la casilla estaba vacia.
  if (tabla->elems[idx].dato == NULL)
    return;
  // Vaciar la casilla si hay coincidencia.
  else if (tabla->comp(tabla->elems[idx].dato, dato) == 0) {
    tabla->numElems--;
    tabla->destr(tabla->elems[idx].dato);
    tabla->elems[idx].dato = NULL;
    return;
  }
  else{
    int casillaNula=0;
    for(unsigned i= idx+1; i<tabla->capacidad && !casillaNula ; i++ ){
      //al ser linear probing, si se encuentra una casilla nula a partir del indice dado entonces el elemento no se encuentra
      if (tabla->elems[i].dato == NULL)
        casillaNula=1;
      // 
      else if (tabla->comp(tabla->elems[i].dato, dato) == 0){
        tabla->destr( tabla->elems[i].dato);
        tabla->elems[i].dato=NULL;
        casillaNula=1;
      }
    }
    return ;
  }
}

