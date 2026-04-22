#ifndef __UTILS_H__
#define __UTILS_H__

void* copiar_puntero_entero(void* i);

int comparar_puntero_entero(void* i1, void* i2);

void destruir_puntero_entero(void* i);

void imprimir_puntero_entero(void* i);

void *copiar_cadena(void *dato);

void destruir_cadena(void *dato);

void imprimir_cadena(void *dato, __attribute__((unused)) void *extra) ;

int comparar_cadena(void *dato1, void *dato2);

/**
 * determina si un string es un entero
 */
int es_entero(char* s);
unsigned KRHash(char *s);

unsigned KRHash2(char *s) ;

#endif