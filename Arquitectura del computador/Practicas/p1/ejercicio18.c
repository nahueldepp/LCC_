#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char* argv[]){

    char* cadena= argv[2];
    unsigned lencadena=strlen(cadena); 
    char* codificado= malloc(sizeof(char)* (lencadena+1));
    int codigo= atoi(argv[1]);
    for(unsigned i= 0; i<lencadena; i++){
        codificado[i]=(char)(cadena[i]^codigo);
    }
    codificado[lencadena]='\0';

    printf("La cadena %s con el codigo %d se codifica en: %s\n",cadena,codigo, codificado);
    char* descodificado= malloc(sizeof(char)* (lencadena+1));
    for(unsigned i= 0; i<lencadena; i++){
        descodificado[i]=(char)(codificado[i]^codigo);
    }
    printf("Si lo descodificamos: %s\n",descodificado);
    return 0;
}