#include "../cabeceras/listas.h"
#include "../cabeceras/utils.h"
#include "../cabeceras/parser.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


GLista glista_crear(){
    GLista nuevaLista= malloc(sizeof(struct _GLista));
    nuevaLista->izq= NULL;
    nuevaLista->der= nuevaLista->izq;

    return nuevaLista;
}

int glista_vacia(GLista lista){
  return lista->izq == NULL || lista->der == NULL;
}

void glista_destruir(GLista lista, FuncionDestructora destr){

  Nodo nodoAdestruir;
  while(lista->izq != NULL){
      nodoAdestruir= lista->izq;
      lista->izq= lista->izq->sig;
      destr(nodoAdestruir->dato);
      free(nodoAdestruir);
  }
  free(lista);
}


GLista glista_agregar_izq(GLista lista, void* dato, FuncionCopia copia){
  Nodo nuevoNodo= malloc(sizeof(struct _SNodo));
  nuevoNodo->dato= copia(dato);
  nuevoNodo->sig= lista->izq;
  nuevoNodo->ant= NULL;

  if(lista->izq == NULL)
      lista->der= nuevoNodo;
  else
    lista->izq->ant=nuevoNodo;

  lista->izq= nuevoNodo;
  return lista;
}

GLista glista_agregar_der(GLista lista,void* dato, FuncionCopia copia){

  Nodo nuevoNodo= malloc(sizeof(struct _SNodo));
  nuevoNodo->sig= NULL;
  nuevoNodo->ant= lista->der;
  nuevoNodo->dato= copia(dato);
  
  if(lista->izq == NULL)
    lista->izq= nuevoNodo;
  else
    lista->der->sig= nuevoNodo;
  lista->der= nuevoNodo;
  return lista;
}

GLista glista_eliminar_izq(GLista lista, FuncionDestructora destr ){
  
  if(lista->izq == NULL)
    return lista;
  
  Nodo nodoAeliminar= lista->izq;
  lista->izq= nodoAeliminar->sig;
  if(lista->izq == NULL)
    lista->der = lista->izq;
  else
    lista->izq->ant= NULL;
  destr(nodoAeliminar->dato);
  free(nodoAeliminar);
  return lista;
}

GLista glista_eliminar_der(GLista lista, FuncionDestructora destr){
  if(glista_vacia(lista))
    return lista;

  Nodo nodoAeliminar= lista->der;
  lista->der= nodoAeliminar->ant;
  if(lista->der == NULL)
    lista->izq= lista->der;
  else
    lista->der->sig=NULL;
  destr(nodoAeliminar->dato);
  free(nodoAeliminar);

  return lista;
}

void glista_recorrer(GLista lista, FuncionVisitante func, int sentidoLista){
  
  if(sentidoLista == DLIST_RECORRIDO_HACIA_ADELANTE){
        for(Nodo siguiente= lista->izq; siguiente != NULL; siguiente= siguiente->sig){
            func(siguiente->dato);
        }
    }
    else{
        for(Nodo anterior= lista->der; anterior != NULL; anterior= anterior->ant){
            func(anterior->dato);
        }
    }
    puts("");
}   

GLista glista_copiar(GLista lista, FuncionCopia copia){

  GLista listaCopia=glista_crear();
  Nodo temp= lista->izq;
    while(temp!= NULL){
        listaCopia= glista_agregar_der(listaCopia, temp->dato,(FuncionCopia) copia);
        temp= temp->sig;
    }
    return listaCopia;
}

int glista_longitud(GLista lista){

    int i=0;
    for(Nodo siguiente= lista->izq; siguiente != NULL; siguiente= siguiente->sig, i++);

    return i;
}

/**
 * Funciones para crear listas que evaluaran las funciones de listas definidas por el usuario
 */


/*
 * Crea una lista
 * dependiendo del operador crear una lista para DEFL o APPLY
 */
