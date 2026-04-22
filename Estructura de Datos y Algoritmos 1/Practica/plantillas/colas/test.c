#include "Lcolas.h"
#include <stdio.h>
#include <stdlib.h>


void in_destruir(int* dato){
    return;
}
int* in_copiar(int* dato){
    return dato;
}

void in_imprimir(int* dato){
    printf("%d\n", *dato);
}

int main(){
    Cola cola= cola_crear();

    int x= 15;
    int y= 78;
    int* p= &x;
    int*c= &y;
    printf("%p\n", p);
    cola= cola_encolar(cola, p, (FuncionCopia)in_copiar);
    cola= cola_encolar(cola, c, (FuncionCopia)in_copiar);
    int* m= cola_inicio(cola);
    printf("%p\n", m);
    int* l=(int*)cola_desencolar(cola, (FuncionDestructora)in_destruir,(FuncionCopia) in_copiar);
    int* t=(int*)cola_desencolar(cola, (FuncionDestructora)in_destruir,(FuncionCopia) in_copiar);
    printf("c\n");
    printf("%d %d\n",*l,*t);
    cola_destruir(cola, (FuncionDestructora)in_destruir);

    return 0;
}