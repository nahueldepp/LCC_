#include "treap.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Treap treap_crear(){
    return NULL;
}

static Treap rotacion_der(Treap root){

    Treap hijoIzq= root->izq;

    root->izq= hijoIzq->der;
    hijoIzq->der= root;
    return hijoIzq;
}

static Treap rotacion_izq(Treap root){

    Treap hijoDer= root->der;

    root->der= hijoDer->izq;
    hijoDer->izq= root;

    return hijoDer;
}
Treap treap_insertar(Treap root, int dato){

    if(root == NULL){
        Treap nuevoNodo= malloc(sizeof(T_Nodo));
        nuevoNodo->der= NULL;
        nuevoNodo->izq= NULL;
        nuevoNodo->key= dato;
        nuevoNodo->priority= rand()%100;
        return nuevoNodo;
    }
    //dato>root->key
    else if(dato>root->key){
        root->der= treap_insertar(root->der, dato);
        while(root->der && root->priority<root->der->priority)
            root= rotacion_izq(root);
    }
    else{
        root->izq= treap_insertar(root->izq, dato);
        while(root->izq && root->priority<root->izq->priority)
            root== rotacion_der(root);
    }
    return root;
}

Treap treap_eliminar(Treap root, int dato){
    if(root == NULL)
        return NULL;
    
    if(root->key<dato){
        root->der= treap_eliminar(root->der, dato);
        return root;
    }
    else if(root->key>dato){
        root->izq= treap_eliminar(root->izq, dato);
        return root;
    }
    
    else{
        if(root->der && root->izq){
            //si el nodo de la derecha tiene mas prioridad que el de la izquierda lo subo
            if(root->der->priority>root->izq->priority) {
                root= rotacion_izq(root);
                root->der= treap_eliminar(root->der,dato);
            }
            else{
                root= rotacion_der(root);
                root->izq= treap_eliminar(root->izq,dato);
            }
        }
        //el nodo es una hoja o tiene un soloo hijo
        else{
            
            Treap reeemplazo= root->der==NULL?root->izq:root->der;
            free(root);
            root= reeemplazo;
        }
        return root;
    }
    

}

//Treap treap_cantiodad

void treap_destruir(Treap root){
    if(root == NULL)
        return;
    treap_destruir(root->izq);
    treap_destruir(root->der);
    free(root);

}

void treap_recorrer(Treap root, int sentido){

    if(root== NULL)
        return;
    if(sentido == 1)
        printf("key: %d\tpriority: %d\n", root->key,root->priority);
    treap_recorrer(root->izq,sentido);

    if(sentido==2)
        printf("key: %d\tpriority: %d\n", root->key,root->priority);

    treap_recorrer(root->der,sentido);
}


int main(){

    srand(time(NULL));
    Treap arbol= treap_crear();

    for(int i= 0; i< 5; i++){
        arbol = treap_insertar(arbol,i);
    }
    puts("");
    treap_recorrer(arbol,1);
    printf("inorder\n");
    treap_recorrer(arbol,2);
    arbol= treap_eliminar(arbol, 4);
    arbol= treap_eliminar(arbol, 2);
    arbol = treap_insertar(arbol,1);
    
    puts("");
    treap_recorrer(arbol,1);
    printf("inorder\n");
    treap_recorrer(arbol,2);
    puts("");
    treap_destruir(arbol);
    return 0;
}