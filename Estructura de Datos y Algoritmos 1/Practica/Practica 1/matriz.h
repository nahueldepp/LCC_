#ifndef _MATRIZ_H
#define _MATRIZ_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Matriz_ Matriz;

//crea una matriz de tamñao filXcol
Matriz* matriz_crear(size_t fil, size_t col);

//devueve el número de columnas de la matriz
size_t matriz_num_columnas(Matriz* mPtr);

//devuelve el número de filas de la matriz
size_t matriz_num_filas(Matriz* mPtr);

//destruye, libera el espacio usado para la matriz
void matriz_destruir(Matriz* mPtr);

//dada una posicion (fil,col), escribe un dato 
void matriz_escribir_pos(Matriz* mPtr, size_t fil, size_t col, double dato);

//devuelve el dato en la posicion [fil][col]
double matriz_leer_pos(Matriz* mPtr, size_t fil, size_t col);

//intercambia dos filas
void matriz_intercambiar_filas(Matriz* mPtr, size_t filI, size_t filK);

//inserta una fila nueva en la posicion nada
void matriz_insertar_fila(Matriz** mPtr, size_t posFil, double* filaExtra);

#endif