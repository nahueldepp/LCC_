#include "utils.h"
#include <math.h>


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

/* static unsigned es_primo(int n){
  if( n==1 || n == 2)
    return 1;
  int esPrimo= 1;
  for(int i=3; i< sqrt(n) && esPrimo; i++){
    if(n%i == 0){
      esPrimo=0;
    }
  }
  return esPrimo;
}

// Función que devuelve el menor primo mayor a 2*x
static int menor_primo_mayor_doble(int x) {
    int n = 2 * x + 1;
    while (!es_primo(n)) {
        n++;
    }
    return n;
}
 */