Lista lista_crear(char* tokens[], int numTokens,int tipoLista){

  Lista nuevaLista= malloc(sizeof(struct _List));
  assert(nuevaLista != NULL);
  nuevaLista->glista= glista_crear();

  switch(tipoLista){
    case(0):{//lista con nombre propio
      //lectura de datos para declaraciones DEFL 
      nuevaLista->nombre= malloc(sizeof(char) * (strlen(tokens[1]) + 1));
      assert(nuevaLista->nombre != NULL);
      strcpy(nuevaLista->nombre,tokens[1]);

      
      for(int i = 4; i < numTokens-2; i+=2){
          int* dato= malloc(sizeof(int));
          *dato= atoi(tokens[i]);
          glista_agregar_der(nuevaLista->glista,dato, (FuncionCopia)copiar_puntero_entero);
          free(dato);
      }
      break;
    }
    case(1):{//lista generica, no se guardara en la tabla de listas
      //lectura de datos para declaraciones APPLY sobre listas genericas: [z,X,y]
      nuevaLista->nombre= malloc(sizeof(char) * (strlen(tokens[0]) + 1));
      assert(nuevaLista->nombre != NULL);
      strcpy(nuevaLista->nombre,tokens[0]);

      //apply nombreFun [x,y];
      for(int i = 3; i < numTokens-2; i+=2){
          int* dato= malloc(sizeof(int));
          *dato= atoi(tokens[i]);
          glista_agregar_der(nuevaLista->glista,dato, (FuncionCopia)copiar_puntero_entero);
          free(dato);
      }

    }

  }
    return nuevaLista;
}

/*
 *Destruye una lista
 */
void lista_destruir(Lista lista){
  assert(lista != NULL);
  free(lista->nombre);
  glista_destruir(lista->glista, (FuncionDestructora)destruir_puntero_entero);
  free(lista);
}

Lista lista_copia(Lista lista){
  Lista copiaLista= malloc(sizeof(struct _List));
  assert(copiaLista != NULL);
  copiaLista->nombre= malloc(sizeof(char)* (strlen(lista->nombre) + 1 ));
  assert(copiaLista->nombre != NULL);
  strcpy(copiaLista->nombre, lista->nombre);

  copiaLista->glista= glista_copiar(lista->glista, (FuncionCopia)copiar_puntero_entero);
  return copiaLista;
}

void lista_imprimir(Lista lista){
printf("[");
Nodo siguiente= lista->glista->izq;
  for(;siguiente!=NULL && siguiente->sig != NULL; siguiente= siguiente->sig){
    printf("%d,", *(int*)siguiente->dato);
    }
  if(siguiente != NULL)
    printf("%d]\n", *(int*)siguiente->dato);
  else
    printf("]\n");
}

int lista_comparar(Lista l1, Lista l2){
  return comparar_cadena(l1->nombre, l2->nombre);
}

/**
 * compara el cuerpor de las listas
 * retorna 1 si son iguales, 0 en caso contrario
 */
int lista_comparar_cuerpo(Lista l1, Lista l2){

  Nodo elemntoL1= l1->glista->izq;
  Nodo elemntoL2= l2->glista->izq;
  int iguales= 1;
  while(elemntoL1!=NULL && elemntoL2!=NULL && iguales){
    iguales= (0==comparar_puntero_entero(elemntoL1->dato,elemntoL2->dato));
    elemntoL1= elemntoL1->sig;
    elemntoL2= elemntoL2->sig;
  }
  if(elemntoL1==NULL && elemntoL2!=NULL)
    return 0;
  if(elemntoL1!=NULL && elemntoL2==NULL)
    return 0;
  return iguales;
}
/**
 * retorna 1 si los extremos de la lista son iguales, 0 en caso contrario
 */
int lista_lados_iguales(Lista lista){
  if(lista->glista->izq== NULL)
    return 1;
  return *(int*)lista->glista->izq->dato == *(int*)lista->glista->der->dato;
}

/**
 * Hashear una lista por su nombre.
 */
unsigned lista_hashear(Lista lista) {
  return KRHash(lista->nombre);
}
unsigned lista_hashear2(Lista lista) {
  return KRHash2(lista->nombre);
}

