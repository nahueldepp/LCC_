#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum color {Rojo, Azul, Neutro} Color;

typedef struct Nodo_{
    char* cdato;
    Color colorNodo;
    struct Nodo_ *der, *izq;
}Nodo;

typedef Nodo* ArbolBinarioColoreado;


ArbolBinarioColoreado arbol_crear(void){
    return NULL;
}

ArbolBinarioColoreado arbol_insertar(ArbolBinarioColoreado root, char* cdato, Color color){
    if(root == NULL){
        Nodo* nuevoNodo= malloc(sizeof(Nodo));
        nuevoNodo->cdato=malloc(sizeof(char)* (strlen(cdato)+1));
        strcpy(nuevoNodo->cdato, cdato);
        nuevoNodo->colorNodo= color;
        nuevoNodo->der=NULL;
        nuevoNodo->izq=NULL;
        return nuevoNodo;
    }
    //el dato es mayor, se va a la derecha
    printf("stcmp: %d nodo:%s palabra: %s\n ",strcmp(root->cdato,cdato),root->cdato,cdato );
    if(strcmp(root->cdato,cdato)<0)//root->cdato<cdato
        root->der= arbol_insertar(root->der, cdato, color);
    //se inserta a la izquierda
    else    
        root->izq= arbol_insertar(root->izq, cdato,color);
    //si el dato ya estaba en el arbol no se hace nada
    return root;
    
}

void color_aux(ArbolBinarioColoreado inicio,unsigned* numRojos, unsigned* numAzules){
    if(inicio == NULL)
    return;
    else if(inicio->colorNodo == Rojo)
        *numRojos+=1;
    else if(inicio->colorNodo== Azul)
        *numAzules+=1;
    color_aux(inicio->izq, numRojos, numAzules);
    printf("colorNodo: %d palabra: %s\n ",inicio->colorNodo, inicio->cdato);
    color_aux(inicio->der, numRojos, numAzules);
    return;
}
//retorna el color del arbol
Color color(ArbolBinarioColoreado inicio){
    unsigned numRojos=0, numAzules=0;
    color_aux(inicio,&numRojos,&numAzules);
    Color color= numRojos>numAzules?Rojo:Azul;
    if(color<2)
        return color;
    else
        return Neutro;

}

//recorre recursivamente el arbol contando la cantidad de hojas puras, teniendo en cuenta que la raiz es pura
void cantidad_puras_aux(ArbolBinarioColoreado inicio,unsigned antEsPura,Color colorHojaAnt,unsigned* numPuras){

    if(inicio == NULL)
        return;
    else if(antEsPura == 1 && inicio->colorNodo == colorHojaAnt){
        *numPuras +=1;
        cantidad_puras_aux(inicio->der,1,inicio->colorNodo,numPuras);
        cantidad_puras_aux(inicio->izq,1,inicio->colorNodo,numPuras);
    }
    else{
        cantidad_puras_aux(inicio->der,0,inicio->colorNodo,numPuras);
        cantidad_puras_aux(inicio->izq,0,inicio->colorNodo,numPuras);
        
    }
    
}
unsigned cantidad_puras(ArbolBinarioColoreado inicio){

    unsigned numPuras= 0;
    cantidad_puras_aux(inicio,1,inicio->colorNodo,&numPuras);
    return numPuras;
}
int main(){
    char* palabras[]={"d","b","f","e","a"};
    ArbolBinarioColoreado arbol= arbol_crear();
    
    /* for(unsigned i= 0; i<4; i++){
        Color color;
        if(i%2 == 0)
        color= Rojo;
        else
        color= Azul;
        arbol= arbol_insertar(arbol, palabras[i],color);
        } */
       
    arbol= arbol_insertar(arbol, palabras[0],Rojo);
    arbol= arbol_insertar(arbol, palabras[1],Rojo);
    arbol= arbol_insertar(arbol, palabras[2],Azul);
    arbol= arbol_insertar(arbol, palabras[3],Rojo);
    arbol= arbol_insertar(arbol, palabras[4],Rojo);
    Color colorArbol= color(arbol);
    printf("Color: %d", colorArbol);
    printf("NumPuras: %d\n", cantidad_puras(arbol));
    return 0;
}