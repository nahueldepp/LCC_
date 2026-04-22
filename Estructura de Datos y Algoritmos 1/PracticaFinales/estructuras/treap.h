#ifndef __TREAP_H__
#define __TREAP_H__


/**
 * Estructura de un treap, guarda una key o valor, y una prioridad
 * Los valores se ordedan como en un arbol binaria segun las keys
 * y tamb se ordenan como un heap usando las prioridades para hacer las rotaciones
 */
typedef struct _Nodo{
    int key;
    int priority;
    struct _Nodo* izq, *der;
}T_Nodo;

typedef T_Nodo*  Treap;

Treap treap_crear();

Treap treap_insertar(Treap, int);

Treap treap_eliminar(Treap, int);

void treap_recorrer(Treap, int);

void treap_destruir(Treap);


#endif