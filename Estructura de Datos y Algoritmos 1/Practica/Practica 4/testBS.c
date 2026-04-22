#include <stdio.h>
#include <stdlib.h>
#include "headers/bstree.h"

static int comparar_enteros(int* data, int* extra){
   return *data - *extra;
}
static  void imprimir_enteros(int* data, __attribute__((unused)) void* extra){
    printf("%d ",*data);
}
static  void* copiar_enteros(int* data){
    return data;
}

static void destruir_entero(int* data){
    return;
}



int main(){

    int numeros[8]={9,1,2,15,4,8,6,7};
    BSTree raiz= bstree_crear();
    printf("a\n");
    raiz= bstree_insertar(raiz,numeros+1,(FuncionCopiadora)copiar_enteros,(FuncionComparadora) comparar_enteros);
    raiz= bstree_insertar(raiz,numeros+3,(FuncionCopiadora)copiar_enteros,(FuncionComparadora) comparar_enteros);
    raiz= bstree_insertar(raiz,numeros+2,(FuncionCopiadora)copiar_enteros,(FuncionComparadora) comparar_enteros);
    raiz= bstree_insertar(raiz,numeros+4,(FuncionCopiadora)copiar_enteros,(FuncionComparadora) comparar_enteros);
    raiz= bstree_insertar(raiz,numeros+6,(FuncionCopiadora)copiar_enteros,(FuncionComparadora) comparar_enteros);
    raiz= bstree_insertar(raiz,numeros+5,(FuncionCopiadora)copiar_enteros,(FuncionComparadora) comparar_enteros);

    printf("PREORDER\n");
    bstree_recorrer(raiz,BTREE_RECORRIDO_PRE,(FuncionVisitanteExtra)imprimir_enteros,NULL);
    puts("");
    printf("INORDER\n");
    bstree_recorrer(raiz,BTREE_RECORRIDO_IN,(FuncionVisitanteExtra)imprimir_enteros,NULL);
    puts("");
    printf("POSORDER\n");
    bstree_recorrer(raiz,BTREE_RECORRIDO_POST,(FuncionVisitanteExtra)imprimir_enteros,NULL);
    puts("");

    int cota= bstree_cota_inferior(raiz, 16,(FuncionComparadora) comparar_enteros );
    printf("cota: %d\n", cota);
    //bstree_recorrer_intervalo(raiz, -3, 8, (FuncionVisitanteExtra)imprimir_enteros, (FuncionComparadora)comparar_enteros);

    printf("\ncdlis\n");

    cdlist cdlista= bstree_to_cdlist( raiz);

    bstree_cdlist_recorrer(cdlista, (FuncionVisitanteExtra) imprimir_enteros, 0);
    printf("primero %d\n", *(int*)cdlista->primero->data);
    printf("ultimo %d\n", *(int*)cdlista->ultimo->data);
    bstree_cdlist_destruir(cdlista, (FuncionDestructora) destruir_entero);
    //bstree_destruir(raiz,(FuncionDestructora)destruir_entero );
    return 0;
}