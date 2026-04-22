#include "pilas.h"
#include <stdlib.h>
#include <stdio.h>


/**
 * Crea una pila vacia
 */
Pila pila_crear(FuncionCopia copia, FuncionDestructora destr){
    Pila nuevaPila= malloc(sizeof(_Pila));
    nuevaPila->datos.capacidad= MAX_PILA;
    nuevaPila->datos.arreglo= malloc(sizeof(void*)* MAX_PILA);
    nuevaPila->topePila= -1;
    nuevaPila->copi= copia;
    nuevaPila->destr= destr;
    for(unsigned i= 0; i< MAX_PILA; i++){
        nuevaPila->datos.arreglo[i]= NULL;
    }
    return nuevaPila;
}


/**
 * Agrega un  elemento a la pila
 */
void pila_push(Pila pila, void* dato ){

    //si la pila no es del tamaño sufieciente
    if(pila->topePila +1 == pila->datos.capacidad){
        pila->datos.capacidad*=2;
        pila->datos.arreglo= realloc(pila->datos.arreglo, pila->datos.capacidad);
    }

    if(pila->datos.arreglo[pila->topePila + 1] != NULL)
        pila->destr(pila->datos.arreglo[pila->topePila + 1]);
    pila->datos.arreglo[++pila->topePila]= pila->copi(dato);
}

/**
 * Retorna el elemento en el tope de la pila
 * Reduce en 1 topePila, sin eliminar el elemento, habilita a ser pisado mas tarde
 */
void* pila_pop(Pila pila){

    if( pila->topePila == -1 )
        return NULL;
    return pila->datos.arreglo[pila->topePila--];
}


void pila_destruir(Pila pila){
    if(pila->topePila == -1)
        return;
    for(unsigned i=0; i< pila->datos.capacidad; i++ ){
        if(pila->datos.arreglo[i] != NULL){
            pila->destr(pila->datos.arreglo[i]);
        }
    }
    free(pila->datos.arreglo);
    free(pila);
    return;
}