#include "contacto.h"
#include "glist.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

  GList lista = glist_crear();
  
  Contacto *contactos[6];
  contactos[0] = contacto_crear("Pepe Argento", "3412695452", 61);
  contactos[1] = contacto_crear("Moni Argento", "3412684759", 60);
  contactos[2] = contacto_crear("Coqui Argento", "3415694286", 32);
  contactos[3] = contacto_crear("Paola Argento", "3416259862", 29);
  contactos[4] = contacto_crear("Maria Elena Fuseneco", "3416874594", 59);
  contactos[5] = contacto_crear("Dardo Fuseneco", "3416894526", 64);

  for (int i = 0; i < 6; ++i) {
    lista =
        glist_agregar_inicio(lista, contactos[i], (FuncionCopia)contacto_copia);
    contacto_destruir(contactos[i]);
  }

  printf("Lista:\n");
  glist_recorrer(lista, (FuncionVisitante)contacto_imprimir);

  GList listaMayor60= glist_filtrar(lista, (FuncionCopia)contacto_copia, (Predicado)mayor_60);

  printf("ListaFiltro:\n");
  glist_recorrer(listaMayor60, (FuncionVisitante)contacto_imprimir);

  SGList listaOrdenada= sglist_crear();


  printf("ListaOrdenada:\n");
  Contacto* contacto0= contacto_crear("b", "3412695452", 61);
  Contacto* contacto1= contacto_crear("a", "3412695452", 61);
  Contacto* contacto3= contacto_crear("d", "3412695452", 61);
  Contacto* contacto4= contacto_crear("c", "3412695452", 61);
  listaOrdenada= sglist_insertar(listaOrdenada, contacto0,(FuncionCopia) contacto_copia, (FuncionComparadora)contacto_comparar);
  listaOrdenada= sglist_insertar(listaOrdenada, contacto1,(FuncionCopia) contacto_copia, (FuncionComparadora)contacto_comparar);
  listaOrdenada= sglist_insertar(listaOrdenada, contacto3,(FuncionCopia) contacto_copia, (FuncionComparadora)contacto_comparar);
  listaOrdenada= sglist_insertar(listaOrdenada, contacto4,(FuncionCopia) contacto_copia, (FuncionComparadora)contacto_comparar);
  glist_recorrer(listaOrdenada, (FuncionVisitante)contacto_imprimir);

  printf("el elemento 'a' %d", sglist_buscar(listaOrdenada,contacto0,(FuncionComparadora)contacto_comparar));

  printf("Ordenar Lista: \n");
  
  Contacto* c0 = contacto_crear("P", "3412695452", 61);
  Contacto* c1= contacto_crear("M", "3412684759", 60);
  Contacto* c2= contacto_crear("C", "3415694286", 32);
  Contacto* c3 = contacto_crear("A", "3416259862", 29);
  Contacto* c4 = contacto_crear("B", "3416874594", 59);
 
  void* contactosArr[]={c0,c1,c2,c3,c4};

  SGList listaNueva= sglist_arr(contactosArr, 5, (FuncionCopia) contacto_copia, (FuncionComparadora) contacto_comparar);
  glist_recorrer(listaNueva, (FuncionVisitante)contacto_imprimir);
  for (int i = 0; i < 5; ++i) {
    contacto_destruir(contactosArr[i]);
  }
  glist_destruir(listaOrdenada, (FuncionDestructora)contacto_destruir);
  glist_destruir(listaMayor60,(FuncionDestructora)contacto_destruir);
  glist_destruir(lista, (FuncionDestructora)contacto_destruir);

  return 0;
}