#include <stdio.h>
#include <stdlib.h>
#include "gcolas.h"
#include "../Practica 2/glist/contacto.h"


Cola* cola_crear(){
    Cola* nuevaCola= malloc(sizeof(Cola));
    nuevaCola->inicio= NULL;
    nuevaCola->final=NULL;
    
    return nuevaCola;
}

void cola_destruir(Cola* cola, FuncionDestructora funDestruir){
    glist_destruir(cola->inicio,(FuncionDestructora) funDestruir);
    free(cola);
}

/**
* retorna 1 si la cola esta vacia 0  en  caso contrario
 */
int cola_es_vacia(Cola* cola){
    return cola->inicio == NULL;
}

/**
 * que retorna el elemento que se encuentre en el inicio de la cola, sin eliminarlo
 */
void* cola_inicio(Cola* cola){
    return cola->inicio;
}

/**
 * Encola un elemento( lo coloca al inicio de la lista)
 */
void cola_encolar(Cola* cola, void* dato, FuncionCopia funCopia){
    if(cola_es_vacia(cola)){
        cola->inicio= glist_agregar_inicio(cola->inicio, dato, (FuncionCopia) funCopia);
        cola->final= cola->inicio;
    }
    else{
        cola->final=glist_agregar_final(cola->final,dato, (FuncionCopia) funCopia); 
    }
}

void* cola_desencolar(Cola* cola, FuncionDestructora funDestruir, FuncionCopia funCopia){

    GNode* nodoAdesencolar= cola->inicio;
    void* dato= funCopia(cola->inicio->data);
    cola->inicio= cola->inicio->next;
    funDestruir(nodoAdesencolar->data);
    free(nodoAdesencolar);
    return dato;

}

void cola_imprimir(Cola* cola, FuncionVisitante funVisitante){
    glist_recorrer(cola->inicio,(FuncionVisitante) funVisitante); 
}


int main(){
    
    Cola* cola= cola_crear();
    printf("vacia?%d\n", cola_es_vacia(cola));

    Contacto* contacto0;
    Contacto* contacto1;
    Contacto* contacto2;
    contacto0= contacto_crear("nahuel","155555",16);
    contacto1= contacto_crear("pepe","78878",65);
    contacto2= contacto_crear("juan","7558878",8);

    cola_encolar(cola, contacto0, (FuncionCopia) contacto_copia);
    cola_encolar(cola, contacto1, (FuncionCopia) contacto_copia);
    cola_encolar(cola, contacto2, (FuncionCopia) contacto_copia);

    cola_imprimir(cola, (FuncionVisitante) contacto_imprimir);
    puts("");
    contacto_imprimir(cola_desencolar(cola, (FuncionDestructora) contacto_destruir,(FuncionCopia) contacto_copia));

    cola_imprimir(cola, (FuncionVisitante) contacto_imprimir);

    cola_destruir(cola,(FuncionDestructora) contacto_destruir);
    //cola_imprimir(cola, (FuncionVisitante) contacto_imprimir);
    return 0;
}