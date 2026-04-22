#include "arregloenteros.h"
#include <stdlib.h>
#include <stdio.h>

//crear_arreglo_enteros: int ->ArregloEnteros
ArregloEnteros* arreglo_enteros_crear(int capacidad){

    ArregloEnteros* arr;
    arr= (ArregloEnteros*)malloc(sizeof(ArregloEnteros));
    if(arr == NULL){
        return NULL;
    }
    arr->direccion=malloc(sizeof(int)*capacidad);

    if (arr->direccion == NULL)
    {   
        
        free(arr);

    }
    
    arr->capacidad= capacidad;
    return arr;
}

//b)
//destruir_arreglo_enteros; ArregloEnteros* -> void
void arreglo_enteros_destruir(ArregloEnteros* arrPtr){
    free(arrPtr->direccion);
    free(arrPtr);
}

//c)

int arreglo_enteros_leer(ArregloEnteros* arrPtr, int pos){

    return *(arrPtr->direccion +  pos);
}

//d)
void arreglo_enteros_escribir(ArregloEnteros* arrPtr, int pos, int dato){

    *(arrPtr->direccion + pos)= dato;
}

//e)
int arreglo_enteros_capacidad(ArregloEnteros* arrPtr){

    return arrPtr->capacidad;
}

//f)

void arreglo_enteros_imprimir(ArregloEnteros* arrPtr){
    for(int i= 0; i < arrPtr->capacidad ; i++){
        printf("%d, ", arreglo_enteros_leer(arrPtr, i));
    }
    printf("\n");
}


//4)

// ajustar_arreglo_enteros(): ArregloEnteros*, int  -> void
//ajusta el tamanño del arreglo. SI la nueva capacidad es menor, el contenido debe ser truncado
void arreglo_enteros_ajustar(ArregloEnteros* arrPtr, int capacidad){

    int tamanoArreglo= arreglo_enteros_capacidad(arrPtr);

    ArregloEnteros* nuevoArreglo= arreglo_enteros_crear(capacidad);

    for(int i = 0; i < capacidad; i++){
        arreglo_enteros_escribir(nuevoArreglo,i,arreglo_enteros_leer(arrPtr,i));
    }

    free(arrPtr->direccion);
    arrPtr->direccion= nuevoArreglo->direccion;
    arrPtr->capacidad= capacidad;
    free(nuevoArreglo);
    

}
//insertar_arreglos_enteros(): ArregloEnteros*, int, int ->void
//insreta el dato en la posicion dada, moviendo odos los elementos desdee esa posicion un lugar a la derecha
//(se incrementa el tamaño del arreglo)
void arreglo_enteros_insertar(ArregloEnteros* arrPtr,int pos, int dato){

    int nuevaCapacidad= arreglo_enteros_capacidad(arrPtr)+1;
    arreglo_enteros_ajustar(arrPtr, nuevaCapacidad );
    for(int i = nuevaCapacidad-1; pos < i; i--){

        arreglo_enteros_escribir(arrPtr, i, arreglo_enteros_leer(arrPtr,i-1));
    }
    arreglo_enteros_escribir(arrPtr, pos, dato);
}

//c

//arreglo_enteros_eliminar(): arrPtr, pos -> ArregloEnteros*
//elimina el dato en la posicion dada, moviendo todos los elementos posterioes un lugar a la izquerda( se reduce el tamaño del arreglo)
void arreglo_enteros_eliminar(ArregloEnteros* arrPtr, int pos){

    int nuevaCapacidad=arreglo_enteros_capacidad(arrPtr)-1;
    for(int i=pos; i < nuevaCapacidad; i++){
        arreglo_enteros_escribir(arrPtr,i,arreglo_enteros_leer(arrPtr,i+1));
    }
    arreglo_enteros_ajustar(arrPtr,nuevaCapacidad);
}