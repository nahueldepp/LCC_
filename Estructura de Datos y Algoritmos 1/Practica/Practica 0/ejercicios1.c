#include <stdio.h>
#include <stdlib.h>

//----//
void set_first(int*);
void set_in(int*);
void swap(int*, int* );
//----//

//ejercicio 1
int main(void){
    int a;
    a=56;
    int *p=&a;
    char c;
    char *carArr[5];
    int intArr[5];
    intArr[0]=35;
    printf("la dirección de a es: %p\n",&a);
    printf("la dirección de a es: %p\n",&c);

    for(int i=0;i<5;i++){
        printf("La direccion del elemento %d de carArr es: %p\n",i,&carArr[i]);

    }

    //ejer2
    printf("primer elemento antes de set_first: %d\n",intArr[0]);
    set_first(intArr);
    printf("primer elemento despues de set_first: %d\n",intArr[0]);
    
    //ejer3

    set_in(p);
    printf("El valor que guarda p es: %d\n",*p);

    //ejer 4

    int b;
    int *pb=&b;

    swap(p,pb);

    printf("a=%d y b=%d\n",a,b);

    float *prueba=(float*)malloc(sizeof(int));
    *prueba=377777.54454;
    printf("prueba=%f\n",*prueba);
    free(prueba);
    

    
}

//ejercicio 2;

// set_first: int []->void
//modifica el primer elemento de un array de int, lo pone en cero
void set_first(int arr[]){

    *arr=0;
}


//ejercicio 3

//set_in:int*->void
//toma el puntero a un entero, y reemplaza el entero apuntado por 1 si el enteto apuntado era diferente a 0, y 0 en caso contrario

void set_in(int* iptr){

    if(*iptr!=0){
        *iptr=1;
    }
    else{
        *iptr=0;
    }
}

//ejercicio4;

//swap: int* int* -> void
//dados dos puneteros a variables, intercambia el contenido de las variables apuntadas

void swap(int* a, int* b){

    int temp;
    temp=*a,
    *a=*b;
    *b=temp;

}