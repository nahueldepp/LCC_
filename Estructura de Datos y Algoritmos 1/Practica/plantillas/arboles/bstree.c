#include "headers/bstree.h"
#include "headers/pilas.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>





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

    printf("a\n");
    if(fcomparar(dato, arbol->data)==0){
        printf("b\n");
        if((arbol->der == NULL) && (arbol->izq == NULL)){
            printf("1\n");
            fdestruir(arbol->data);
            free(arbol);
            arbol= NULL;
        }
        else if((arbol->der == NULL)){
            printf("2\n");
            BSTree nodoAeliminar= arbol;
            arbol= arbol->izq;
            fdestruir(nodoAeliminar->data);
            free(nodoAeliminar);
        }
        else if((arbol->izq == NULL)){
            printf("3\n");
            BSTree nodoAeliminar= arbol;
            arbol= arbol->der;
            fdestruir(nodoAeliminar->data);
            free(nodoAeliminar);
        }
        else{
            printf("4\n");
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

    if(!((fcomparar(nodo->data,c1)>0) && (fcomparar(nodo->data,c2)<0))){
        printf("%s\n", (char*)nodo->data);
        return 0;
    }
    // c1<nodo-data && nodo->data<c2
    else{
        int izq;
        int der;
        izq= bstree_cota_aux(c1, nodo->data, nodo->izq, fcomparar);
        der= bstree_cota_aux(nodo->data,c2, nodo->der, fcomparar);
        return izq<der? izq:der;
    }
}   
/**
 * determina si un ABB es valido
 */

 int bstree_ABB_valido(BSTree arbol, FuncionComparadora fcomparar){

    int cotaInf=(int)-INFINITY;
    int cotaSup= (int)INFINITY;
    return bstree_cota_aux(&cotaInf,&cotaSup,arbol ,fcomparar);

 }