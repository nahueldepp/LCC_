#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "A2GL.h"


/* IMPLEMENTACION DE LOS ALGORITMOS DE ORDENAMIENTO DE A2 PARA LISTAS GENERALES SIMPLEMENTE ENLAZADAS */


/*
*Dada una cola, la convierte en una IList
*/
List cola_a_lista(Cola cola){

    List lista= malloc(sizeof(IList));
    lista->final= cola->final;
    lista->inicio= cola->inicio;
    int tam;
    for(GNode* temp=cola->inicio; temp != NULL; temp= temp->next){
        tam++;
    }
    lista->tam= tam;
    return lista;
}

void lista_desruir(List lista, FuncionDestructora destr){

    while(lista->inicio != NULL){
        GNode* nodoAdestruir = lista->inicio;
        lista->inicio= lista->inicio->next;
        destr(nodoAdestruir);
        free(nodoAdestruir);
    }
    free(lista);
}
/**
 * cambia los elementos dadas dos posiciones en un array
 */

 static void swap(void** a, void** b){
    void* aux = *a;
    *a = *b;
    *b = aux;
 }


/**
 * metodo mergesort
 */

GNode* combinar( GNode* inicioL1 , GNode* inicioL2 ){
    

    
    GNode* nuevaLista= NULL;
    GNode* nodoF = NULL;
    if (inicioL1->data < inicioL2->data){
            nuevaLista = inicioL1;
            nodoF=nuevaLista;
            inicioL1= inicioL1->next;
        }
    else {
        nuevaLista = inicioL2;
        nodoF= nuevaLista;
        inicioL2= inicioL2->next;
    }

    while (inicioL1 && inicioL2)
    {
        if (inicioL1->data < inicioL2->data){
            nuevaLista = inicioL1;
            inicioL1= inicioL1->next;
        }
        else {
            nuevaLista = inicioL2;
            inicioL2= inicioL2->next;
        }
        
    }
    
    if(inicioL1)
        nodoF->next = inicioL1;

    else
        nodoF->next = inicioL2;

    return nuevaLista;

}
static void merge_sort_R(List lista, GNode* inicio, GNode* final, int tam){
    if(tam<2)
        return;

    int mitadI= (tam )/2;
    GNode* medio = inicio;
    for(int i=1; i<=mitadI; i++){
        medio= medio->next;
    }
    GNode* incioL2= medio->next;
    medio->next= NULL;
    merge_sort_R(lista, inicio, medio, mitadI);
    merge_sort_R(lista, incioL2, final, tam-mitadI);

    inicio = combinar(inicio , incioL2);
    
    GNode* temp= inicio;
    for(temp; temp->next != NULL; temp= temp->next);
    lista->final= temp;
    lista->inicio= inicio;
}


void merge_sort(List lista, int tam){
    
    merge_sort_R( lista, lista->inicio,lista->final, tam);
}

/**
 * ordenamiento qsort para arrays de enteros
 */

 /**
  * particion de Lomuto
  * devuelve la cantidad de elementos <=pivot
  */
static int particionar(int* arr, int pivot,int inicio, int fin){
    int j= inicio;
    for(int i= inicio; i < fin; i++){
        if(arr[i] <= pivot){
            int temp= arr[i];
            arr[i]= arr[j];
            arr[j]= temp;
            j++;
        }
    }
    return j;
}

static void qsort_int_R(int* arr, int inicio, int fin){
    if(inicio >=  fin)
        return;
    int pivot= arr[fin];
    int pos= particionar(arr, pivot,inicio ,fin);//marca donde empieza la forontera
    arr[fin]= arr[pos];
    qsort_int_R(arr, inicio, pos-1);// parte izquierda
    qsort_int_R(arr, pos+1 , fin);//parte derecha

 }
void qsort_int(int* arr,int tam){
    assert(arr!= NULL);
    qsort_int_R(arr, 0, tam);
}

/**
 * qsort con particion dijkstra
 * particiona el array en 3 [<p | p== | p<]
 */
static void  qsort_3_R(int arr[], int inicio, int fin){
    
    if(inicio >= fin)
        return;
    int lt= inicio, gt= fin; //  lowerThan gretarThan
    int i= inicio;
    int pivot= arr[fin];
    while(i <= gt ){
        if(arr[i] < pivot){
            int temp= arr[i];
            arr[i++]= arr[lt];
            arr[lt++]= temp;
            
        }
        else if(arr[i] > pivot){
            int temp= arr[i];
            arr[i]= arr[gt];
            arr[gt--]= temp;
        }
        else
            i++;
    }
    
    qsort_3_R(arr,inicio, lt-1);
    qsort_3_R(arr, gt + 1, fin);
}

void qsort_3(int arr[], int tam){
    
    qsort_3_R(arr, 0, tam);
}