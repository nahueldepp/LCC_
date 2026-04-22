#include "pilas.h"
#include <stdlib.h>
#include <stdio.h>
//pilas de listas simplemente enlazadas generales

Pila pila_crear(){
    return NULL;
}

void pila_destruir(Pila pila,FuncionDestructora destruir){
    
    for(pila; pila != NULL;){
        GNode* nodoADestruir=pila;
        pila= pila->next;
        destruir(nodoADestruir);
        free(nodoADestruir);
    }
}

/**
 * retorna 1 si la pila est´a vac´ıa, y 0 en caso contrario.
 */
int pila_es_vacia(Pila pila){
   return pila == NULL;
}

/**
 *  retorna el elemento que se encuentre en el tope de la pila, pero sin
eliminarlo.
 */
void* pila_tope(Pila pila){
    return pila->data;
}

Pila pila_apilar(Pila pila, void* dato, FuncionCopia copiar){

    Pila nuevoDato= malloc(sizeof(GNode));
    nuevoDato->data= copiar(dato);
    nuevoDato->next= pila;
    return nuevoDato;
}

void* pila_desapilar(Pila* pila, FuncionDestructora funDes, FuncionCopia funCop){
    if(pila==NULL){
        return NULL;
    }
    GNode* nodoAeliminar= *pila;
    void* dato=funCop((*pila)->data);
    *pila= (*pila)->next;
    funDes(nodoAeliminar->data);
    free(nodoAeliminar);
    return dato;
}

void pila_imprimir(Pila pila, FuncionVisitante imprimir){

    for(GNode* nodo= pila; nodo->next != NULL; nodo= nodo->next){
        imprimir(nodo->data);
    }
}

Pila pila_revertir_lista(Pila lista,FuncionCopia copiar, FuncionDestructora destruir){
    Pila pila= pila_crear();
    while(lista != NULL){
        pila_apilar(pila,lista->data,(FuncionCopia)copiar);
        lista= lista->next;
    }
    pila_destruir(lista,(FuncionDestructora) destruir);
    return pila;
}
