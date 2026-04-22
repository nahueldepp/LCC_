#ifndef _G_COLAS_H_
#define _G_COLAS_H_
#include "../Practica 2/glist/glist.h"


typedef struct _Cola{
    GNode* inicio;//el inicio de la cola es el inicio de la lista
    GNode* final;//el fin de la cola es el fin de la lista, se agrega al final
}Cola;

Cola* cola_crear();

void cola_destruir(Cola* cola, FuncionDestructora funDestruir);

/**
 * retorna 1 si la cola esta vacia 0  en  caso contrario
 */
int cola_es_vacia(Cola* cola);

/**
 * que retorna el elemento que se encuentre en el inicio de la cola, sin eliminarlo
 */
void* cola_inicio(Cola* cola);

/**
 * Encola un elemento( lo coloca al principio de la lista)
 */
void cola_encolar(Cola* cola, void* dato, FuncionCopia copia);

void* cola_desencolar(Cola* cola, FuncionDestructora funDestruir, FuncionCopia funCopia);

void cola_imprimir(Cola* cola, FuncionVisitante funDestruir);



#endif