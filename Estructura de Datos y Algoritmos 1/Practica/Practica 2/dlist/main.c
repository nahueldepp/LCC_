#include "dlist.h"
#include <stdio.h>


void imprimir_dato(int dato){
    printf("%d ",dato);
}

int main(){
    DList nuevaLista=  dlist_crear();

    nuevaLista= dlist_agregar_inicio(nuevaLista, 3);
    nuevaLista= dlist_agregar_final(nuevaLista, 4);
    nuevaLista= dlist_agregar_inicio(nuevaLista, 2);
    nuevaLista= dlist_agregar_final(nuevaLista, 5);
    nuevaLista= dlist_agregar_inicio(nuevaLista, 1);

    dlist_recorrer(nuevaLista,imprimir_dato, DLIST_RECORRIDO_HACIA_ADELANTE);
    puts("");
    dlist_recorrer(nuevaLista,imprimir_dato, DLIST_RECORRIDO_HACIA_ATRAS);
    puts("");
    dlist_destruir(nuevaLista);
}