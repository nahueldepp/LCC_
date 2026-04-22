#include <stdlib.h>
#include <stdio.h>

int funcion(float* arreglo, int cantElems);
void main(){
    float flotantes[]= {1.3,2.3,6.5,5.0};
    int cantFloats= 4;
    int paaridad= funcion(flotantes, cantFloats);
    printf("Paridad %d\n", paaridad);
}