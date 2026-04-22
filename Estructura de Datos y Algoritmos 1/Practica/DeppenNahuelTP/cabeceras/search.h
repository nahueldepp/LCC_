#ifndef __SEARCH_H__
#define __SEARCH_H__

#include "listas.h"
#include "colas.h"
#include "funciones.h"
#include "tablahash.h"




/**
 * Estructura que guarda una lista de listas y el nombre de las funciones
 * que se usaron para obtenerlas(en orden)
 */
struct _Composicion{

    //Como solo se aceptan 20 pares, significa que a lo sumo habra 20 listasOrigen
    //es decir que a lo sumo se evaluaran 20 listas por composicion
    //estas listas son copias de su composicion previa(copia de las originaes en el primer caso)
    Lista listas[20];
    int numListas;
    //nombre de las funciones que se usaron para obtener las listas
    char** funcNombres;
    int numFunc;
    int profundidad ; //capacidad de la lista de nombres de funciones
};

typedef struct _Composicion* Composicion;



typedef struct _Pardelistas{
    //lista de la cual se parte para evaluar
    Lista listaOrigen;
    //lista objetivo a la cual se quiere llegar por medio de una composición
    Lista listaDestino;
}ParDeListas;



//
struct _Pares{
    //se aceptaran 20 pares
    ParDeListas par[20];

    int numPar;
};

//array de pares de listas
typedef struct _Pares* ParesDeListas;

/**
 * Dado un array de tokens crea pares de listas
 */
ParesDeListas pares_crear(char* tokens[], int numTokens, TablaHash tablaListas);

/**
 * A partir de pares de listas, crea una composicion inicial, en la cual no se aplicaron funciones
 * es decir, solo copia las listas de origen
 */
Composicion composicion_crear(ParesDeListas pares, int profundidad);

/**
 * Crea una copia de una composición
 */
Composicion composicion_copiar(Composicion comp);

/**
 * Composicion destruir 
 */

void composicion_destruir(Composicion comp);

/**
 * Aplica una instruccion a las listas de la estructura Composicion y agrega el nombre de la instrucción simple
 * (nombre de la función) al array de nombres
 */
Composicion nueva_composicion(Instruccion inst, Composicion comp, TablaHash tablaFunciones);

/**
 * Compara las listas de la composición con las listas de origen
 * retorna 1 si las listas de la composición son todas iguales a las de origen
 * caso contrario retorna 0;
 */
int composicion_adecuada(Composicion comp, ParesDeListas paresListas);

Composicion search_aux(NombresFunciones nombres, ParesDeListas paresDelistas,Cola cola,TablaHash tablaFunciones, int profundidadMax);

void search(char* tokens[],int numTokens,NombresFunciones nombres, TablaHash tablaFunciones, TablaHash tablaListas, int profundadMax);

#endif