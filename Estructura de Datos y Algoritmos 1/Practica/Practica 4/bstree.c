#include "headers/bstree.h"
#include "headers/pilas.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>



/**
 * Retorna un arbol de busqueda binaria vacio.
 */
BSTree bstree_crear(){
   /*  BSTree nuevoArbol= malloc(sizeof(_BST_Nodo));
    nuevoArbol->der= NULL;
    nuevoArbol->izq= NULL;
    return nuevoArbol; */
    return NULL;
}

/**
 * Destruye el arbol y sus datos.
 */
void bstree_destruir(BSTree arbol, FuncionDestructora fdestruir){

    if(arbol == NULL) return;

    bstree_destruir(arbol->izq, fdestruir);
    bstree_destruir(arbol->der, fdestruir);
    fdestruir(arbol->data);
    free(arbol);

}

/**
 * Retorna 1 si el dato se encuentra y 0 en caso contrario.
 */
int bstree_buscar(BSTree arbol, void* dato, FuncionComparadora fcomparar){

    int der= 0;
    int izq= 0;
    if(arbol == NULL) return 0;
    if(fcomparar(dato, arbol->data)==0){ 
        return 1;
    }
    else if(fcomparar(dato,arbol->data)<0){
        return bstree_buscar(arbol->izq, dato, fcomparar);
    }
    else{
        return bstree_buscar(arbol->der, dato, fcomparar);
    }
}

/**
 * Inserta un dato no repetido en el arbol, manteniendo la propiedad del arbol
 * de busqueda binaria.
 */
BSTree bstree_insertar(BSTree arbol, void* dato, FuncionCopiadora fcopia, 
    FuncionComparadora fcomparar){

        if(arbol == NULL){
            BSTree nuevoNodo= malloc(sizeof(_BST_Nodo));
            nuevoNodo->data= fcopia(dato);
            nuevoNodo->der= NULL;
            nuevoNodo->izq = NULL;
            return nuevoNodo;
        }
        else if(fcomparar(dato, arbol->data)<0)//dato<arbol->dato
        {
            arbol->izq= bstree_insertar(arbol->izq, dato,fcopia, fcomparar);
        }
        else if(fcomparar(dato, arbol->data) > 0){
            arbol->der=bstree_insertar(arbol->der, dato,fcopia , fcomparar);
        }

        return arbol;
        
     }

/**
 * Recorrido DSF del arbol
 */
void bstree_recorrer(BSTree arbol, BSTreeRecorrido ordenRecorrido, 
    FuncionVisitanteExtra visit, void *extra){
    
        if(arbol == NULL) return;

        if(ordenRecorrido == BTREE_RECORRIDO_PRE)
            visit(arbol->data, extra);
        bstree_recorrer(arbol->izq, ordenRecorrido, visit, extra);
        if(ordenRecorrido == BTREE_RECORRIDO_IN)
            visit(arbol->data, extra);
        bstree_recorrer(arbol->der, ordenRecorrido, visit, extra);
        if(ordenRecorrido == BTREE_RECORRIDO_POST)
            visit(arbol->data, extra);
        
}

BSTree bstree_eliminar(BSTree arbol, void *dato,
FuncionComparadora fcomparar, FuncionDestructora fdestruir){

    if(arbol == NULL) return NULL;

    if(fcomparar(dato, arbol->data)==0){
        if((arbol->der == NULL) && (arbol->izq == NULL)){
            fdestruir(arbol->data);
            free(arbol);
            arbol= NULL;
        }
        else if((arbol->der == NULL)){
            BSTree nodoAeliminar= arbol;
            arbol= arbol->izq;
            fdestruir(nodoAeliminar->data);
            free(nodoAeliminar);
        }
        else if((arbol->izq == NULL)){
            BSTree nodoAeliminar= arbol;
            arbol= arbol->der;
            fdestruir(nodoAeliminar->data);
            free(nodoAeliminar);
        }
        else{
            BSTree datoReemplazo= bstree_minimo_derecho(arbol);
            BSTree datoAeliminar= arbol;
            printf("%s\n",(char*) datoReemplazo->data);
            arbol = datoReemplazo;
            fdestruir(datoAeliminar);
            free(datoAeliminar);
        }
    }
    else if(fcomparar(dato, arbol->data)<0)//dato<arbol->dato
    {
        arbol->izq= bstree_eliminar(arbol->izq, dato,fcomparar, fdestruir);
    }
    else if(fcomparar(dato, arbol->data) > 0){
        arbol->der= bstree_eliminar(arbol->der, dato,fcomparar , fdestruir);
    }
    return arbol;
}

BSTree bstree_minimo_derecho(BSTree arbol){
    if(arbol == NULL) return NULL;
    BSTree nodo= arbol->der;
    void* datoRoot= arbol->data;
    while(nodo->izq != NULL){
        nodo= nodo->izq;
    }
    return nodo;
}

