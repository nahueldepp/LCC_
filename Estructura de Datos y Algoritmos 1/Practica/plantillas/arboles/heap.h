#ifndef __HEAP_H__
#define __HEAP_H__

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitanteExtra)(void *dato, void *extra);
typedef void (*FuncionVisitante) (void* dato);

typedef struct _BHeap{
    void **arr;
    int capacidad;
    int ultimo;
    FuncionComparadora comp;
    FuncionCopiadora copy;
    FuncionDestructora destr;
 } *BHeap;
/**
 * crea un heap vacío con una capicidad y una funcion de 
 * comparacion dadas
 */
BHeap bheap_crear(FuncionComparadora comp, FuncionCopiadora copy,FuncionDestructora destr);

/**
 * destruye el heap
 */
void bheap_destruir(BHeap bHeap);

/**
 * ratorna 1 si el heap está vacío y
 *  0 en caso contrario
 */

int bheap_vacio(BHeap );

/**
 * recorre los nodos utilizando busquedapor extension
 * ,aplicando la función dada en cada elemento
 */
void bheap_recorrer(FuncionVisitante visit, BHeap bHeap);

/**
 * agrega un elemento al heap, 
 * realocando el arreglo en caso de ser necesario
 * el resultado debe ser nuevamente ser un heap binario
 */
void bheap_insertar(void* data,BHeap bHeap);

/**
 * elimina un elemento del heap, el resultado debe ser 
 * un heap binario
 */
void bheap_eliminar(void* data, BHeap bHeap);

/**
 * A partir de un arreglo crea un heap binario
 */
BHeap bheap_crear_desde_arr(void **arr, int largo, FuncionComparadora comp, FuncionCopiadora copy, FuncionDestructora destr);

/**
 * popea el primer elemento de array
 */
void* bheap_pop(BHeap bHeap);

/**
 * Ordena usando un heap binario
 */
void heapSort(void** arr, int largo, FuncionComparadora comp);
#endif