#include "slist.h"
#include <stdio.h>
#include <stdlib.h>

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  SList nodo = lista;
  for (;nodo->sig != NULL;nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void slist_recorrer(SList lista, FuncionVisitante visit) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

int slist_longitud(SList lista){

  int longitud= 0;
  for(; lista; lista= lista->sig){
    longitud++;
  }

  return longitud; 
}

SList slist_concatenar(SList lista1, SList lista2 ){

  if(lista1 == NULL)
    return lista2;

  SList nodo= lista1;
  for(; nodo->sig != NULL; nodo= nodo->sig );

  nodo->sig= lista2;  
  return lista1;
}

SList slist_insertar(SList lista, int pos, int dato){

  SNodo* nuevoNodo= malloc(sizeof(SNodo));
  nuevoNodo->dato= dato;
  nuevoNodo->sig= lista;

  if(lista == NULL || pos == 0 ) 
    return nuevoNodo;

  int largoLista= slist_longitud(lista);

  if (0< pos <= largoLista)
  {

    SList temp= lista;
    SList tempAnterior;
    for(int i = 0; i< pos; i++){
      tempAnterior= temp;
      temp= temp->sig;
    }
    tempAnterior->sig=nuevoNodo;
    nuevoNodo->sig=temp;
    

  }
  else{
    printf("La posicion selecionada no es valida\n"); 
  }

  return lista;
}

SList slist_eliminar(SList lista,int pos){

  if(lista == NULL)
    return lista;

  int largoLista= slist_longitud(lista);

  SList temp= lista;

  if(pos == 0){
    lista = lista->sig;
    free(temp);
  }
  else if( (0 < pos) && (pos < largoLista) ){
    
    SList tempAnterior;
    for(int i = 0; i< pos; i++){
      tempAnterior= temp;
      temp= temp->sig;
    }
    
    tempAnterior->sig = temp->sig;
    free(temp);
  }
  else{
    printf("La posicion selecionada no es valida\n"); 

  }
  
  return lista;
}



int slist_contiene( SList lista, int dato){
  
  if(lista == NULL)
    return 0;
  
  SList temp= lista;
  while( (temp->dato != dato) && (temp->sig!= NULL)  ){
    temp=temp->sig;
  }

  if(temp->dato != dato)
    return 0;
  else 
    return 1;
} 

int slist_indice(SList lista, int dato){

  int i = 0;
  SList temp= lista;
  while( (temp->dato != dato) && (temp->sig!= NULL)  ){
    temp=temp->sig;
    i++;
  }

  if(temp->dato != dato)
    return -1;
  else 
    return i;
}

SList slist_intersecar(SList lista1, SList lista2){

  SList nuevaLista=slist_crear();
  if( (lista1 == NULL) || (lista2 == NULL)){
    return nuevaLista;
  }

  
  for(SList temp= lista1; temp != NULL; temp= temp->sig ){
    for(SList temp2= lista2; temp2 != NULL; temp2= temp2->sig ){

    if((temp->dato == temp2->dato) && !slist_contiene(nuevaLista, temp->dato)){

      nuevaLista = slist_agregar_inicio(nuevaLista, temp->dato);
      }
    }
  }
  return nuevaLista;
}


SList slist_custom(SList lista1,SList lista2, FuncionComparacion fun){

  SList nuevaLista= slist_crear();
  if ((lista1 == NULL) || (lista2 == NULL))
  {
    return nuevaLista;
  }

  
  for(SList temp= lista1; temp != NULL; temp= temp->sig ){
    for(SList temp2= lista2; temp2 != NULL; temp2= temp2->sig ){

    if(fun(temp->dato,temp2->dato) && !slist_contiene(nuevaLista, temp->dato)){

      nuevaLista = slist_agregar_inicio(nuevaLista, temp->dato);
      }
    }
  }
  
  return nuevaLista;
}


SList slist_ordenar(SList lista, FuncionComparacion funComp){

  if(lista == NULL){
    return lista;
  }

  int largoLista= slist_longitud(lista);

  for(int i = 0; i < largoLista; i++){
    for(SList temp = lista; temp->sig != NULL; temp= temp->sig){

      if((funComp(temp->dato, temp->sig->dato) == 0) || (funComp(temp->dato, temp->sig->dato) == -1));

      else{
        int datoTemp= temp->dato;
        temp->dato= temp->sig->dato;
        temp->sig->dato= datoTemp;
      }
    }
  }
  return lista;
}

SList slist_intercalar(SList lista, SList listaAinsertar){

  SList nuevaLista = NULL;
  int i= 1;
  for(SList temp= listaAinsertar; temp != NULL; temp= temp->sig){

    nuevaLista= slist_insertar(lista, i, temp->dato);
    i += 2;
  }
  return nuevaLista;
}

SList slist_partir(SList lista){

  int largoLista= slist_longitud(lista);

  SList segundaMitad= lista;

  int i = 0;
  for(;i < (largoLista)/2; i++, segundaMitad= segundaMitad->sig);

  SList temp= segundaMitad;
  segundaMitad= segundaMitad->sig;
  temp->sig= NULL;

  return segundaMitad;

}


SList2 slist2_crear(){

  SList2 listaNueva;

  listaNueva.primero= NULL;
  listaNueva.ultimo= listaNueva.primero;

  return listaNueva;

}

SList2 slist2_agregar_final(SList2 lista, int dato){

  SNodo* nuevoNodo= malloc(sizeof(SNodo));
  nuevoNodo->dato= dato;
  nuevoNodo->sig= NULL;

  if(lista.primero == NULL){
    lista.primero= nuevoNodo;
    lista.ultimo= nuevoNodo;
  }
  else{
    lista.ultimo->sig= nuevoNodo;
    lista.ultimo= nuevoNodo;
  }

  return lista;

}

SList2 slist2_agregar_inicio(SList2 lista, int dato){

  SNodo* nuevoNodo= malloc(sizeof(SNodo));
  nuevoNodo->dato= dato;
  nuevoNodo->sig= NULL;

  if(lista.primero == NULL){
    lista.primero= nuevoNodo;
    lista.ultimo= nuevoNodo;
  }
  else{
    nuevoNodo->sig= lista.primero;
    lista.primero= nuevoNodo;
  }
  return lista;
}

/**
 * Dada una lista, deterina si existe en ciclo en la misma, en el caso que no exista, devuelve NULL
 * caso contrario devuelve el puntero de inicio del ciclo
 */
SNodo* slist_ciclo(SList lista){

  printf("e");
  SNodo* liebre= lista;
  SNodo* tortuga= lista;
  printf("D");
  while((liebre->sig != NULL) && (liebre->sig->sig != NULL)){
    printf("c");
    liebre=liebre->sig->sig;
    tortuga= tortuga->sig;
    if(liebre == tortuga) 
      break;
  }

  if((liebre->sig == NULL)  || (liebre->sig->sig == NULL) ){
    printf("a");
    return liebre;
  }
  else{
    tortuga= lista;
    while(liebre != tortuga){
      tortuga= tortuga->sig;
      liebre= liebre->sig;
    }
    printf("b");
    
    return tortuga;
  }
  return NULL;
}