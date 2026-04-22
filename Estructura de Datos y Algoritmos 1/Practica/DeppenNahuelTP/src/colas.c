#include <stdio.h>
#include <stdlib.h>
#include "../cabeceras/colas.h"


Cola cola_crear(){
    Cola nuevaCola= malloc(sizeof(struct _Cola));
    nuevaCola->inicio= NULL;
    nuevaCola->final=nuevaCola->inicio;
    
    return nuevaCola;
}

void cola_destruir(Cola cola, FuncionDestructora funDestruir){

    while(cola->inicio != NULL){
        GNode* nodoAdestruir = cola->inicio;
        cola->inicio= cola->inicio->sig;
        funDestruir(nodoAdestruir->data);
        free(nodoAdestruir);
        
    }
    free(cola);
}

/**
 * retorna 1 si la cola esta vacia 0  en  caso contrario
 */
int cola_es_vacia(Cola cola){
    return cola->inicio == NULL;
}

/**
 * que retorna el elemento que se encuentre en el inicio de la cola, sin eliminarlo
 */
void* cola_inicio(Cola cola){
    return cola->inicio->data;
}

/**
 * Encola un elemento( lo coloca al final de la lista)
 */
Cola cola_encolar(Cola cola, void* dato, FuncionCopia funCopia){

    GNode* nuevoNodo = malloc(sizeof(GNode));
        nuevoNodo->data= funCopia(dato);
        nuevoNodo->sig= NULL;
    if(cola_es_vacia(cola)){
        cola->inicio= nuevoNodo;
        cola->final= nuevoNodo;
    }
    else{
        cola->final->sig = nuevoNodo;
        cola->final = nuevoNodo;
    }
    return cola;
}


void* cola_desencolar(Cola cola, FuncionDestructora funDestruir, FuncionCopia funCopia){

    if(cola_es_vacia(cola)) return NULL;

    GNode* nodoAdesencolar= cola->inicio;
    void* dato= funCopia(cola->inicio->data);
    cola->inicio= cola->inicio->sig;
    funDestruir(nodoAdesencolar->data);
    free(nodoAdesencolar);
    return dato;

}

void cola_imprimir(Cola cola, FuncionVisitante funVisitante){
    for(GNode* temp=cola->inicio; temp != NULL; temp= temp->sig){
        funVisitante(temp->data);
    }
}

Cola cola_copiar(Cola cola, FuncionCopia funCopia){

    Cola colaCopia=cola_crear();
    GNode* temp= cola->inicio;
    while(temp!= NULL){
        colaCopia= cola_encolar(colaCopia, temp->data, funCopia);
        temp= temp->sig;
    }
    return colaCopia;
}