#include <stdio.h>
#include <stdlib.h>
#include "headers/btree.h"


static void imprimir_entero(BTree data) {
  printf("%d ", data->dato);
}

int main() {
  BTree ll = btree_unir(1, btree_crear(), btree_crear());
  BTree l = btree_unir(2, ll, btree_crear());
  BTree r = btree_unir(3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(4, l, r);

  
  btree_recorrer(raiz, BTREE_RECORRIDO_POST, (FuncionVisitante)imprimir_entero);
  puts("");
  btree_recorrer(raiz, BTREE_RECORRIDO_IN, (FuncionVisitante)imprimir_entero);
  puts("");
  btree_recorrer(raiz, BTREE_RECORRIDO_PRE,(FuncionVisitante) imprimir_entero);
  puts("");

  int i= btree_nnodos(raiz);
  printf("%d\n",i);
  printf("%d\n", btree_buscar(raiz, 4));

  BTree arbolCopia= btree_copiar(raiz);
  btree_recorrer(arbolCopia,BTREE_RECORRIDO_POST, (FuncionVisitante) imprimir_entero);
  puts("");

  BTree raiz2= btree_unir(6, raiz, arbolCopia);
  printf("%d\n",btree_profundidad(raiz2, 1));
  printf("%d\n",btree_nnodos_profundidad(raiz2, 3));
  printf("%d\n",btree_sumar(raiz2));

  //btree_valores_nivel(raiz2, (FuncionVisitante) imprimir_entero, 3);
  btree_recorrer_rbfs(raiz2, (FuncionVisitante) imprimir_entero);
  puts(" ");
  printf("afuera\n");
  btree_recorrer_bfs(raiz2,(FuncionVisitante) imprimir_entero);
  puts("");
  /* btree_destruir(raiz);
  btree_destruir(arbolCopia); */
  btree_recorrer(raiz2,BTREE_RECORRIDO_IN, (FuncionVisitante) imprimir_entero);
  raiz2= btree_mirror(raiz2);
  puts("");
  printf("mirror\n");
  btree_recorrer(raiz2,BTREE_RECORRIDO_IN, (FuncionVisitante) imprimir_entero);
  puts("");

  int completo= btree_es_completo(raiz2);
  printf("completo? %d\n", completo);

  BTree r1 = btree_unir(5, btree_crear(), btree_crear());
  BTree r2 = btree_unir(10, btree_crear(), btree_crear());
  BTree r21 = btree_unir(15, r1, r2);
  

  BTree r21copia= btree_copiar(r21);
  BTree a1a2= btree_unir(30, r21,r21copia);

  int completo2= btree_es_completo(a1a2);
  printf("completo2? %d\n", completo2);
    btree_recorrer(a1a2,BTREE_RECORRIDO_IN, (FuncionVisitante) imprimir_entero);
  
  btree_destruir(a1a2);
  btree_destruir(raiz2);
  return 0;
}
