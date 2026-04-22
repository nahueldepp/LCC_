#ifndef _ARREGLO_ENTEROS_
#define _ARREGLO_ENTEROS_
typedef struct {
    int* direccion;
    int capacidad;
    } ArregloEnteros;
    

ArregloEnteros* arreglo_enteros_crear(int capacidad);

void arreglo_enteros_destruir(ArregloEnteros* arreglo);

int arreglo_enteros_leer(ArregloEnteros* arreglo, int pos);

void arreglo_enteros_escribir(ArregloEnteros* arreglo, int pos, int dato);

int arreglo_enteros_capacidad(ArregloEnteros* arreglo);

void arreglo_enteros_imprimir(ArregloEnteros* arreglo);

/** 
 *  ajusta el tamanño del arreglo. SI la nueva capacidad es menor, el contenido debe ser truncado
 */
void arreglo_enteros_ajustar(ArregloEnteros* arrPtr, int capacidad);

void arreglo_enteros_insertar(ArregloEnteros* arreglo, int pos, int dato);

void arreglo_enteros_eliminar(ArregloEnteros* arreglo, int pos);

#endif