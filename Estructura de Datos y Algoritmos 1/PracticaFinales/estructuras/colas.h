#ifndef __COLAS_H__
#define __COLAS_H__

#define MAX_COLA 10
typedef  void* (*FuncionCopia)(void*);
typedef  void (*FuncionDestructora)(void*);

typedef struct _Cola* Cola;


/**
 * Crea una cola vacia
 */
Cola cola_crear(FuncionCopia, FuncionDestructora);

/**
 * Agrega un elemento a la cola
 */
void cola_enqueue(Cola, void*);

/**
 * Desencola el elemento al frente de la cola
 */

void* cola_dequeue(Cola, void*);

/**
 * Retorna 1 si la cola esta vacia, 0 en caso contrario
 */
int cola_isEmpty(Cola);


#endif 