
#include "../Practica 2/glist/contacto.h"
#include "glistpila.h"
#include <stdlib.h>
#include <stdio.h>



//pilas de listas simplemente enlazadas generales

Pila pila_crear(){
    return NULL;
}

void pila_destruir(Pila pila,FuncionDestructora destruir){
    glist_destruir(pila, (FuncionDestructora) destruir);
}

/**
 * retorna 1 si la pila est´a vac´ıa, y 0 en caso contrario.
 */
int pila_es_vacia(Pila pila){
   return glist_vacia(pila);
}

/**
 *  retorna el elemento que se encuentre en el tope de la pila, pero sin
eliminarlo.
 */
void* pila_tope(Pila pila){
    return pila->data;
}

void pila_apilar(Pila* pila, void* dato, FuncionCopia copiar){
    *pila=glist_agregar_inicio(*pila, dato,(FuncionCopia) copiar);
    
}

void* pila_desapilar(Pila* pila, FuncionDestructora funDes, FuncionCopia funCop){
    GNode* nodoAeliminar= *pila;
    void* dato=funCop((*pila)->data);
    *pila= (*pila)->next;
    funDes(nodoAeliminar->data);
    free(nodoAeliminar);
    return dato;
}

void pila_imprimir(Pila pila, FuncionVisitante imprimir){
    glist_recorrer(pila,(FuncionVisitante) imprimir);
}

GList pila_revertir_lista(GList lista,FuncionCopia copiar, FuncionDestructora destruir){
    Pila pila= pila_crear();
    while(lista != NULL){
        pila_apilar(&pila,lista->data,(FuncionCopia)copiar);
        lista= lista->next;
    }
    glist_destruir(lista,(FuncionDestructora) destruir);
    return pila;
}

int main(){

    Contacto* contacto0;
    Contacto* contacto1;
    contacto0= contacto_crear("nahuel","155555",16);
    contacto1= contacto_crear("pepe","78878",65);
    GList lista= glist_crear();
    lista= glist_agregar_inicio(lista, contacto1, (FuncionCopia) contacto_copia);
    lista= glist_agregar_inicio(lista, contacto0, (FuncionCopia) contacto_copia);
    glist_recorrer(lista, (FuncionVisitante)contacto_imprimir);
    lista= pila_revertir_lista(lista,(FuncionCopia) contacto_copia, (FuncionDestructora) contacto_destruir);
    glist_recorrer(lista, (FuncionVisitante)contacto_imprimir);

    printf("av\n");
    Pila nuevaPila= pila_crear();
    
    
    pila_apilar(&nuevaPila,contacto0,(FuncionCopia)contacto_copia);
    pila_apilar(&nuevaPila,contacto1,(FuncionCopia)contacto_copia);
    contacto_imprimir(pila_tope(nuevaPila));
    
    printf("A\n");
    pila_imprimir(nuevaPila,(FuncionVisitante)contacto_imprimir);
    contacto_imprimir(pila_desapilar(&nuevaPila,(FuncionDestructora) contacto_destruir, (FuncionCopia) contacto_copia));
    pila_imprimir(nuevaPila,(FuncionVisitante)contacto_imprimir);

    return 0;
}