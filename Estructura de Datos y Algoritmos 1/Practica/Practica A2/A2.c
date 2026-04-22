#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "A2.h"


/**
 * cambia los elementos dadas dos posiciones en un array
 */

 static void swap(void** a, void** b){
    void* aux = *a;
    *a = *b;
    *b = aux;
 }


/**
 * Busqueda binaria para arreglo de enteros
 * devuelve el indice i deonde se encuentra el valor x o -1 en caso contrario
 */
int binserach(int a[], int len, int x){

    if(a[0] > x || a[len] < x)
        return -1;
    int der, izq, med;
    der= len - 1;
    izq= 0;
    med= (der + izq) /2;

    while( izq < der && a[med] != x ){

        if(a[med] < x)
            izq= med + 1;
        else
            der= med - 1;
        med= (der + izq)/2;
    }
    if(izq < der)
        return -1;
    return med;
}
/**
 * Se recorre haciendo swaps adyacentes
 */
void bubble(int* a){

    int size= sizeof(a)/sizeof(a[0]);
    int cambio= 1;
    while(cambio){
        cambio = 0;
        for(int i= 0; i< size - 2; i++){
            if(a[i] > a[i + 1]){
                int temp= a[i];
                a[i]= a[i + 1];
                a[i+1] = temp;
                cambio= 1;
            }
        }
    }
} 

/**
 * se lleva un prefijo ordenado( el array detras de cierto a[i]) y se agregan elementos de a uno
 */

void insertion(int* a){
    int size = sizeof(a)/sizeof(a[0]);
    
    for(int i= 1; i < size; i++){
        int j= i-1;
        int key = a[i];

        /*mueve los elementos de a[0 ... i-1] que son mayores a la llave
        a una posición deleante de su ubicacion actual*/
        while(j >= 0 && a[j] > key){
            a[j+1]= a[j];
            j -= 1;
        }
        a[j + 1]= key;
    }
}


/**
 * metodo mergesort
 */

void combinar(int* array ,int inicio ,int  mitad ,int  fin){
     int tam_izq = mitad - inicio +1;
    int tam_der = fin - mitad;

    int *a_izq = malloc(sizeof(int)* tam_izq);
    int *a_der = malloc(sizeof(int ) * tam_der);

    for (int i = 0; i < tam_izq; i++){
        a_izq[i] = array[i + inicio];
    }
    for(int i=0; i < tam_der; i++){
        a_der[i] = array[i + mitad +1];
    }
    int min = 0;
    for(int i = 0, j=0, k= inicio; k<= fin; k++){
        if(i < tam_izq && (j >= tam_der || a_izq[i] <= a_der[j])){
            min = a_izq[i];
            i++;
        }
        else{
            min = a_der[j];
            j++;
        }
        array[k]=min;
    }
    free(a_izq);
    free(a_der);
    
}
static void merge_sort_int_R(int *array, int inicio, int fin){
    if(inicio >= fin)
        return;

    int mitad= (inicio + fin )/2;
    merge_sort_int_R(array, inicio, mitad );
    merge_sort_int_R(array, mitad+1, fin);

    combinar(array , inicio , mitad , fin);
}


void merge_sort_int(int *array,int tam){
    
    merge_sort_int_R(array, 0, tam);
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