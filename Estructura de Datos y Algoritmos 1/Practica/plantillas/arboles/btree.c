#include "btree.h"
#include "../pilas/pilas.h"
#include "../colas/Lcolas.h"
#include <stdio.h>
#include <stdlib.h>



/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear(){
    return NULL;
}

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo){
    return nodo == NULL;
}


/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo, FuncionDestructora destruir){

    if(btree_empty(nodo)) return;

    btree_destruir(nodo->left,destruir);
    btree_destruir(nodo->right,destruir);
    destruir(nodo->dato);

    free(nodo);
}

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(void* dato, BTree left, BTree right, FuncionCopia copia){

    BTree nuevoArbol= malloc(sizeof(BTNodo));
    nuevoArbol->dato= copia(dato);
    nuevoArbol->left = left;
    nuevoArbol->right = right;
    return nuevoArbol;
}

/**
 * Recorrido del arbol, utilizando la funcion pasada. Mediante DFS
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,
    FuncionVisitante visit){

    if (arbol == NULL)
        return;
      
    if (orden == BTREE_RECORRIDO_PRE)
    visit(arbol);

    btree_recorrer(arbol->left, orden, (FuncionVisitante)visit);

    if (orden == BTREE_RECORRIDO_IN)
    visit(arbol);

    btree_recorrer(arbol->right, orden,(FuncionVisitante) visit);

    if (orden == BTREE_RECORRIDO_POST)
    visit(arbol);
}

void* no_copia(void* dato){
    return dato;
}
void no_destruir(void* dato){
    return;
}

void btree_recorrer_pre_it(BTree arbol, FuncionVisitanteInt visit, 
    FuncionCopia copia, FuncionDestructora destruir){

    if(arbol == NULL) return;

    Pila pilaNodos= pila_crear();

    pilaNodos= pila_apilar(pilaNodos, arbol,(FuncionCopia) copia);

    while( !pila_es_vacia(pilaNodos) ){

        BTree nodoActual= pila_tope(pilaNodos);
        visit(nodoActual);

        pilaNodos= pila_desapilar(pilaNodos,(FuncionDestructora) destruir, (FuncionCopia)copia);

        if(nodoActual->right != NULL){
            pilaNodos= pila_apilar(pilaNodos, nodoActual->right, (FuncionCopia)copia);
        }
        if(nodoActual->left != NULL){
            pilaNodos= pila_apilar(pilaNodos, nodoActual->right, (FuncionCopia)copia);
        }

    }
    
    pila_destruir(pilaNodos, no_destruir);
}
 
int btree_nnodos(BTree arbol){
    if(btree_empty(arbol)) return 0;

    int i= 1;
    i = i + btree_nnodos(arbol->left);
    i = i + btree_nnodos(arbol->right);

    return i;
}

/**
 *retorna 1 si el núumero dado se encuentra en el árbol, y 0 en caso contrario
 */
int btree_buscar(BTree arbol, void* x, FuncionComparadora comparar){

    if(btree_empty(arbol)) return 0;

    if(comparar(arbol->dato, x)){
        return 1;
    }
    int izq= btree_buscar(arbol->left, x, comparar);
    int der= btree_buscar(arbol->right, x, comparar);

    return izq>der? izq:der;
}

BTree btree_copiar(BTree arbol, FuncionCopia copia ){
    BTree nuevoArbol= btree_crear();
    
    if(btree_empty(arbol)) return NULL;

    nuevoArbol = btree_unir(arbol->dato,btree_copiar(arbol->left, copia),
    btree_copiar(arbol->right,copia),copia);

    return nuevoArbol;
}

/**
 * retorna la altura de un arbol (distancia desde la raiz hata la hoja mas lejana)
 */
int btree_altura(BTree arbol){

    if(btree_empty(arbol)) return -1;

    int depthDerecha= btree_altura(arbol->right);
    int depthIzquierda= btree_altura(arbol->left);

    return 1 + (depthDerecha >= depthIzquierda? depthDerecha:depthIzquierda);

}

int btree_nnodos_profundidad(BTree arbol, int profundidad){
    if(btree_empty(arbol)) return 0;

    if(profundidad == 0) return 1;

    return btree_nnodos_profundidad(arbol->left, profundidad - 1) +
         btree_nnodos_profundidad(arbol->right, profundidad - 1);
}

/**
 * retorna la profundiad del nodo que contiene el núemro dado, -1 si el número no se encuentra en el arbol
 */
