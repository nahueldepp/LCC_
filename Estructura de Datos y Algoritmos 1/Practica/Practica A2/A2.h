#ifndef __A2_H__
#define __A2_H__

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitanteExtra)(void *dato, void *extra);
typedef void (*FuncionVisitante) (void* dato);

/**
 * Busqueda binaria para arreglo de enteros
 * devuelve el indice i deonde se encuentra el valor x o -1 en caso contrario
 */
int binserach(int a[], int len, int x);

/**
 * Se recorre haciendo swaps adyacentes
 */
void bubble(int* a); 

/**
 * se lleva un prefijo ordenado( el array detras de cierto a[i]) y se agregan elementos de a uno
 */

void insertion(int* a);

/**
 * metodo mergesort
 */
void merge_sort_int(int *array,int tam);

/**
 * ordenamiento qsort para arrays de enteros
 */
void qsort_int(int* arr,int tam);

void qsort_3(int arr[], int tam);
#endif