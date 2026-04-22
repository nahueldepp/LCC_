#ifndef _PILAS_H
#define _PILAS_H
#include "arregloenteros.h"
struct _Pila{
    ArregloEnteros* arr;
    int ultimaPos;
};
typedef struct _Pila* Pila;
//pilas de entetros

Pila pila_crear(int capacidad);

void pila_destruir(Pila pila);

int pila_es_vacia(Pila pila);

int pila_tope(Pila pila);

void pila_apilar(Pila pila, int x);

void pila_desapilar(Pila pila);

void pila_imprimir(Pila pila);
#endif