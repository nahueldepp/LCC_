#include <stdlib.h>
#include <stdio.h>
#include "final4tabla.h"

typedef struct {
    void *dato;
    int estado; //
} CasillaHash;

TablaHash tabla_crear(FuncionCopiadora copia, FuncionComparadora comp, FuncionDestructora destr, FuncionHash hash1){
    
    TablaHash nuevaTabla= malloc(sizeof(struct _TablaHash));
    nuevaTabla->capacidad= TAM_TABLA;
    nuevaTabla->numElems= 0;
    nuevaTabla->elems= malloc(sizeof(CasillaHash)*nuevaTabla->capacidad);
    nuevaTabla->copia= copia;
    nuevaTabla->comp= comp;
    nuevaTabla->hash1= hash1;
    //nuevaTabla->hash2= hash2;
    nuevaTabla->destr= destr;
    for(unsigned i = 0; i< nuevaTabla->capacidad;i++){
        nuevaTabla->elems[i].dato=NULL;
    }
    return nuevaTabla;

}


/**
 * tabla_insertar(): TablaHash void*-> void
 * usando LINEAR PROBING inserta un dato
 */
void tabla_insertar(TablaHash tabla, void* dato){

    float loadFactor= tabla->numElems /(float) tabla->capacidad;
    if(loadFactor>=0.75){
        printf("LOADFACTOR %f\n", loadFactor);
        tabla_rehash(tabla);
    }
    unsigned idx= tabla->hash1(dato) % tabla->capacidad;
    if(tabla->elems[idx].dato == NULL){
        tabla->elems[idx].dato= tabla->copia(dato);
        tabla->elems[idx].estado= !ELIMINADO;
        tabla->numElems++;
        return;
    }
    //la casilla encontrada contiene el mismo dato (se pisa) o contiene un dato eliminado(tambien se pisa)
    else if(tabla->comp(tabla->elems[idx].dato,dato)==0 || tabla->elems[idx].estado==ELIMINADO){
        tabla->destr(tabla->elems[idx].dato);
        tabla->elems[idx].dato= tabla->copia(dato);
        //como los elementos eliminados siguen contando como elementos, no se suman
        return;
    }
    //hay una colision
    else{
        int lugarEncontrado=0;
        for(unsigned i = 1; i< tabla->capacidad && !lugarEncontrado  ; i++){
            idx= (tabla->hash1(dato) + i) % tabla->capacidad;
            if(tabla->elems[idx].dato == NULL){
                tabla->elems[idx].dato= tabla->copia(dato);
                tabla->elems[idx].estado= !ELIMINADO;
                tabla->numElems++;
                lugarEncontrado=1;
            }
            else if(tabla->comp(tabla->elems[idx].dato,dato)==0 || tabla->elems[idx].estado==ELIMINADO){
                tabla->destr(tabla->elems[idx].dato);
                tabla->elems[idx].dato= tabla->copia(dato);
                lugarEncontrado=1;
            }
        }
        return;
    }

}

void* tabla_buscar(TablaHash tabla, void* dato){

    ;
    void* direccion= NULL;
    for(unsigned idx = (tabla->hash1(dato)) % tabla->capacidad; tabla->elems[idx].dato!=NULL && idx < tabla->capacidad && !direccion ;idx++){
        if(tabla->elems[idx].estado!= ELIMINADO && tabla->comp(tabla->elems[idx].dato,dato)==0){
            direccion = tabla->elems[idx].dato;
        }
        
    }
    return direccion;
}

void tabla_eliminar(TablaHash tabla, void* dato){
    
    unsigned idx = (tabla->hash1(dato)) % tabla->numElems;
    void* direccion= NULL;
    for(unsigned i=1; tabla->elems[idx].dato!=NULL && i < tabla->numElems && !direccion ;i++){
        if(tabla->elems[idx].estado!= ELIMINADO && tabla->comp(tabla->elems[idx].dato,dato)==0){
            direccion = tabla->elems[idx].dato;
        }
        idx= (tabla->hash1(dato)+i) % tabla->numElems;
    }
    idx--;
    if(direccion == NULL )
        return;
    else {
        tabla->elems[idx].estado= ELIMINADO;
        return;
    }

    
}

void tabla_rehash(TablaHash tabla){

    int viejaCapacidad= tabla->capacidad;
    CasillaHash* viejoArray=  tabla->elems;

    tabla->capacidad= tabla->capacidad * 2;
    tabla->elems= malloc(sizeof(CasillaHash)*tabla->capacidad);
    tabla->numElems = 0;
    for(unsigned i = 0; i< tabla->capacidad;i++){
        tabla->elems[i].dato=NULL;
    }
    for(int i=0; i< viejaCapacidad; i++){
        if(viejoArray[i].dato!= NULL && viejoArray[i].estado != ELIMINADO){
            tabla_insertar(tabla, viejoArray[i].dato);
            tabla->destr(viejoArray[i].dato);
        }
        else if(viejoArray[i].dato!= NULL){
            tabla->destr(viejoArray[i].dato);
        }
        
    }
    free(viejoArray);
    return;
}

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