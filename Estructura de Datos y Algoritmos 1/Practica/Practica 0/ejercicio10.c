#include <stdio.h>
#include <stdlib.h>

/* char* copiar_cadena(char* cad, int longitud){
    char* a=malloc(sizeof(char) * longitud);
    a = cad;
    return a;
    //en este codigo hay un problema de dangling reference, ya que:
    (hablando en main)
    //aqui en b se copia la direccion al valor apuntado, es decir q b es una dangling reference
    //al hacerlo de esta manera perdemos la referencia al bloque de memoria usado en la funcion copiar_cadena y ya no lo podremos liberar
}  */


//copiar_cadena: char* char* ->
//dado dos punteros a char (cadenas de caracteres), copia la cadena a en b
void copiar_cadena(char* a, char* b, int longitud ){

    for(int i = 0; i < longitud; i++){
        *(b+i)=*(a+i);

    }

}

void nullify(int* a){

    printf("nully %d %p\n",a[0],a);
    a=NULL;
    //printf("nully %d %p\n",a[0],a);

}

int main(){
    char a[10] = "hola";     
    int longitud= sizeof(a)/sizeof(*a);
    char* b= malloc(sizeof(char)*longitud);
    copiar_cadena(a, b, longitud);
    printf("%s %s\n", a, b);
    b[0] = 's';
    printf("%s %s\n",a ,b ); 
    free(b);
    //11a
    int k[10];
    k[0]=123;
    printf("%d %p\n",k[0],k); //123
    nullify(k); //solo se modifica el valor que guarda la direccion que almacena k en la funcio, no se modifica el valor de k
    printf("%d %p\n",k[0],k); //123

    //b
    char* ptr = "hola mundo";
    ptr[0]='s';//no son modificables las letras, ya que ptr es solo un puntero a la cadena de caracteres inmutable "hola mundo"
    //printf("%s\n",ptr); segmentation fault


     
    // Una solucion seria: 


    return 0;
}