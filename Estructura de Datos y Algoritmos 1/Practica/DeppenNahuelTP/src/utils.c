#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "../cabeceras/utils.h"


void* copiar_puntero_entero(void* i) {
  int* p = malloc(sizeof(int));
  *p = *(int*)i;
  return p;
}
int comparar_puntero_entero(void* i1, void* i2) {
  return (*(int*)i1 - *(int*)i2);
}
void destruir_puntero_entero(void* i) { free(i); }

void imprimir_puntero_entero(void* i) {
  printf("%d", *(int*)i);
} 

int comparar_cadena(void *dato1, void *dato2) {
  return strcmp(dato1, dato2);
}

void *copiar_cadena(void *dato) {
  char *str = malloc(sizeof(char) * (strlen(dato) + 1));
  assert(str != NULL);
  strcpy(str, dato);
  return str;
}
void destruir_cadena(void *dato) { free(dato); }

void imprimir_cadena(void *dato, __attribute__((unused)) void *extra) {
  /* __attribute__((unused)) le dice al compilador que esta variable puede no
   * ser usada, de esta forma las banderas no tiran warnings.*/
  printf("\"%s\" ", (char *)dato);
}


int es_entero(char* s) {
    if (s == NULL || *s == '\0') return 0;
    int esDigito= 1;
    for (int i = 0; s[i] && esDigito; i++) {
        if (!isdigit(s[i]))
         esDigito= 0;
    }
    return esDigito;
}

/**
 * Funcion de hash para strings propuesta por Kernighan & Ritchie en "The C
 * Programming Language (Second Ed.)".
 */
unsigned KRHash(char *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; ++s) {
    hashval = *s + 31 * hashval;
  }
  return hashval;
}
unsigned KRHash2(char *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; ++s) {
    hashval = *s+ (hashval * 65536) + (hashval * 64) - hashval;
  }
  return hashval;
}
