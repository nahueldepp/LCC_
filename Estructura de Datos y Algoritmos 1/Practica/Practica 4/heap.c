#include "headers/heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define RIGHT(i) (2 * (i + 1))
#define LEFT(i) ((2 * i) + 1)
#define PARENT(i) ((i-1)/2)

#define HEAP_SIZE 1024

void swap(void** a, void** b){
    void* aux = *a;
    *a = *b;
    *b = aux;
}

BHeap bheap_crear(FuncionComparadora comp, FuncionCopiadora copy,FuncionDestructora destr){
    BHeap bHeap = malloc(sizeof(struct _BHeap));
    bHeap->arr = malloc(sizeof(void*)*HEAP_SIZE);
    bHeap->capacidad = HEAP_SIZE;
    bHeap->comp = comp;
    bHeap->destr = destr;
    bHeap->copy = copy;
    bHeap->ultimo = -1;
    return bHeap;
}

void bheap_destruir(BHeap bHeap){
    bheap_recorrer(bHeap->destr, bHeap);
    free(bHeap->arr);
    free(bHeap);
}

int bheap_vacio(BHeap bHeap){
    return bHeap->ultimo == -1;
}

void bheap_recorrer(FuncionVisitante visit, BHeap bHeap){
    for(int i = 0; i <= bHeap->ultimo; i++){
        visit(bHeap->arr[i]);
    }
}

static void flotar(BHeap heap, int i){
    
    for(i; i>0 && 

        (heap->comp(heap->arr[i], heap->arr[PARENT(i)])>0); i/=2){
        //intercambio con el padre
        swap(heap->arr + i, heap->arr+ PARENT(i) );
    }

}



/**
 * agrega un elemento al heap, 
 * realocando el arreglo en caso de ser necesario
 * el resultado debe ser nuevamente ser un heap binario
 */
void bheap_insertar(void* dato,BHeap heap){

    if(heap->ultimo+ 1 == heap->capacidad){
        heap->capacidad = heap->capacidad * 2;
        heap->arr= realloc(heap->arr,sizeof(void*) * heap->capacidad );
    }
    //se inserta el elemento al final del heap
    heap->arr[++heap->ultimo]= heap->copy(dato);
    //se flota el elemento hasta la pos final
    flotar(heap, heap->ultimo);

}


static void hundir(BHeap heap, int i){
    int esMayor= 1;
    int n = heap->ultimo;
    while(LEFT(i)<=n && esMayor){
        int k= LEFT(i);
        
        if(k+1<=n && (heap->comp(heap->arr[k+1],heap->arr[k]))>0){
            k=k+1; //el hijo derecho es mayor
            
        }
        if(heap->comp(heap->arr[i],heap->arr[k])>0){
            esMayor=0; //es mayor que ambos
        }
        else{
            swap(heap->arr + k, heap->arr + i);
            i=k;
        }

    }
}
/**
 * elimina un elemento del heap, el resultado debe ser 
 * un heap binario
 */

void bheap_eliminar(void* data, BHeap bHeap){
    int pos = -1;
    int i = 0;

    // Buscamos la primera aparicion del elemento
    while (pos == -1 && i <= bHeap->ultimo) {

        if (bHeap->comp(data, bHeap->arr[i]) == 0) {
            pos = i;
        }

        i++;

    }

    if(pos == -1){
        printf("El elemento no se encuentra en el arbol\n");
        return;
    }

    //Si el elemento estaba en el arbol, lo quitamos y lo reemplazamos por el ultimo.
    void* elem = bHeap->arr[pos];
    bHeap->arr[pos] = bHeap->arr[bHeap->ultimo--];

    // Destruimos el dato
    bHeap->destr(elem);

    // Ubicamos el dato segun corresponda
    if (pos > 0  && bHeap->comp(bHeap->arr[pos], bHeap->arr[PARENT(pos)]) > 0) {
        flotar(bHeap, pos);
    } 
    else {
        hundir(bHeap, pos);
    }
}


BHeap bheap_crear_desde_arr(void **arr, int largo, FuncionComparadora comp, FuncionCopiadora copy, FuncionDestructora destr){

    BHeap bHeap = malloc(sizeof(struct _BHeap));
    bHeap->comp = comp;
    bHeap->copy = copy;
    bHeap->destr = destr;
    bHeap->capacidad = largo;
    bHeap->ultimo = largo-1;
    bHeap->arr = arr;
    
    // Convertimos en bheap. Notar que la ultima mitad del array son todas hojas
    for(int i = largo / 2; i >= 0; i --){
        hundir(bHeap, i);
    }
    return bHeap;
}

static void* dummy_copy(void* dato){
    return dato;
}

static void dummy_destr(void* dato){
    (void) dato;
    return;
}

void* bheap_pop(BHeap bHeap){
    void* max = bHeap->arr[0];
    // Reemplazamos la raiz por el ultimo
    bHeap->arr[0] = bHeap->arr[bHeap->ultimo--];
    // Hundimos la nueva raiz hasta su posición final
    hundir(bHeap, 0);
    return max;
}

void heapSort(void** arr, int largo, FuncionComparadora comp){
    BHeap bHeap = bheap_crear_desde_arr(arr, largo, comp, dummy_copy, dummy_destr);
    for(int i = largo - 1; i >= 0; i--){
        void* max = bheap_pop(bHeap);
        bHeap->arr[i] = max;
    }
    free(bHeap);
}