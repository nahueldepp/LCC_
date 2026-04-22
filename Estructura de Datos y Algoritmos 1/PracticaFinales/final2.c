#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * Arbol binario de palabras
 */
struct Palabras_{
    char* palabra;
    struct Palabras_ *izq, *der;
} ;

typedef struct Palabras_* BSTPalabras;



/**
 * devuelve un arbol  de palabras vacio
 */
BSTPalabras crearPalabras(void){
    return NULL;
}

BSTPalabras insertar_palabra(BSTPalabras root, char* palabra){

    if(root== NULL){
        BSTPalabras nuevoNodo= malloc(sizeof(struct Palabras_));
        int largoP= strlen(palabra)+1;
        nuevoNodo->palabra= malloc(sizeof(char)* largoP);
        strcpy(nuevoNodo->palabra,palabra);
        nuevoNodo->der= NULL;
        nuevoNodo->izq= NULL;
        return nuevoNodo;
    }
    else if(strcmp(root->palabra, palabra)>0){
        root->izq= insertar_palabra(root->izq, palabra);
    }
    else if(strcmp(root->palabra, palabra)<0){
        root->der= insertar_palabra(root->der, palabra);
    }
    return root;

}

BSTPalabras menor_mayor(BSTPalabras root){
    BSTPalabras nodoAnt= root;
    BSTPalabras nodo= root;
    for(nodo; nodo->izq != NULL;nodoAnt= nodo, nodo= nodo->izq);
    if(nodoAnt != nodo){
        nodoAnt->izq= nodo->der;
    }
    nodo->der= NULL;
    return nodo;
        
}

BSTPalabras eliminar_palabra(BSTPalabras root, char* palabraAeliminar){

    if(root == NULL){
        return NULL;
    }
    if(strcmp(root->palabra, palabraAeliminar)==0){
        //free(root->palabra);
        if(root->der && root->izq){
            BSTPalabras menorNodoMayor= menor_mayor(root);
            BSTPalabras nodoAeliminar= root;
            menorNodoMayor->izq= nodoAeliminar->izq;
            menorNodoMayor->der= nodoAeliminar->der;
            free(nodoAeliminar->palabra);
            free(nodoAeliminar);
            return menorNodoMayor;
        }
        else if(root->der){
            BSTPalabras nodoDerecho= root->der;
            free(root->palabra);
            free(root);
            return nodoDerecho;
        }
        else if(root->izq){
            free(root->palabra);
            BSTPalabras nodoizq= root->izq;
            free(root);
            return nodoizq;
        }
        else{
            free(root->palabra);
            free(root);
            return NULL;
        }
    }
    else if(strcmp(root->palabra, palabraAeliminar)>0){
        root->izq= eliminar_palabra(root->izq, palabraAeliminar);
    }
    else
        root->der= eliminar_palabra(root->der, palabraAeliminar);

    return root;
}

void imprimir_palabras(BSTPalabras root){
    if(root == NULL)
        return;
    imprimir_palabras(root->izq);
    printf("%s ",root->palabra);
    imprimir_palabras(root->der);
}

char* buscar_palabra(BSTPalabras root, char* palabra){
    
    if(root== NULL)
        return NULL;
    char* palabraEncontrada= strstr(root->palabra, palabra);
    if(palabraEncontrada){
        printf("%s\n", palabraEncontrada);
        return palabraEncontrada;
    }
    buscar_palabra(root->izq, palabra);
    buscar_palabra(root->der, palabra);
}


void contar_ocurrencias_aux(BSTPalabras palabras, char c, int* ocurrencias){

    if(palabras == NULL)
        return;
    if(palabras->palabra[0] == c)
        (*ocurrencias)++;
    contar_ocurrencias_aux(palabras->izq, c, ocurrencias);
    contar_ocurrencias_aux(palabras->der, c, ocurrencias);
}
int contar_ocurrencias(BSTPalabras palabras, char c){

    int ocurrencias= 0;
    contar_ocurrencias_aux(palabras, c, &ocurrencias);
    return ocurrencias;
}

