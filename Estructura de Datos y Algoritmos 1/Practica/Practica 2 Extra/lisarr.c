#include "listarr.h"
#include <stdio.h>

/**
 * Dada una arreglo de nodos, inicializa el orden de todos los nodos
 */
void node_init(NodeArray nodo){
    for(int i= 0; i < NUMNODES; i++){
        nodo[i].next = i + 1;
    }
    nodo[NUMNODES-1].next = -1;
}

/**
 * Devuelve un nodo libre
 */
int getnode(NodeArray nodo){
    if(avail == -1){
        printf("Overflow: No hay mas espacio");
        return -1;
    }

    int p;
    p=avail;
    avail = nodo[p].next;
    return p;
}

/**
 * Libera un nodo
 */
void freenode(int p, NodeArray nodo){

    (nodo + p)->next = avail;
    avail = p;
}

