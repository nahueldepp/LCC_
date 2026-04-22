/**
 * Las matrices esparsas, dispersas o ralas son un tipo particular de matrices que se distinguen por estar
 poco densamente pobladas, es decir, una baja proporción de sus entradas son distintas a 0. Naturale
mente, una representación de matriz esparsa que almacena las entradas nulas resulta en desperdicio de
 memoria. Teniendo en cuenta esto, se eligen representaciones más compactas que sacrifican algo de
 complejidad temporal para ganar en complejidad espacial.
 Por otro lado, se definen las matrices de adyacencia como 
 */

 //

#include <stdlib.h>
#include <stdio.h>

typedef struct Nodo_{
    int vecino;
    struct Nodo_* sig;
}Nodo;

typedef Nodo* Lista; 

// lista de adyacencia, 
typedef struct matrizAd{
    int numVertices;//cantidad de vertices(elementos)
    Lista* filas;//array que guarda listas de los vecinos de cada vertice

}MatrizAdyacencia;

// crea una lista vacia
Lista lista_crear(){
    
    return NULL;
}
//agrega un nuevo nodo al final de la lista
Lista lista_agregar(Lista lista,int dato){
    if(lista == NULL){
        Nodo* nuevoNodo= malloc(sizeof(Nodo));
        nuevoNodo->vecino= dato;
        nuevoNodo->sig=NULL;
        lista=nuevoNodo;
    }
    
    else if(lista->vecino != dato)
        lista->sig= lista_agregar(lista->sig, dato);
    return lista;
}

Lista lista_eliminar(Lista lista, int dato){
    if(lista == NULL)
        return lista;
        
    else if(lista->vecino == dato){
        Nodo* sig= lista->sig;
        free(lista);
        return sig;
    }
    else{    
        lista->sig= lista_eliminar(lista->sig, dato);
    }
    return lista;

}

void imprimir_lista(Lista lista){

    if(lista == NULL )
        return;
    else    
        printf("%d ", lista->vecino);
    imprimir_lista(lista->sig);
}
//crea  una matriz vacia n*n
MatrizAdyacencia matriz_crear(int numVertices){

    MatrizAdyacencia nuevaMatriz;
    nuevaMatriz.numVertices= numVertices;
    nuevaMatriz.filas= malloc(sizeof(Lista)*numVertices);
    return nuevaMatriz;
} 

//agrega la relación (i,j), haciendo que en la posicion filas[i] se agregue un nodo con vecino= j;
//si j o i no esta dentro de los parametros de la matriz, retorna la matriz sin modificación
void agregar_relacion(MatrizAdyacencia matriz, int i, int j){
    if(i>=matriz.numVertices || j>=matriz.numVertices){
        return ;  // por si i o j no esta dentro de los parametros de la matiz;
    }
    matriz.filas[i]= lista_agregar(matriz.filas[i], j);

}

/**
 * Dado una relacion (i,j), la elimina, si no existe no realiza cambios
 */
void eliminar_relacion(MatrizAdyacencia matriz, int i, int j){

    if(i>matriz.numVertices || j>matriz.numVertices){
        return ;  // por si i o j no esta dentro de los parametros de la matiz;
    }
    matriz.filas[i]= lista_eliminar(matriz.filas[i], j);
}


void imprimir_matriz(MatrizAdyacencia matriz){

    for(int i= 0; i<matriz.numVertices; i++ ){
        printf("%d: ", i);
        imprimir_lista(matriz.filas[i]);
        puts("");
    }
}

int pertenece(int x, Lista lista){

    int esta= 0;
    for(Nodo* nodo= lista; nodo!=NULL && !esta; nodo= nodo->sig){
        if(nodo->vecino == x)
            esta= 1;
    }
    return esta;
}
int es_simetrica(MatrizAdyacencia matriz){

    int esSimetrica= 1;
    for(int i = 0;i < matriz.numVertices && esSimetrica; i++ ){
        Lista filaI= matriz.filas[i];
        if(filaI !=  NULL){
            int parSimetrico= 1;
            Nodo* nodo= filaI;
            while (nodo!=NULL && parSimetrico ){
                int parSimetrico=pertenece(i, matriz.filas[nodo->vecino]);
                if(!parSimetrico)
                    esSimetrica= 0;
                nodo= nodo->sig;

            }

        }
    }

    return esSimetrica;
}

int rkleen(MatrizAdyacencia matriz, int i){
    
}
void main(){

    MatrizAdyacencia matriz= matriz_crear(5);
    agregar_relacion(matriz,0,3);
    agregar_relacion(matriz,4,3);
    eliminar_relacion(matriz, 4,3);
    agregar_relacion(matriz,1,5);
    agregar_relacion(matriz,0,4);
    agregar_relacion(matriz,3,0);
    agregar_relacion(matriz,4,0);
    agregar_relacion(matriz,3,2);
    agregar_relacion(matriz,2,3);

    imprimir_matriz(matriz);
    printf("es simatrica?: %d\n", es_simetrica(matriz));
    
}