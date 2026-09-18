#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

/*
Se debe pedir el usuario que exprese el largo del mensaje y el mensaje
Las letras cuestan,cada una 10 pesos
Los digitos tienen un valor de 20 cada uno
Los caracteres especiales cuestan 30 y los espacios en blamco no tienen valor
*/


//-----------Prototipos-----------------
int precio_del_mensaje(char* mensaje);
//--------------------------------------

int main(){

    printf("Escriba la longitud del mensaje y el mensaje:\n");
    int largo_mensaje;
    scanf("%d",&largo_mensaje);

    char* mensaje;
    mensaje=(char*)malloc(sizeof(char)*(largo_mensaje+1));
    fgets(mensaje,largo_mensaje,stdin);


}

int precio_del_mensaje(char* mensaje){

    for(int pos_letra;mensaje[pos_letra]!='\0';pos_letra++){

    }
}