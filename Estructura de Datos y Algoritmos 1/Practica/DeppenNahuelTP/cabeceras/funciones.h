#ifndef __FUNCIONES_H__
#define __FUNCIONES_H__
#include "listas.h"
#include "colas.h"
#include "tablahash.h"

#define CAPACIDAD_INICIAL_NOMBRES 200
#define MAX_EVALUACIONES 300
/**
 * tipo de funciones
 */
typedef enum {
    FUNC_OI,FUNC_OD,FUNC_SI,FUNC_SD,FUNC_DI,FUNC_DD,
    FUNC_USUARIO,
    FUNC_REPETICION
}TipoFuncion;

typedef void (*OperacionPrimitiva) (Lista);


typedef struct _funcionesPrimitivas{
    char* nombre;
    OperacionPrimitiva operacion;
}FuncionPrimitiva;

/**
 * Oi: agrega un cero a la izquierda de la lista:
 */
void func_Oi(Lista lista);

/**
 * Od: agrega un cero a la derecha de la lista:
 */
void func_Od(Lista lista);

/**
 * Si: suma uno al elemento a la izquierda de la lista
 */
void func_Si(Lista lista);
/**
 * Sd: suma un uno al elemento a la derecha de la lista
 */
void func_Sd(Lista lista);

/**
 * Di: borra el elemento de la izquierda de la lista
 * en caso de querer borrar la lista vacia, devuelve la lista vacia
 */
void func_Di(Lista lista);

/**
 * Dd: borra el elemento de la derecha de la lista
 */
void func_Dd(Lista lista);


// lista de instrucciones
typedef GLista Instrucciones;

struct _Instruccion{
    TipoFuncion funcionTipo;// en el caso que funcionTipo sea menor a 6, sabemos que es una primitiva
    union {
        // nombre de una funcion definida por el usuario
        char* nombre;
        //lista de instrucciones a repetir, donde cada dato es una instruccion
        Instrucciones listaRepeticion;
    };
    
};
typedef struct _Instruccion* Instruccion;



struct _Funcion{
    //nombre de la funcion
    char* nombre;
    //lista de instrucciones
    Instrucciones cuerpo;  
};
typedef struct _Funcion* Funcion;



/**
 * Dada una Lista y un TipoFuncion  < FUNC_USUAIRO
 * evalua la lista segun el TipoFuncion
 */
void  evaluar_primitiva(Lista lista, TipoFuncion);

/**
 * Dado el nombre de una función, determina si es una primitiva o no
 * en caso de que sea una primitiva devuelve TipoFuncion de la primitiva (<6)
 * caso contraria devuelve FUNC_USUARIO (6)
 */
int primitiva_tipo(char* token);


/**
 * Dado un token (nombre de una funcion Primitiva o definida por el usuario)crea una Instruccion,
 * en caso de ser primitiva, solo asigna TipoFuncion como su primitiva correspondiente,
 * en el caso de ser una funcion definida por el usuario, guarda el TipoFuncion y su nombre
 * retorna una Instruccion
 */
Instruccion instruccion_simple_crear(char* token);

/**
 * Dada una array de tokens, la posicion del token a evaluar y el número de tokens
 * crea una lista de Instruccion (Instrucciones)
 */
Instrucciones instrucciones_crear(char* tokens[], int* i, int numTokens);

/**
 * Aplica la instruccion dada sobre la lista
 */
void instruccion_evaluar(Instruccion inst,Lista lista,TablaHash tablaFunciones,int* numEvaluaciones);

/**
 * Dada una instruccion, retorna una copia fisica
 */ 
Instruccion instruccion_copiar(Instruccion inst);

/**
 * Destruye una instruccion
 */ 
void Instruccion_destruir(Instruccion inst);


/**
 * Immprime una funcion por "niveles" (Dependiendo la profundidad de las Instrucciones, las imprime mas a la derecha)
 */ 
void instruccion_imprimir(Instruccion inst, int nivel);

/**
 * Dado una array de tokens, y la cantidad de tokens crea una funcion que evalua listas
 * Esta función posee nombre y un cuerpo de instrucciones (lista de: nombres ó punteros a instrucciones)
 */
Funcion funcion_crear(char* tokens[],int numTokens);



/**
 * Destruye una funcion de listas
 */
void funcion_destuir(Funcion funcion);

/**
 * Dada una funcion de listas crea una copia fisica y la retorna
 */
Funcion funcion_copia(Funcion f);
/**
 * Imprime una funcion
 */
void funcion_imprimir(Funcion f);

/**
 * Dada una funcion y un nombre, determina si ese es el nombre de la funcion
 */
int funcion_comparar(Funcion f, Funcion g);

/**
 * Dada una función de listas, una lista y una tabla de funciones:
 * Crea una copia de la lista dada y la evalua
 * En caso exitoso retorna la copia de la lista evaluada
 * en otro caso retorna NULL
 */
Lista funcion_evaluar(Funcion f, Lista lista,TablaHash tablaFunciones );




/**
 * Hashear un contacto por su nombre. 
 */
unsigned funcion_hashear(Funcion funcion);

unsigned funcion_hashear2(Funcion funcion);



/**
 * Almacena nombres de funciones
 */
struct _nombres{
    int capacidad;
    char** arrNombres;
    int numNombres;
};
typedef struct _nombres* NombresFunciones;


/**
 * Crea una estructura NombresFunciones
 */
NombresFunciones nombre_funciones_crear(void);

/**
 * agrega nombre de funciones a un array NombresFunciones
 */
void nombres_funciones_agregar(NombresFunciones nombres, char* nuevoNombre);

/**
 * Dobla la capacidad de almacenamieto de nombres
 */
void nombres_funciones_ampliar_capacidad(NombresFunciones nombres);

/**
 * Destruye una estructura NombresFunciones
 */
void nombres_funciones_destruir(NombresFunciones nombres);


#endif