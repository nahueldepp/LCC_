#include "dlist.h"
#include <stdlib.h>
#include <stdio.h>

 

DList dlist_crear(){
    DList nuevaLista;
    nuevaLista.primero= NULL;
    nuevaLista.ultimo= nuevaLista.primero;

    return nuevaLista;
}

void dlist_destruir(DList lista){

    DNodo* nodoAdestruir;
    while(lista.primero != NULL){
        nodoAdestruir= lista.primero;
        lista.primero= lista.primero->sig;
        free(nodoAdestruir);
    }
}

DList dlist_agregar_inicio(DList lista, int dato){
    DNodo* nuevoNodo= malloc(sizeof(DNodo));
    nuevoNodo->dato= dato;
    nuevoNodo->sig= lista.primero;
    nuevoNodo->ant= NULL;

    if(lista.primero == NULL)
        lista.ultimo= nuevoNodo;

    if(lista.primero != NULL)
        lista.primero->ant=nuevoNodo;

    lista.primero= nuevoNodo;
    return lista;
}

DList dlist_agregar_final(DList lista, int dato){

    DNodo* nuevoNodo= malloc(sizeof(DNodo));
    
    nuevoNodo->ant= lista.ultimo;
    nuevoNodo->sig= NULL;
    nuevoNodo->dato= dato;
    
    lista.ultimo->sig= nuevoNodo;
    lista.ultimo= nuevoNodo;
    return lista;
}

void dlist_recorrer(DList lista, FuncionVisitante func, int sentidoLista){

    if(sentidoLista == DLIST_RECORRIDO_HACIA_ADELANTE){
        for(DNodo *siguiente= lista.primero; siguiente != NULL; siguiente= siguiente->sig){
            func(siguiente->dato);
        }
    }
    else{
        for(DNodo *anterior= lista.ultimo; anterior != NULL; anterior= anterior->ant){
            func(anterior->dato);
        }
    }
}

int slist_longitud(DList lista){

    int i=0;
    for(DNodo* siguiente= lista.primero; siguiente != NULL; siguiente= siguiente->sig, i++);

    return i;
}