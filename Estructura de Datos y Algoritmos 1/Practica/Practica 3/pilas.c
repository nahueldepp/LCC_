#include <stdio.h>
#include "pilas.h"
#include <ctype.h>
#include <stdlib.h>




/**
 *  crea e inicializa una nueva pila vac´ıa con la capacidad dada.
 */
Pila pila_crear(int capacidad){
    Pila nuevaPila=malloc(sizeof(struct _Pila));
    nuevaPila->arr= arreglo_enteros_crear(capacidad);
    nuevaPila->ultimaPos= -1;
    return nuevaPila;
}

/**
 * libera la memoria requerida para la pila.
 */
void pila_destruir(Pila pila){
    arreglo_enteros_destruir(pila->arr);
    free(pila);
}

/**
 * retorna 1 si la pila est´a vac´ıa, y 0 en caso contrario.
 */
int pila_es_vacia(Pila pila){
    return (pila->ultimaPos == -1);
}

/**
 *  retorna el elemento que se encuentre en el tope de la pila, pero sin
eliminarlo.
 */
int pila_tope(Pila pila){
    return *(pila->arr->direccion + pila->ultimaPos);
}

/**
 * inserta un elemento en el tope de la pila, en caso que la pila
 * se encuentre llena, deber´a aumentar al doble la capacidad del arreglo
 * Ayuda: puede llamar a la funci´on arreglo enteros ajustar.
 */
void pila_apilar(Pila pila, int x){

    if(pila->ultimaPos == pila->arr->capacidad - 1){   
        arreglo_enteros_ajustar(pila->arr, pila->arr->capacidad * 2);

    }
    arreglo_enteros_escribir(pila->arr,++(pila->ultimaPos), x);
    
} 

/**
 * elimina el elemento que se encuentra en el tope de la pila.
 */
void pila_desapilar(Pila pila){
    (pila->ultimaPos)--;
}

/**
 * 
 */
void pila_imprimir(Pila pila){
    int ultimaPos=pila->ultimaPos;
    for(int i= 0; i<=ultimaPos; i++)
    printf("%d, ",pila->arr->direccion[i]);
}

int main(){

    Pila nuevaPila= pila_crear(5);
    pila_apilar(nuevaPila,5);
    pila_apilar(nuevaPila,1);
    pila_apilar(nuevaPila,2);
    pila_apilar(nuevaPila,3);
    pila_apilar(nuevaPila,4);
    pila_desapilar(nuevaPila);
    pila_apilar(nuevaPila,13);

    pila_imprimir( nuevaPila);

    Pila nueva2Pila= pila_crear(5);
    printf("es vacia? %d \n",pila_es_vacia(nuevaPila));
    printf("es vacia? %d \n",pila_es_vacia(nueva2Pila));
    pila_apilar(nueva2Pila, 6);

    printf("tope de la pila 1 %d \n", pila_tope(nuevaPila));
    printf("tope de la pila 2 %d \n", pila_tope(nueva2Pila));
    pila_destruir(nueva2Pila);
    pila_destruir(nuevaPila);
}