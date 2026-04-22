#ifndef __PILAS_H__
#define __PILAS_H__

typedef void* (*FuncionCopia)(void*);
typedef void (*FuncionDestructora)(void*);
typedef int (*FuncionComparadora)(void*);

#define MAX_PILA 20

typedef struct{
    void** arreglo;
    unsigned capacidad;
}ArregloGenerico;

/**
 * Estructura de pila pa elementos genericos 
 * usando un array 
 */
typedef struct _pila{
    ArregloGenerico datos;
    unsigned topePila;//representa la posicion del ultimo elemento agregado
    FuncionCopia copi;
    FuncionDestructora destr;
}_Pila;

typedef _Pila* Pila;

/**
 * Crea una pila vacia
 */
Pila pila_crear(FuncionCopia, FuncionDestructora);

/**
 * Agrega un  elemento a la pila
 */
void pila_push(Pila , void* );

/**
 * Retorna el elemento en el tope de la pila
 * Reduce en 1 topePila, sin eliminar el elemento, habilita a ser pisado mas tarde
 */
void* pila_pop(Pila);


/**
 * destruye la pila
 */
void pila_destruir(Pila);
#endif