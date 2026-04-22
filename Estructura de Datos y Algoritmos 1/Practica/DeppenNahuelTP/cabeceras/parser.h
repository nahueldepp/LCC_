#ifndef __PARSER_H__
#define __PARSER_H__
#include "tablahash.h"

typedef enum{DEFF, DEFL, APPLY, SEARCH, EXIT} Operaciones;
/**
 * Dada una linea de texto y una lista de tokens, tokeniza la linea al formato necesario
 * donde ,;][{}<>= son tokens individuales
 * retora el número de tokens en caso de tokenizar con exito, 0 en caso contrario
 */
int tokenizar(char texto[], char* tokens[]);

/**
 * libera los espacios en memoria apuntados en tokens[i]
 */
void liberar_tokens(char* tokens[]);

/**
 * retorna 1 si la declaracion de defl esta bien definida, 0 en otro caso
 * ademas revisa si todas las funciones declaradas en el cuerpo de la función estan previamente definidas
 */
int parse_defl(char* tokens[],int numTokens);

/**
 * Retorna 1 si la declaración de deff esta bien definida, 0 en caso contrario
 */
int parse_deff(char* tokens[],int numTokens,TablaHash tablaFunc);

/**
 * Retorna 1 si la declaración de apply es aplicada a una lista generica [z,X,y] y esta bien definida
 * Retorna 2 si la declaracón de apply es aplicada a una lista definida previamente
 * 0 en caso contrario
 */
int parse_apply(char* tokens[], int  numTokens, TablaHash tablaLista);

/**
 * Retorna 1 si la declaración de search esta bien definida, 0 en caso contrario
 */
int parse_search(char* tokens[], int  numTokens, TablaHash tablaListas);

/**
 * determina el tipo de declaración ingresada y devuelve su tipo
 */
int parse_intruccion(char* token);
#endif