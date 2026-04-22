#include <stdio.h>
#include <stdlib.h>

void combinar(int *array, int inicio, int mitad, int fin){
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

void merge_sort_R(int *array, int inicio, int fin){
    if(inicio >= fin)
        return;

    int mitad = inicio + (fin - inicio) / 2;

    merge_sort_R(array, inicio, mitad);
    merge_sort_R(array, mitad  + 1, fin);

    combinar(array , inicio , mitad , fin);
}

void merge_sort(int *array, int tam){
    merge_sort_R(array, 0, tam -1);
}

//Se pide que realice una implementacion 
//de mergesort para listas de enteros respetando el nombrede las funciones dadas


typedef struct _INodo{
    int dato;
    struct _INodo* next;
}INodo;

typedef struct{
    INodo* inicio;
    INodo* final;
    int tam;
}IList;

void combinarL(INodo* inicio,INodo* mitad, INodo* final, int tam){
    int tam_izq = (tam + 1)/2;
    int tam_der = tam - tam_izq;

    IList a_izq;
    INodo* temp=inicio;
        for(int i=1; i<= tam_izq; i++,temp = temp->next){
            INodo* nuevoNodo= malloc(sizeof(INodo));
            nuevoNodo->dato= temp->dato;
            nuevoNodo->next= NULL;

            if(i == 1){
                a_izq.inicio= nuevoNodo;
                a_izq.final= nuevoNodo;
            }
            a_izq.final->next=nuevoNodo;
            a_izq.final= nuevoNodo;
        }
        temp=mitad->next;
        for(int i=1; i<= tam_izq; i++,temp = temp->next){
            INodo* nuevoNodo= malloc(sizeof(INodo));
            nuevoNodo->dato= temp->dato;
            nuevoNodo->next= NULL;

            if(i == 1){
                a_izq.inicio= nuevoNodo;
                a_izq.final= nuevoNodo;
            }
            a_izq.final->next=nuevoNodo;
            a_izq.final= nuevoNodo;
        }


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


void merge_sort_RL(INodo* inicio, INodo* final, int tam){
    if(inicio == final)
        return;

    int mitadInt = (tam + 1)/2;
    INodo* mitad;
    for(int i = 0; i<= mitadInt; i++ ){
        mitad= inicio->next;
    }

    merge_sort_R(inicio, mitad, mitadInt);
    merge_sort_R(mitad->next,final, tam-mitadInt+1);

    combinarL(inicio, mitad , final, tam);
}


void merge_sort_lista(IList lista, int tam){
    merge_sort_RL(lista.inicio, lista.final, lista.tam);
}