#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

int comp_mayor(int a, int b){
  return a==b;
}

int fun_comp(int a, int b){
  return a-b;
}



int main(int argc, char *argv[]) {

  SList lista = slist_crear();

  lista = slist_agregar_inicio(lista, 3);
  lista = slist_agregar_inicio(lista, 2);
  lista = slist_agregar_inicio(lista, 1);
  lista = slist_agregar_final(lista, 4);

  slist_recorrer(lista, imprimir_entero);
  puts("");

  int longitudLista= slist_longitud(lista);
  printf("La longitud de la lista es: %d\n", longitudLista);

  //creo una nueva lista 
  SList lista2 = slist_crear();

  lista2 = slist_agregar_inicio(lista2, 6 );
  lista2 = slist_agregar_inicio(lista2, 6);
  lista2 = slist_agregar_inicio(lista2, 4);


  // concateno las listas previas
  lista= slist_concatenar(lista, lista2);
  slist_recorrer(lista, imprimir_entero);
  puts("");

  longitudLista= slist_longitud(lista);
  printf("La longitud de la lista es: %d\n", longitudLista);

  //agrego un elemento
  lista = slist_insertar(lista, 7, 15);
  slist_recorrer(lista, imprimir_entero);
  puts("");

  //elimino un elemneto de la lista
  lista=slist_eliminar(lista, 7);
  slist_recorrer(lista, imprimir_entero);
  puts("");

  printf("%d\n", slist_indice(lista,1));

  // interseccion de listas: 

  printf("\nInterseccion de listas\n ");



  printf("lista 1:");
  slist_recorrer(lista, imprimir_entero);
  puts("");

  printf("lista 2:");
  slist_recorrer(lista2, imprimir_entero);
  puts("");

 

  SList interseccion= slist_intersecar(lista, lista2);
  printf("lista inter:");
  slist_recorrer(interseccion, imprimir_entero);
  puts("");


  SList interseccion_custom= slist_custom(lista,lista2,comp_mayor);

  printf("lista inter custom:");
  slist_recorrer(interseccion_custom, imprimir_entero);
  puts("");

  //comparacion de listas

  SList listaOrdenadanada= slist_crear();
  listaOrdenadanada= slist_agregar_inicio(listaOrdenadanada,5);
  listaOrdenadanada= slist_agregar_inicio(listaOrdenadanada,8);
  listaOrdenadanada= slist_agregar_inicio(listaOrdenadanada,7);
  listaOrdenadanada= slist_agregar_inicio(listaOrdenadanada,9);
  listaOrdenadanada= slist_agregar_inicio(listaOrdenadanada,10);
  slist_recorrer(listaOrdenadanada, imprimir_entero);
  puts("");
  printf("%p\n", slist_ciclo(listaOrdenadanada));
  listaOrdenadanada=slist_ordenar(listaOrdenadanada, fun_comp);
  slist_recorrer(listaOrdenadanada, imprimir_entero);
  puts("");

  //insertar listas 

  SList listaInsertar= NULL;

  listaInsertar= slist_intercalar(listaOrdenadanada, interseccion_custom);
  slist_recorrer(listaInsertar, imprimir_entero);
  puts("");

  //partir lista

  SList segundaMitad= slist_partir(listaInsertar);
  slist_recorrer(segundaMitad, imprimir_entero);
  puts("");

  slist_recorrer(listaInsertar, imprimir_entero);
  puts("");

  slist_destruir(segundaMitad);
  slist_destruir(listaInsertar);
  slist_destruir(interseccion);
  slist_destruir(interseccion_custom);
  slist_destruir(lista);


  //Usando SList 2
  SList2 nuevaLista;
  nuevaLista= slist2_crear();

  nuevaLista= slist2_agregar_final( nuevaLista, 5);
  printf("ultimo elemento %d\n", nuevaLista.ultimo->dato);
  nuevaLista= slist2_agregar_inicio(nuevaLista, 8);
  
  printf("primer elemento %d\n", nuevaLista.primero->dato);

  slist_destruir(nuevaLista.primero);

  //Algoritmo de la tortuga y la liebre

  SList listaCiclo= slist_crear();
  listaCiclo= slist_agregar_inicio(listaCiclo,5);
  listaCiclo= slist_agregar_inicio(listaCiclo,4);
  listaCiclo= slist_agregar_inicio(listaCiclo,3);
  listaCiclo= slist_agregar_inicio(listaCiclo,2);
  /*  listaCiclo->sig->sig->sig->sig= listaCiclo->sig; */
  printf("%d\n",listaCiclo->dato);
  //printf("%p\n",listaCiclo);
  slist_recorrer(listaCiclo, imprimir_entero);
  slist_ciclo(listaCiclo);
  //printf("%p\n", slist_ciclo(listaCiclo)); 
  //printf("%p\n", NULL);

  slist_destruir(listaCiclo);

  return 0;
}
