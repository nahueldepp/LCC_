#include "Acolas.h"
#include <stdlib.h>
#include <stdio.h>


Cola cola_crear(){
  Cola nuevaCola= malloc(sizeof(_ACola));
  nuevaCola->frente= -1;
  nuevaCola->final= -1;
}

void cola_destruir(Cola cola, FuncionDestructora destruir){

  if((cola->frente != -1)&&(cola->frente <= cola->final)){
    for(int i= cola->frente; i<=cola->final; i++){
      printf("cola %d\n",i);
      destruir(cola->arr[i]);
    }
  } 
  else{
    for(int i= cola->frente; i != cola->final; i= ++i % MAXCOLA){
      destruir(cola->arr[i]);
    }
    
  }
  free(cola);
}

/**
 * retorna 1 si la cola esta vacia 0  en  caso contrario
 */
int cola_es_vacia(Cola cola){
  return cola->final == -1; 
}

/**
 * que retorna el elemento que se encuentre en el inicio de la cola, sin eliminarlo
 */
void* cola_inicio(Cola cola){
  return cola->arr[cola->frente];
}

/**
 * Encola un elemento
 */
void cola_encolar(Cola cola, void* dato, FuncionCopia copia){

  if((cola->final + 1) % MAXCOLA == cola->frente){
    printf("Espacio insuficiente");
    return;
    }
  if(cola->frente == -1){
    cola->frente = 0;
  }
  cola->final = ++cola->final % MAXCOLA;
  cola->arr[cola->final] = copia(dato);

}

void* cola_desencolar(Cola cola, FuncionDestructora funDestruir, FuncionCopia funCopia){

  if(cola_es_vacia(cola)) return NULL;
  void* dato= funCopia(cola->arr[cola->frente]);
  funDestruir(cola->arr[cola->frente]);
  
  if(cola->final == cola->frente){
    cola->final = -1;
    cola->frente= -1;
  }
  else{

    cola->frente= ++cola->frente % MAXCOLA;
  }
  

  return dato;
}

void cola_imprimir(Cola cola, FuncionVisitante funImprimir){
  for(int i= cola->frente; i != cola->final; i++ % MAXCOLA){
    funImprimir(cola->arr[i]);
  }
}
