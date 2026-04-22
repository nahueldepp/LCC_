#include "matriz.h"
#include <stdio.h>

void imprimir_matriz(Matriz* mPtr,int fil, int col){

    printf("\n ---------------\n");
    for(int i = 0; i < fil; i++ ){
        printf("\n");
        printf("|");
        for(int j= 0; j< col; j++){
            printf("%5.1f ",matriz_leer_pos(mPtr, i, j));
        }
        printf("|"); 
    }
    printf("\n");
}

int main(void){

    size_t cantFilas= 6;
    size_t cantColumnas= 6;

    Matriz* m= matriz_crear(cantFilas,cantColumnas);
    
    int k= 1;
    for(int i = 0; i < cantFilas; i++ ){
        printf("\n");
        printf("|");
        
        for(int j= 0; j< cantColumnas; j++, k++){

            matriz_escribir_pos(m, i, j, k );
            printf("%5.1f ",matriz_leer_pos(m, i, j));
        }
        printf("|");
        
    }

    matriz_intercambiar_filas(m, 0, 5);

    imprimir_matriz(m, cantFilas,  cantColumnas);
    
    double filExtra[]={0.1, 0.2 ,0.3 , 0.4, 0.5, 0.6};
    matriz_insertar_fila(&m,5,filExtra);

    imprimir_matriz(m, cantFilas + 1,  cantColumnas);
    
    matriz_destruir(m);
}