#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define TAM_INI 20
#define PARENT(i) ((i-1)/2)
#define LEFT(i) ((i*2)+1)
#define RIGHT(i) ((i+1)*2)
/**
 * Apluicacion de max heap para enteros
 */
typedef struct heap{
    int* arr;
    unsigned capacidad;
    int ultimo;// indice donde se incertó el ultimo elemento
}*BHeap;

/**
 * Crea un Bheap vacio con el tamaño inicial predefinido
 */
BHeap bheap_cear(){

    BHeap nuevoHeap= malloc(sizeof(struct heap));
    nuevoHeap->arr= malloc(sizeof(int)* TAM_INI);
    nuevoHeap->capacidad=TAM_INI;
    nuevoHeap->ultimo= -1;
    return nuevoHeap;
}


/**
 * flotar(): BHeap int -> void
 * Flota el elemento que se encuntra en la posicion dada
 */

void flotar(BHeap bheap, int pos){

    for(int i= pos; i>0 && bheap->arr[PARENT(i)]<bheap->arr[i]; i=(i-1)/2){
        int temp= bheap->arr[PARENT(i)];
        bheap->arr[PARENT(i)]= bheap->arr[i];
        bheap->arr[i]= temp;
    }
}


/**
 * bheap_insertar(): BHeap int -> void
 * Agrega un elemento al heap manteniendo la propiedad de maxHeap
 */
void bheap_insertar(BHeap bheap, int dato){

    //en el caso que no exista más espacio
    if(bheap->ultimo + 1 == bheap->capacidad){
        bheap->capacidad= bheap->capacidad*2;
        bheap->arr= realloc(bheap->arr,sizeof(int)*bheap->capacidad);
    }

    bheap->arr[++bheap->ultimo]= dato;
    flotar(bheap,bheap->ultimo);
}

/**
 * hundir(): BHeap int -> void
 * Unde el primer elemento del heap
 */
void hundir(BHeap bheap,int pos){

    int esMayor= 1;
    int ultimo= bheap->ultimo;
    //mientras haya algun hijo y el elemento a hundir sea mayor q alguno de sus hijos
    while(LEFT(pos)<= ultimo && esMayor){
        int hijo= LEFT(pos);
        //si existe el hijo derecho y ademas este es mayor
        if(hijo + 1 <= ultimo && bheap->arr[hijo]<bheap->arr[hijo + 1 ]){
            hijo= hijo +1;
        } 
        //chequeo si el hijo mayor es mayor que su padre
        if(bheap->arr[hijo]<bheap->arr[pos])
            esMayor =0;
        else{
            int temp= bheap->arr[pos];
            bheap->arr[pos]=bheap->arr[hijo];
            bheap->arr[hijo]= temp;
        }
    }
    
}

void bheap_eliminar(BHeap bheap, int dato){

    if(bheap->ultimo == -1)
        return;
    
    int encontrado=0;
    int pos, i=0;
    while(i <= bheap->ultimo && !encontrado){
        if(bheap->arr[i]== dato){
            pos= i;
            encontrado =1;
        }
        
        i++;
    }
    //el dato no se encuentra en la lista
    if(encontrado == 0)
        return;
    
    //piso el dato en la posicion pos con el ultimo dato del array
    //reduzco la cantidad de elemnetos
    bheap->arr[pos]= bheap->arr[bheap->ultimo--];
    
    if(pos>0 && bheap->arr[pos]>bheap->arr[PARENT(pos)]){
        flotar(bheap,pos);
    }
    
}
/**
 * bheap_destruir(): BHeap -> void
 * destruye un Bheap
 */
void bheap_destruir(BHeap bheap){
    free(bheap->arr);
    free(bheap);
}


void bheap_recorrer(BHeap bheap){

    for(unsigned i=0; i<=bheap->ultimo;i++){
        printf("%d\t|",i);
    }
    puts("");
    for(unsigned i=0; i<=bheap->ultimo;i++){
        printf("%d\t|", bheap->arr[i]);
    }
    puts("");
}

int main(){
    
    srand(time(NULL));
    BHeap heap= bheap_cear();
    
    for(unsigned i = 0; i<8; i++){
        bheap_insertar(heap, rand()%50);
    }
    bheap_insertar(heap, 16);
    bheap_recorrer(heap);
    puts("");
    bheap_eliminar(heap,16);
    bheap_recorrer(heap);
    bheap_destruir(heap);
}