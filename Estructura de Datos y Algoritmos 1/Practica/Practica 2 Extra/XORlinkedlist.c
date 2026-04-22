#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct _XNode{
    int dato;
    struct _XNode* xnp; 
}XNode;

typedef XNode* XList;
XNode* XOR(XNode* prev, XNode* curr){
    return (XNode*) ((unsigned long)prev^(unsigned long)curr);
}

typedef void(*FuncionVisitante)(XNode* xlista);
XList xlist_crear(){
    return NULL;
}

XList xlist_agregar_principio(XList xlist, int dato){

    XNode* nuevoNodo= malloc(sizeof(XNode));
    nuevoNodo->dato= dato;
    nuevoNodo->xnp= XOR(NULL, xlist);
    
     if(xlist !=NULL){
        xlist->xnp= XOR(nuevoNodo, xlist->xnp);
        printf("xlist %p\n", xlist);
        printf("xlist->xnp %p\n",XOR(nuevoNodo, xlist->xnp));
     }
    printf("nuevonodo= %p\n ", nuevoNodo);
    return nuevoNodo;
}

void xlist_destruir(XList lista){

    XNode* prev= NULL;
    XNode* sig;
    while(lista != NULL){
        sig= XOR(prev, lista->xnp);
        prev= lista;
        free(lista);
        lista= sig;
    }
}

void xlist_recorrer(XList xlist, FuncionVisitante fun){
    XNode* prev= NULL;
    XNode* sig;
    while( xlist ){
        printf("dato %d\n", xlist->dato);
        sig= XOR(prev, xlist->xnp);
        prev= xlist;
        xlist= sig;
    }
    
    puts(" ");
}

void xlist_imprimir_dato(XNode* nodo){
    printf("%d ",nodo->dato);
}

int main(void){
 
    XList lista= NULL;
    XNode a, b;
    XNode* p= &a;
    XNode* q= &b;

    printf("p=%p\n",p);
    printf("q=%p\n",q);
    printf("%p\n",XOR(p,NULL));


    lista= xlist_agregar_principio(lista, 4);
    lista= xlist_agregar_principio(lista, 3);
    lista= xlist_agregar_principio(lista, 2);
    lista= xlist_agregar_principio(lista, 1);


    
    xlist_recorrer(lista, (FuncionVisitante)xlist_imprimir_dato);

    xlist_destruir(lista); 

    //printf("%p\n",XOR(r,p));
    return 0;
}