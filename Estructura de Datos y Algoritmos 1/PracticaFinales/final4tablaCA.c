#include <stdlib.h>
#include <stdio.h>
#include "final4tabla.h"
#include <assert.h>


TablaHash tabla_crear(FuncionCopiadora copia, FuncionComparadora comp,FuncionDestructora destr,FuncionHash hash){

    TablaHash tabla= malloc(sizeof(struct _TablaHash));
    assert(tabla != NULL);
    tabla->capacidad= TAM_TABLA;
    tabla->elems=malloc(sizeof(CasillaHash) * tabla->capacidad);
    assert(tabla != NULL);
    tabla->numElems=0;
    tabla->comp= comp;
    tabla->copia= copia;
    tabla->destr= destr;
    tabla->hash1= hash;
    for(unsigned i= 0; i< tabla->capacidad;i++){
        tabla->elems[i]= NULL;
    }
    return tabla;
}

void tabla_insertar(TablaHash tabla, void* dato){

    assert(dato!=NULL);
    
    unsigned idx= tabla->hash1(dato)%tabla->capacidad;
    
    //si la casilla buscada esta vacia
    if(tabla->elems[idx] == NULL){
        tabla->elems[idx]= malloc(sizeof(_CasillaHash));
        tabla->elems[idx]->dato= tabla->copia(dato);
        tabla->elems[idx]->sig=NULL;
        tabla->numElems++;
        printf("numElem %d\n", tabla->numElems);
        
    }
    //las se encuentra ocpada por el mismo dato (se pisa)
    else if(tabla->comp(tabla->elems[idx]->dato, dato)==0){
        tabla->destr(tabla->elems[idx]->dato);
        tabla->elems[idx]->dato= tabla->copia(dato);
        
    }
    //hay una colision, se procede a enlazar el viejo dato con el nuevo (se agrega a la lista)
    //se chequea que ya no este en la lista, si lo esta se pisa
    else{
        CasillaHash nodo= tabla->elems[idx]->sig;
        int enLista= 0;
        while(nodo != NULL && !enLista){
            if(tabla->comp(nodo->dato,dato)==0){
                tabla->destr(nodo->dato);
                nodo->dato= tabla->copia(dato);
                enLista= 1;
            }
            nodo= nodo->sig;
        }
        if(!enLista){
            nodo= malloc(sizeof( _CasillaHash));
            nodo->dato= tabla->copia(dato);
            nodo->sig=tabla->elems[idx];
            tabla->elems[idx]=nodo;
        }
    }
    float loadFactor= tabla->numElems/(float)tabla->capacidad;
    printf("loadfactor %f\n", loadFactor);
    if(loadFactor >= 0.75){
        tabla_rehash(tabla);
    }
    return;
}

/**
 * tabla_buscar(): TablaHash void* -> void*
 * Busca el dato pasado en la tabla, en caso de no encontrarlo retorna NULL
 */
void* tabla_buscar(TablaHash tabla, void* dato){

    unsigned idx= tabla->hash1(dato)%tabla->capacidad;
    void* encontrado= NULL;
    //el dato no se encuentra en la tabla
    if(tabla->elems[idx] == NULL)
    return encontrado;
    else if(tabla->comp(tabla->elems[idx]->dato, dato)==0){
        encontrado= tabla->elems[idx]->dato;
    }
    //el dato podria encontrarse en la lista de ese indice
    else{
        CasillaHash nodo= tabla->elems[idx];
       
        while(nodo!= NULL && tabla->comp(nodo->dato,dato)!=0){
            
            nodo= nodo->sig;
        }
        if(nodo!= NULL){
            encontrado= nodo->dato;
        }
    }
    return encontrado;
}


void tabla_eliminar(TablaHash tabla, void* dato){

    assert(dato != NULL);
    unsigned idx= tabla->hash1(dato)%tabla->capacidad;
    
    if(tabla->elems[idx]->dato == NULL)
        return;
    else if(tabla->comp(tabla->elems[idx]->dato, dato)== 0){
        CasillaHash nodoAeliminar= tabla->elems[idx];
        tabla->elems[idx]= nodoAeliminar->sig;
        tabla->destr(nodoAeliminar->dato);
        free(nodoAeliminar);
        return;
    }
    //el dato a eliminar se encuentra en la lista
    else{
        CasillaHash nodoAnterior= tabla->elems[idx];
        CasillaHash nodoAeliminar= tabla->elems[idx]->sig;
       
        while(nodoAeliminar != NULL && tabla->comp(nodoAeliminar->dato,dato)!=0){
            nodoAnterior= nodoAeliminar;
            nodoAeliminar= nodoAeliminar->sig;
        }
        //si estaba en la lista
        if(nodoAeliminar != NULL){   
            nodoAnterior->sig= nodoAeliminar->sig;
            tabla->destr(nodoAeliminar->dato);
            free(nodoAeliminar);
        }
        return;
    }
}

void tabla_rehash(TablaHash tabla){
     
    CasillaHash* viejoArray= tabla->elems;
    unsigned viejaCapacidad= tabla->capacidad;

    tabla->capacidad= tabla->capacidad*2;
    tabla->elems= malloc(sizeof(CasillaHash)*tabla->capacidad);
    tabla->numElems=0;
    for(unsigned idx=0; idx<tabla->capacidad;idx++){
        tabla->elems[idx]=NULL;
    }
    for(unsigned idx= 0; idx < viejaCapacidad;idx++){
        if(viejoArray[idx] != NULL){
            CasillaHash nodo= viejoArray[idx];
            CasillaHash nodoAeliminar;
            while(nodo != NULL){
                tabla_insertar(tabla,nodo->dato);
                nodoAeliminar= nodo;
                nodo= nodo->sig;
                tabla->destr(nodoAeliminar->dato);
                free(nodoAeliminar);
            }

        }
    }
    free(viejoArray);

}

void tablahash_destruir(TablaHash tabla){

    for(unsigned i= 0; i< tabla->capacidad; i++){
        
        if(tabla->elems[i]!=NULL){
            CasillaHash nodo= tabla->elems[i];
            CasillaHash nodoAeliminar;
            while (nodo){
                nodoAeliminar= nodo;
                nodo= nodo->sig;
                tabla->destr(nodoAeliminar->dato);
                free(nodoAeliminar);
            }
        }
    }

    free(tabla->elems);
    free(tabla);
    return;
}