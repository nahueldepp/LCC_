#ifndef _LISTARR_H
#define _LISTARR_H
#define NUMNODES 100 //numero de nodos en un array

typedef struct _NodeType{
    void* data;
    int next;
}NodeType;

typedef NodeType NodeArray[NUMNODES];

int avail=0;

/**
 * Dada una arreglo de nodos, inicializa el orden de todos los nodos
 */
void node_init(NodeArray nodo);

/**
 * Devuelve un nodo libre
 */
int getnode(NodeArray nodo);

/**
 * Libera un nodo
 */
void freenode(int p);
#endif