//ejercicio 2 

typedef void* (*FuncionCopia)(void* dato);
typedef void (*FuncionDestructora)(void* dato);
typedef void (*FuncionVisitante)(void* dato);
typedef int (*FuncionComparadora)(void* d1, void* d2);

typedef struct Gnodo_{
    void* data;
    struct Gnodo_ *ant, *sig;
}GNodo;

typedef struct GLista_{
    GNodo *primero, *ultimo;
    int numNodos;
}GLista;


GLista glista_crear(void){
    GLista nuevaLista;
    nuevaLista.numNodos= 0;
    nuevaLista.primero= NULL;
    nuevaLista.ultimo= NULL;
    return nuevaLista;
}

GLista glista_agregar_inicio(GLista lista, void* dato, FuncionCopia copy){
    
    GNodo* nuevoNodo= malloc(sizeof(GNodo));
    nuevoNodo->data= copy(dato);
    nuevoNodo->ant= NULL;
    nuevoNodo->sig= lista.primero;
    if(lista.primero == NULL){
        lista.ultimo= nuevoNodo;
    }
    else{
        lista.primero->ant= nuevoNodo;
    }
    lista.numNodos+=1;
    lista.primero= nuevoNodo;
    return lista;
}
GLista glista_agregar_final(GLista lista, void* dato, FuncionCopia copy){
    
    GNodo* nuevoNodo= malloc(sizeof(GNodo));
    nuevoNodo->data= copy(dato);
    nuevoNodo->sig= NULL;
    nuevoNodo->ant= lista.ultimo;
    if(lista.primero == NULL){
        lista.primero= nuevoNodo;
    }
    else{
        lista.ultimo->sig= nuevoNodo;
    }
    lista.numNodos++;
    lista.ultimo= nuevoNodo;
    return lista;
}

void glista_eliminar_lista(GLista lista, FuncionDestructora destr){

    if(lista.primero == NULL)
        return;
    GNodo* nodoSig= lista.primero->sig;
    destr(lista.primero->data);
    free(lista.primero);
    lista.primero= nodoSig;
    glista_eliminar_lista(lista, (FuncionDestructora) destr);
}

void glista_recorrer(GLista lista, FuncionVisitante visit){

    GNodo* nodo= lista.primero;
    for(nodo; nodo != NULL; nodo= nodo->sig){
        visit(nodo->data);
    }
}

GLista glista_mezclar(GNodo* nodoL1, GNodo* nodoL2, int len1,int len2,FuncionComparadora comp, FuncionCopia copy){

    
    GLista nuevaLista= glista_crear();
    int i=1, j=1;
    while(i<=len1 || j<= len2){
        if(nodoL1 && nodoL2){
            if(comp(nodoL1->data,nodoL2->data)<0){
                nuevaLista= glista_agregar_final(nuevaLista, nodoL1->data,(FuncionCopia) copy);
                nodoL1=nodoL1->sig;
                i++;
            }
            else {
                nuevaLista= glista_agregar_final(nuevaLista,nodoL2->data,(FuncionCopia) copy);
                nodoL2= nodoL2->sig;
                j++;
            }
            
        }
        else if (nodoL1 == NULL){
            nuevaLista= glista_agregar_final(nuevaLista,nodoL2->data,(FuncionCopia) copy);
            nodoL2= nodoL2->sig;
            j++;
        }
        else{
            nuevaLista= glista_agregar_final(nuevaLista, nodoL1->data,(FuncionCopia) copy);
            nodoL1=nodoL1->sig;
            i++;
        }
        
    }
    
    return nuevaLista;


}

GLista glista_mezclar_3(GLista lista1,GLista lista2, GLista lista3, FuncionCopia copy, FuncionComparadora comp){

    GLista ordenada1=glista_crear();
    GLista ordenada2=glista_crear();
    ordenada1= glista_mezclar(lista1.primero,lista2.primero,lista1.numNodos,lista2.numNodos,(FuncionComparadora)comp,(FuncionCopia)copy);
    ordenada2= glista_mezclar(ordenada1.primero,lista3.primero,ordenada1.numNodos,lista3.numNodos,(FuncionComparadora)comp,(FuncionCopia)copy);
    return ordenada2;
}

