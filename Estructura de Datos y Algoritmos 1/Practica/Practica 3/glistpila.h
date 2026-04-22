#ifndef _GLIST_PILA_
#define _GLIST_PILA_
#include "../Practica 2/glist/glist.h"


typedef GList Pila;

Pila pila_crear();

void pila_destruir(Pila pila,FuncionDestructora destruir);

/**
 * retorna 1 si la pila es vacia, 0 en caso contrario
 */
int pila_es_vacia(Pila pila);

/**
 * Devuelve el elemento del tope de la pila sin eleminarlo
 */
void* pila_tope(Pila pila);

/**
 * toma un puntero a pila (Pila*) y apila un nuevo dato
 */
void pila_apilar(Pila* pila, void* dato, FuncionCopia copiar);

/**
 * toma un punntero a pila y desapila un elemento
 */
void* pila_desapilar(Pila* pila, FuncionDestructora funDes, FuncionCopia funCop);


void pila_imprimir(Pila pila, FuncionVisitante imprimir);

GList pila_revertir_lista(GList lista,FuncionCopia copiar, FuncionDestructora destruir);

#endif