int btree_profundidad_dato(BTree arbol, void* dato, FuncionComparadora comparar){

    if(btree_empty(arbol)) return -1;

    if(comparar(arbol->dato, dato)) return 0;

    int izq= btree_profundidad(arbol->left, dato);
    int der= btree_profundidad(arbol->right, dato);

    if(izq == -1 && der == -1){
        return -1;
    }
    else{
        return 1 + (izq != -1? izq:der);
    }

}

int btree_sumar(BTree arbol){
    if(btree_empty(arbol)) return 0;

   
    int sumaIzquierda= btree_sumar(arbol->left);
    int sumaDerecha= btree_sumar(arbol->right);

    return arbol->dato + sumaIzquierda + sumaDerecha;
}

void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden, 
                            FuncionVisitanteExtra funExtra, void* extra){

    if(btree_empty(arbol)) return;

    if(orden ==BTREE_RECORRIDO_PRE ){
        funExtra(arbol->dato, extra);
    }
    btree_recorrer_extra(arbol->left, orden, funExtra, extra);
    if(orden ==BTREE_RECORRIDO_IN ){
        funExtra(arbol->dato, extra);
    }
    btree_recorrer_extra(arbol->right, orden, funExtra, extra);
    if(orden ==BTREE_RECORRIDO_POST ){
        funExtra(arbol->dato, extra);
    }
}

void btree_valores_nivel(BTree arbol, FuncionVisitante funVisit, int profundiad){
    if(btree_empty(arbol)) return;

    if(profundiad == 0){
        funVisit(arbol);
    }
    btree_valores_nivel(arbol->left, funVisit, profundiad -1);
    btree_valores_nivel(arbol->right, funVisit, profundiad -1);
}

void btree_recorrer_rbfs(BTree arbol, FuncionVisitante visit){

    if(btree_empty(arbol)) return;

    int altura= btree_altura(arbol);
    
    for(int i= 0; i<=altura; i++){
        btree_valores_nivel(arbol, visit,i );
    }
    
} 

/**
 * breadth first search usanco colas; 
 * 
 */
void btree_recorrer_bfs(BTree arbol, FuncionVisitante visit, 
    FuncionCopia fcopia, FuncionDestructora fdestruir){
    if(btree_empty(arbol)) return;
    
    Cola colaNodos = cola_crear();
    BTree nodo= arbol;
    colaNodos= cola_encolar(colaNodos, nodo, fcopia);


    printf("b\n");
    while(!cola_es_vacia(colaNodos)){
        GNode* nodo= cola_inicio(colaNodos);
        BTree nodoB= nodo->data;
        if(!btree_empty(nodoB->left))
            colaNodos= cola_encolar(colaNodos,nodoB->left, fcopia);

        if(!btree_empty(nodoB->right))
            colaNodos = cola_encolar(colaNodos, nodoB->right, fcopia);
        BTree dato= cola_desencolar(colaNodos,fdestruir, fcopia);
        visit(dato);
    }

    cola_destruir(colaNodos,fdestruir);
}


BTree  btree_mirror(BTree arbol){
    if(arbol == NULL)
        return NULL; 
    BTNodo* temp= arbol->left;
    arbol->left= btree_mirror(arbol->right);
    arbol->right= btree_mirror(temp);
    return arbol;
}


/**
 * determina si el arbol es completo o no (es decir  sus niveles tienen todos los nodos posibles, excepto quizas
 el ultimo nivel, que se encuentra lleno de izquierda a derecha.)
 retorna 1 si esta completo, 0 en caso contrario 
 */
int btree_es_completo(BTree arbol){
    if(arbol == NULL)
        return 0;
    int ambosHijos= 1;
    int completo= 1;

    Cola colaNodos= cola_crear();
    colaNodos= cola_encolar(colaNodos, arbol, no_copia);
    
    while( completo && !cola_es_vacia(colaNodos) ){
        GNode* nodoCola = cola_inicio(colaNodos);
        BTNodo* nodoActual= nodoCola->data;

        if( !ambosHijos && (nodoActual->left || nodoActual->right)){
            completo= 0;
        }

        if(!nodoActual->left || !nodoActual->right)   
            ambosHijos= 0;

        if(!btree_empty(nodoActual->left)){
            colaNodos= cola_encolar(colaNodos,nodoActual->left, no_copia);
        }

        if(!btree_empty(nodoActual->right))
            colaNodos = cola_encolar(colaNodos, nodoActual->right, no_copia);

        cola_desencolar(colaNodos,no_destruir, no_copia);

    }
    cola_destruir(colaNodos, no_destruir);

    return completo;

}