GLista glista_ordenar(GLista lista, FuncionCopia copy, FuncionComparadora comp){

    if(lista.numNodos <2 ){
        return lista;
    }

    GLista l1= glista_crear();
    GLista l2= glista_crear();
    GLista l3= glista_crear();
    
    if(lista.numNodos == 2){
        l1.primero= lista.primero;
        l1.numNodos++;
        lista.primero->sig = NULL;
        l2.primero= lista.ultimo;
        l2.numNodos++;
        l3.primero= NULL;
        return glista_mezclar_3(l1,l2,l3,copy,comp);
    } 
    else{
        
    }
void ejer1(){
    BSTPalabras palabras= crearPalabras();

    palabras= insertar_palabra(palabras,"miau");
    palabras= insertar_palabra(palabras,"piau");
    palabras= insertar_palabra(palabras,"chau");
    palabras= insertar_palabra(palabras,"douuu");
    palabras= insertar_palabra(palabras,"paall");
    palabras= insertar_palabra(palabras,"paalll");
    imprimir_palabras(palabras);
    puts("");
    printf("ocurrencias %d", contar_ocurrencias(palabras,'d'));
    buscar_palabra(palabras,"majullll");
    palabras= eliminar_palabra(palabras,"miau");
    palabras= eliminar_palabra(palabras,"piau");
    palabras= eliminar_palabra(palabras,"chau");
    palabras= eliminar_palabra(palabras,"douuu");
    palabras= eliminar_palabra(palabras,"paall");
    //imprimir_palabras(palabras);
    puts("");
}

int* copiar_entero(int* n){
    int* copian= malloc(sizeof(int));
    *copian= *n;
    return copian;
}
void destruir_puntero_entero(int* n){
    free(n);
}
int comparar_puntero_entero(int* a, int* b){
    return *a-*b;
}
void imprimir_puntero_entero( int* n){
    printf("%d ", *n);
}

void ejer2(){

    int numeros[10]={1,2,102,4,5,6,7,15,80,60};
    GLista lista1= glista_crear();
    lista1=glista_agregar_final(lista1,numeros,(FuncionCopia)copiar_entero);
    /* lista1=glista_agregar_final(lista1,numeros+1,(FuncionCopia)copiar_entero);
    lista1=glista_agregar_final(lista1,numeros+2,(FuncionCopia)copiar_entero); */
    glista_recorrer(lista1, (FuncionVisitante)imprimir_puntero_entero);
    puts("");

    GLista lista2= glista_crear();
    lista2=glista_agregar_final(lista2,numeros+7,(FuncionCopia)copiar_entero);
    /* lista2=glista_agregar_final(lista2,numeros+8,(FuncionCopia)copiar_entero);
    lista2=glista_agregar_final(lista2,numeros+9,(FuncionCopia)copiar_entero); */
    glista_recorrer(lista2, (FuncionVisitante)imprimir_puntero_entero);
    puts("");

    GLista lista3= glista_crear();
    lista3=glista_agregar_final(lista3,numeros+3,(FuncionCopia)copiar_entero);
    /* lista3=glista_agregar_final(lista3,numeros+4,(FuncionCopia)copiar_entero);
    lista3=glista_agregar_final(lista3,numeros+5,(FuncionCopia)copiar_entero); */
    glista_recorrer(lista3, (FuncionVisitante)imprimir_puntero_entero);
    puts("");

    GLista ordenada= glista_crear();
    ordenada= glista_mezclar_3(lista2, lista3, ordenada, (FuncionCopia)copiar_entero, (FuncionComparadora)comparar_puntero_entero);
    glista_recorrer(ordenada, (FuncionVisitante)imprimir_puntero_entero);
    puts("");
}


int main(void){

    ejer2();
    
    return 0;
}