void* no_copia(void* nodo){
    return nodo;
}
void no_destruir(void* nodo){
    return;
}
BSTree bstree_k_esimo_menor(BSTree arbol, int k){

    Pila pilaNodos= pila_crear();
    BSTree nodoActual = arbol;
    int i=0;
     
    while((pilaNodos != NULL) || (nodoActual !=NULL  )){
        while(nodoActual != NULL){
            pilaNodos= pila_apilar(pilaNodos, nodoActual, no_copia);
            nodoActual= nodoActual->izq;
            
        }
        nodoActual=pila_desapilar(&pilaNodos, no_destruir, no_copia);
        
        i++;
        if(i == k){
            break;
        }
        nodoActual= nodoActual->der;
    } 
    pila_destruir(pilaNodos, no_destruir);
    return nodoActual;
} 



/**
 * determina de el valor de un nodo esta entre las cotas c1 y c2
 */

int bstree_cota_aux(void* c1, void* c2, BSTree nodo, FuncionComparadora fcomparar){

    if(nodo == NULL) return 1;

    if(c1!=NULL && (fcomparar(nodo->data,c1) <= 0)){
        return 0;
    }
    if(c2!=NULL && (fcomparar(nodo->data, c2)>=0)){
        return 0;
    }
    // c1<nodo-data && nodo->data<c2
    return bstree_cota_aux(c1, nodo->data, nodo->izq, fcomparar) && 
        bstree_cota_aux(nodo->data,c2, nodo->der, fcomparar);
    
}   
/**
 * determina si un ABB es valido
 */

 int bstree_ABB_valido(BSTree arbol, FuncionComparadora fcomparar){
    return bstree_cota_aux(NULL, NULL,arbol ,fcomparar);

 }

 /**
  * que dado un entero k, busque en el arbol binario
    de busqueda el menor entero mayor a k.
    Se asume arbol de enteros
  */
int bstree_cota_inferior(BSTree arbol, int k, FuncionComparadora comp){

    assert(arbol != NULL);

    _BST_Nodo* nodo= arbol;
    int* cota;
    while( nodo != NULL){
        cota= nodo->data;
        if(comp(&k, nodo->data)<0)
            nodo= nodo->izq;
        else
            nodo=nodo->der;
        
    }
    if(comp(&k,cota)>0){
        printf("NO exite el menor entero mayor a k\n");
        return k;
    }
    return *cota;


 }

/**
 *  que visite a los datos en el intervalo [cota inf cota sup].
 */
void bstree_recorrer_intervalo(BSTree arbol,int cotainf, int cotasup, FuncionVisitanteExtra visit, FuncionComparadora comp){
     
    if(arbol == NULL)
        return;
    
    bstree_recorrer_intervalo(arbol->izq, cotainf, cotasup, visit, comp);

    if((comp(&cotainf, arbol->data)<=0) && (comp(&cotasup, arbol->data)>=0))
        visit(arbol->data, NULL);

    bstree_recorrer_intervalo(arbol->der, cotainf, cotasup, visit, comp);
}


static void bstree_to_cdlist_aux(BSTree arbol,cdlist nuevaLista){
    if(arbol){
        bstree_to_cdlist_aux(arbol->izq, nuevaLista);
        if(nuevaLista->ultimo == NULL){
            nuevaLista->primero= arbol;
        }
        else{
            arbol->izq= nuevaLista->ultimo;
            nuevaLista->ultimo->der= arbol;
        }
        nuevaLista->ultimo= arbol;

        bstree_to_cdlist_aux(arbol->der, nuevaLista);
    }
}
cdlist bstree_to_cdlist(BSTree arbol){
    cdlist nuevaLista= malloc(sizeof(_cdlist));

    nuevaLista->primero= NULL;
    nuevaLista->ultimo=NULL;

    bstree_to_cdlist_aux(arbol, nuevaLista);

    nuevaLista->primero->izq= nuevaLista->ultimo;
    printf("as%d\n",*(int*)nuevaLista->primero->izq->data);
    nuevaLista->ultimo->der= nuevaLista->primero;
    return nuevaLista;
}

void bstree_cdlist_recorrer(cdlist lista, FuncionVisitanteExtra func, int sentidoLista){

    
    if(sentidoLista == 0){
        _BST_Nodo* anterior= lista->primero;
        for(_BST_Nodo* siguiente= lista->primero; anterior != lista->ultimo ; siguiente= siguiente->der){
            func(siguiente->data, NULL);
            anterior=siguiente;
        }
    }
    else{
        _BST_Nodo* anterior= lista->ultimo;
        for(_BST_Nodo* siguiente= lista->ultimo; anterior != lista->primero ; siguiente= siguiente->izq){
            func(siguiente->data, NULL);
            anterior=siguiente;
        }
    }
}

void bstree_cdlist_destruir(cdlist lista, FuncionDestructora destr){

    _BST_Nodo* nodoAdestruir;
    lista->ultimo->der=NULL;
    while(lista->primero != NULL){
        nodoAdestruir= lista->primero;
        lista->primero= lista->primero->der;
        destr(nodoAdestruir->data);
        free(nodoAdestruir);
    }
    free(lista);
}

int bstree_es_completo(BSTree arbol){
    
}