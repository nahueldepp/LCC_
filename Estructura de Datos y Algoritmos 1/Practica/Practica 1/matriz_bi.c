#include "matriz.h"

//definimos arreglo bidimencional( arreglo de punteors a arreglo)

struct Matriz_
{
    double** dato;

    size_t filas;

    size_t columnas;
};


//crea una matriz de tamñao filXcol
Matriz* matriz_crear(size_t fil, size_t col){

    Matriz* nuevaMatriz=malloc(sizeof(Matriz));

    if(nuevaMatriz == NULL){
        free(nuevaMatriz);
        printf("Error al asignar memoria\n");
        return NULL;
    }
    
    nuevaMatriz->dato =(double** )malloc(sizeof(double *) * fil);

    for(int i= 0; i < fil; i++){

        nuevaMatriz->dato[i]= malloc(sizeof(double) * col);

        if (nuevaMatriz->dato[i]==NULL)
        {
            free(nuevaMatriz->dato[i]);
            printf("Error al asignar memoria\n");

            return NULL;
        }
        
    }
    
    nuevaMatriz->columnas= col;
    nuevaMatriz->filas= fil;

    return nuevaMatriz;
}

//devueve el número de columnas de la matriz
size_t matriz_num_columnas(Matriz* mPtr){

    return mPtr->columnas;
}

//devuelve el número de filas de la matriz
size_t matriz_num_filas(Matriz* mPtr){

    return mPtr->filas;
}

//destruye, libera el espacio usado para la matriz
void matriz_destruir(Matriz* mPtr){

    for(int i= 0; i < matriz_num_filas(mPtr); i++){
        free(mPtr->dato[i]);
    }

    free(mPtr->dato);
    free(mPtr);
    
}

//dada una posicion (fil,col), escribe un dato, 0<=fil<filas, 0<=col<columnas
void matriz_escribir_pos(Matriz* mPtr, size_t fil, size_t col, double dato){

    mPtr->dato[fil][col] = dato;
}

//devuelve el dato en la posicion [fil][col], 0<=fil<filas, 0<=col<columnas
double matriz_leer_pos(Matriz* mPtr, size_t fil, size_t col){

    return mPtr->dato[fil][col];
}

//dada una matriz, intercambia la fila i-esima por la fila k-esima
void matriz_intercambiar_filas(Matriz* mPtr, size_t filI, size_t filK){

    
    size_t numeroColumnas= matriz_num_columnas(mPtr);

    for(int j = 0; j < numeroColumnas; j++){

        double temp = mPtr->dato[filI][j];
        mPtr->dato[filI][j]=mPtr->dato[filK][j];
        mPtr->dato[filK][j]= temp;
        
    }
}

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

     matriz_destruir(*mPtr);
     (*mPtr)->dato= mTemp->dato;
     (*mPtr)->filas= cantidadFilas + 1;
     free(mTemp);
 
    if(filaExtra){

        if(sizeof(filaExtra)/sizeof(filaExtra[0]) > (sizeof(double) * cantidadColumnas)){
            printf("La nueva fila debe tener el mismo largo que las prestablecidas\n ");
        }
        else{
            for(int j= 0; j< cantidadColumnas; j++){
                matriz_escribir_pos(*mPtr, posFil, j, filaExtra[j]);
            }
        }
    }
 }
