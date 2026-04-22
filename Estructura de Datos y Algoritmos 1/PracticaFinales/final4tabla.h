#ifndef __TABLA_H__
#define __ TABLA_H__


#define TAM_TABLA 2;
#define ELIMINADO 0
typedef void *(*FuncionCopiadora)(void *dato);
/** Retorna una copia fisica del dato */
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
/** Retorna un entero negativo si dato1 < dato2, 0 si son iguales y un entero
 * positivo si dato1 > dato2  */
typedef void (*FuncionDestructora)(void *dato);
/** Libera la memoria alocada para el dato */
typedef unsigned (*FuncionHash)(void *dato);
/** Retorna un entero sin signo para el dato */


/**
 * Aplicacion de tabla hash con direccionamiento cerrado, usando listas simplemente enlazadas
 */
typedef struct casillaHash{
    void *dato;
    struct casillaHash* sig; //puntero al siguiente elemento
    unsigned largoLista;
} _CasillaHash;

typedef _CasillaHash* CasillaHash;

struct _TablaHash {
    CasillaHash *elems;
    unsigned numElems;
    unsigned capacidad;
    FuncionCopiadora copia;
    FuncionComparadora comp;
    FuncionDestructora destr;
    FuncionHash hash1;
    //FuncionHash hash2;
 };
typedef struct _TablaHash *TablaHash;




TablaHash tabla_crear(FuncionCopiadora copia, FuncionComparadora comp, FuncionDestructora destr, FuncionHash hash1);

void tabla_insertar(TablaHash tabla, void* dato);

void* tabla_buscar(TablaHash tabla, void* dato);

void tabla_eliminar(TablaHash tabla, void* dato);

void tabla_rehash(TablaHash tabla);

void tablahash_destruir(TablaHash tabla);
#endif 