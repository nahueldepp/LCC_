#ifndef _G_LCOLAS_H_
#define _G_LCOLAS_H_


/*---tipo de funciones---*/
typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*Predicado)(void* dato);
typedef int (*FuncionComparadora) (void* dato1, void* dato2);
/*-----------------------*/

typedef struct _GNode {
    void *data;
    struct _GNode *next;
  } GNode;
  
typedef struct _Cola{
  GNode* inicio;
  GNode* final;
}LCola;

typedef LCola* Cola;

Cola cola_crear();

void cola_destruir(Cola cola, FuncionDestructora funDestruir);

/**
 * retorna 1 si la cola esta vacia 0  en  caso contrario
 */
int cola_es_vacia(Cola cola);

/**
 * que retorna el elemento que se encuentre en el inicio de la cola, sin eliminarlo
 */
void* cola_inicio(Cola cola);

/**
 * Encola un elemento( lo coloca al principio de la lista)
 */
Cola cola_encolar(Cola cola, void* dato, FuncionCopia copia);

void* cola_desencolar(Cola cola, FuncionDestructora funDestruir, FuncionCopia funCopia);

void cola_imprimir(Cola cola, FuncionVisitante funDestruir);



#endif