#include <stdio.h>
#include "pilas.h"
#include <stdlib.h>

int* copia_entero(int* a){
    int* copia= malloc(sizeof(int));
    *copia= *a;
    return copia;
}

void destr_entero(int* a ){
    free(a);
}

void imprimir_entero(int* a){
    printf("%d\n", *a);
}
int main(){

    Pila pila= pila_crear((FuncionCopia)copia_entero, (FuncionDestructora)destr_entero);

    int enteros[10];
    for(int i= 0; i< 8; i++){
        enteros[i]= (i+1)*2 -3;
    }
    for(int i= 0; i< 8; i++){
        pila_push(pila, enteros+i);
    }    
    for(int i= 0; i<= pila->topePila; i++){
        imprimir_entero(pila->datos.arreglo[i]);
    }
    printf("pop\n");
    for(int i= 0; i< 8; i++){
        if(i%2 == 0){
            int* a=pila_pop(pila);
            imprimir_entero(a);
        }
    }
    printf("Pila dsp del pop");
    for(int i= 0; i<= pila->topePila; i++){
        imprimir_entero(pila->datos.arreglo[i]);
    }
    return 0;
}
