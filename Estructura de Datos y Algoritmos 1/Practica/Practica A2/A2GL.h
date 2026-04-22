#ifndef __A2GSL_H__
#define __A2GSL_H__

#include "../plantillas/colas/Lcolas.h"

typedef struct{
    GNode* inicio;
    GNode* final;
    int tam;
}IList;

typedef IList* List;

/*
*Dada una cola, la convierte en una IList
*/
List cola_a_lista(Cola cola);

/**
 * metodo mergesort
 */
void merge_sort(List lista);

/**
 * ordenamiento qsort para arrays de enteros
 */
void qsort_int(List lista);

void qsort_3(List lista);
#endif