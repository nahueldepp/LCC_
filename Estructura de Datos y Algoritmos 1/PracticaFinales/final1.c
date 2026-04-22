#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>

typedef struct bstNodo_{
    int dato;
    struct bstNodo_ *der, *izq;
} bstNodo;

typedef bstNodo* BSTSet;

//declare y defina

/**
 * crarBST(): ()->BSTSet
 * retorna un arbol binario vacio
 */

BSTSet crearBST(void){
    
    return NULL;
}

/**
 * agregarBST(): int, BSTSet-> BSTSet
 * agrega un elemento al arbol teniendo en cuanta las propiedades de conjuntos
 * 
 */

BSTSet agregarBST(int valor, BSTSet root){
    if(root == NULL){
        BSTSet nuevoNodo= malloc(sizeof(bstNodo));
        nuevoNodo->dato= valor;
        nuevoNodo->der= NULL;
        nuevoNodo->izq= NULL;
        return nuevoNodo;
    }
    else if(valor< root->dato)
        root->izq= agregarBST(valor, root->izq);//agrego a la izquierda
    else if(valor> root->dato)
        root->der= agregarBST(valor,root->der);//agrego a la derecha

    return root;
}


/**
 * busquedaBST(): BSTSet int -> bool
 * retorna 1 si el valor se encuentra en el conjujnto, 0   en caso contrario 
 */

 int busquedaBST(BSTSet root, int valor){
    if(root == NULL)
        return 0; 
    if(root->dato == valor){
        return 1;
    }
    int boolIzq=0;
    int boolDer=0;
    if( valor< root->dato){
        boolIzq= busquedaBST(root->izq, valor);
    }
    else if(valor>root->dato){
        boolDer= busquedaBST(root->der, valor);
    }

    return boolDer>boolIzq?boolDer:boolIzq;

 }
/**
 * imprimeBST(): ()->()
 * imprime todos los elementos del conjunto, sin repetir, y en orden asecendente
 * 
 */
void imprimeBST(BSTSet root){
    if(root ==NULL)
        return;
    if(root->izq != NULL)
        imprimeBST(root->izq);
    printf("%d ", root->dato);
    if(root->der != NULL)
        imprimeBST(root->der);
}

void interseccion_aux(BSTSet a,BSTSet b, BSTSet* inter ){

    if(a == NULL)
        return;
    if(busquedaBST(b, a->dato))
        *inter= agregarBST(a->dato, *inter);
    interseccion_aux(a->izq,b,inter);
    interseccion_aux(a->der,b,inter);
}
/**
 * interseccionBST()
 * Calcula el resultado de la interseccion de dos conjuntos
 * 
 */

BSTSet interseccionBST( BSTSet arbol1, BSTSet arbol2){

    BSTSet interseccion= crearBST(); 
    
    interseccion_aux(arbol1, arbol2, &interseccion);
    return interseccion;

}

/**
 * 
 */

void lejanoBST_aux(int k, BSTSet root, int* lejano, int* distancia){
    if(root == NULL){
        return;
    }
    int distNodo= abs(k - root->dato);
    if(*distancia < distNodo){
        *distancia= distNodo;
        *lejano= root->dato;
    }
    lejanoBST_aux(k,root->izq ,lejano, distancia);
    lejanoBST_aux(k,root->der ,lejano, distancia);

}
/**
 * lejanoBST(): int BSTSet -> int
 * devuelve el número del conjunto mas lejano a k, el conjunto es vacio devuelve k
 */
int lejanoBST(int k, BSTSet root){
    int lejano= k;
    int distancia=0;
    lejanoBST_aux(k,root, &lejano, &distancia);
    return lejano;
}


int main(void){

    BSTSet a= crearBST();
    BSTSet b= crearBST();

    a= agregarBST(1,a);
    a= agregarBST(5,a);
    a= agregarBST(7,a);
    a= agregarBST(3,a);

    b= agregarBST(6,b);
    b= agregarBST(5,b);
    b= agregarBST(4,b);
    b=agregarBST(1,b);

    imprimeBST(a);
    puts("");
    imprimeBST(b);

    BSTSet inter= interseccionBST(a,b);
    puts("");
    imprimeBST(inter);
    puts("");
   printf("%d\n", lejanoBST(-15,a));
   printf("%d\n", strcmp("b","ca"));
}