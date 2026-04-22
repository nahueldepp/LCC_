#include "colas.h"
#include <stdlib.h>
#include <stdio.h>


/**
 * Estructura de cola circular usando arrays;
 */
struct _Cola{
    void** datos;
    int frente;//posicion el elemento en el frente
    int final;//posicion del elemento del final
    FuncionCopia copi;
    FuncionDestructora destr;
};

/**
 * Crea una cola vacia
 */
Cola cola_crear(FuncionCopia copia, FuncionDestructora destr){
    Cola cola= malloc(sizeof(struct _Cola));
    cola->final=-1;
    cola->frente= -1;
    cola->destr= destr;
    cola->copi= copia;
    cola->datos= malloc(sizeof(void*)* MAX_COLA);
    return cola;
}

/**
 * Agrega un elemento a la cola
 */
void cola_enqueue(Cola cola, void* dato){
    if((cola->final + 1)%MAX_COLA == cola->frente ){
        return;
    }
    if(cola->frente == -1){
        cola->frente= 0;
    }
    cola->final= ++cola->final %MAX_COLA;
    if(cola->datos[cola->final] != NULL){
        cola->destr(cola->datos[cola->final]);
        cola->datos[cola->final]=NULL;
    } 
    cola->datos[cola->final]= cola->copi(dato);
    return;
}

/**
 * Desencola el elemento al frente de la cola
 */

void* cola_dequeue(Cola cola, void* dato){
    void* datoCola= NULL;
    //la cola esta vacia
    if(cola->frente == -1)  
        return datoCola;
    datoCola= cola->datos[cola->frente];
    if(cola->final == cola->frente){
        cola->final= -1;
        cola->frente = -1;
    }
    else
        cola->frente= ++cola->frente % MAX_COLA;
    return datoCola;

}

/**
 * Retorna 1 si la cola esta vacia, 0 en caso contrario
 */
int cola_isEmpty(Cola);