#include "matriz.h"
#include <stdio.h>


//** Implementacion utilizando un arreglo unidimencional (arreglo de doubles)
struct Matriz_{
    double* dato;

    size_t filas;

    size_t columnas;

};

//crea una matriz de tamñao filXcol
Matriz* matriz_crear(size_t fil, size_t col){

    Matriz* nuevaMatriz= malloc(sizeof(Matriz));

    nuevaMatriz->dato= malloc(sizeof(double) * fil * col);

    if (nuevaMatriz == NULL)
    {
        return NULL;
    }

    nuevaMatriz->columnas= col;
    nuevaMatriz->filas= fil;

    return nuevaMatriz;
    
}

//destruye, libera el espacio usado para la matriz
void matriz_destruir(Matriz* mPtr){

    free(mPtr->dato);
    free(mPtr);
}

//devueve el número de columnas de la matriz
size_t matriz_num_columnas(Matriz* mPtr){

    return mPtr->columnas;
}

//devuelve el número de filas de la matriz
size_t matriz_num_filas(Matriz* mPtr){

    return mPtr->filas;
}


//dada una posicion (fil,col), escribe un dato 
void matriz_escribir_pos(Matriz* mPtr, size_t fil, size_t col, double dato){

    size_t numeroColumnas= matriz_num_columnas(mPtr);

    *(mPtr->dato + (fil * numeroColumnas + col ))= dato;
}

//devuelve el dato en la posicion [fil][col]
double matriz_leer_pos(Matriz* mPtr, size_t fil, size_t col){

    size_t numeroColumnas= matriz_num_columnas(mPtr);

    return *(mPtr->dato + (fil * numeroColumnas + col ));
}

//dada una matriz, intercambia la fila i-esima por la fila k-esima
void matriz_intercambiar_filas(Matriz* mPtr, size_t filI, size_t filK){

    size_t numeroFilas= matriz_num_filas(mPtr);
    size_t numeroColumnas= matriz_num_columnas(mPtr);

    for(int j = 0; j < numeroColumnas; j++){
        double temp = matriz_leer_pos(mPtr, filI, j);
        matriz_escribir_pos(mPtr, filI, j, matriz_leer_pos(mPtr, filK, j));
        matriz_escribir_pos(mPtr, filK, j, temp);
    }
}

//agrega una nueva fila a la matriz(crea una matriz con mas una fila extra) y si el dato es dado, copia en esa fila
//el arraeglo dado (double*)
void matriz_insertar_fila(Matriz** mPtr, size_t posFil, double* filaExtra){

    size_t cantidadFilas= matriz_num_filas(*mPtr);
    size_t cantidadColumnas= matriz_num_columnas(*mPtr);

   

    Matriz* mTemp = matriz_crear(cantidadFilas + 1, cantidadColumnas);

    for(int i = 0; i < cantidadFilas; i++){
        for(int j = 0; j< cantidadColumnas; j++){
            matriz_escribir_pos(mTemp, i, j, matriz_leer_pos(*mPtr, i, j));
        }
    }

    //cantFilas=cantNuevasFilas - 1 , con lo cual es la posicion de la ultima fila (0:cantNuevaFila-1)
    matriz_intercambiar_filas(mTemp, posFil, cantidadFilas);

    printf(" marca \n");

    matriz_destruir(*mPtr);
    (*mPtr)->dato= mTemp->dato;
    (*mPtr)->filas= cantidadFilas + 1;
    free(mTemp);

     if(filaExtra){

        if((sizeof(filaExtra)/sizeof(filaExtra[0])) > (sizeof(double) * cantidadColumnas)){
            printf("La nueva fila debe tener el mismo largo que las prestablecidas\n ");
        }
        else{
            for(int j= 0; j< cantidadColumnas; j++){
                matriz_escribir_pos(*mPtr, posFil, j, filaExtra[j]);
            }
        }
    } 
}