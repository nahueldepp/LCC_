#include <stdio.h>
#include <stdlib.h>


//bubble_sort: float[], int ->void
//toma un array de float y su longitud y ordena el array de menor a mayor 
void bubble_sort(float arr[],int longitud){

    for(int iter = 0; iter < longitud-1; iter++){
        for(int i= 0; i < longitud-iter-1; i++){
            if(arr[i] > arr[i+1]){
                float temp=arr[i];
                arr[i]=arr[i+1];
                arr[i+1]=temp;
            }
        }
    }
}

float mediana(float *arreglo, int longitud){
    
    bubble_sort(arreglo, longitud);
    float mediana;
    if(longitud%2 == 0){
        mediana= (arreglo[(longitud / 2) -1] + arreglo[(longitud / 2)]) / 2;
    }
    else{
        mediana= arreglo[((longitud + 1) / 2) -1];
    }

    return mediana;

}

void ejercicio_1(void){
    float arreglo[5]={3.5,3.1,2.9,-1.0,2.2};
    float arreglo2[4]={3.1,2.2,-1.0,2.9};
    float media1, media2;
    media1= mediana(arreglo,5);
    media2= mediana(arreglo2,4);
    printf("%0.2f %0.2f\n",media1,media2);
    
}

//2 implemente las siguientes funciones para cadenas de caracteres:

//string_len():char*->int
//Dada una cadena de caracteres devuelve el largo de la cadeba sin contar el "'\0'"
int string_len(char* str){

    int i = 0;
    for(; str[i]!= '\0';i++){};

    return i;

}

//b
//string_reverse(): char* ->void
//Dada una cadena la invierte
void string_reverse(char* str){
    int largoCadena = string_len(str);
    int tope;
    
    tope= largoCadena / 2; 
    for(int i= 0; i< tope;i++){
        char temp;
        temp=str[i];
        str[i]=str[largoCadena-1-i];
        str[largoCadena-1-i]=temp;
        
    }
}

//c)
 
//string_concat():char*, char*, int -> int
//concatena no mas de max caracteres de la cadena str2 al final de str1. Retorna el numero de caracteres copiados.
int string_concat(char* str1, char* str2, int max ){
    int largo1= string_len(str1);

    for(int i = 0; i< max; i++){
        str1[largo1 + i]= str2[i];
    }
    str1[max + largo1]= '\0';

    return max;
}

int min(int a, int b){

    if(a > b){
        return b;
    }
    else{
        return a;
    }
}

//d)
int string_compare(char* str1, char* str2){

    int largoStr1= string_len(str1);
    int largoStr2= string_len(str2);
    int cadenaMasCorta= min(largoStr1,largoStr2);
    int i= 0;
    while(str1[i] == str2[i] && i < cadenaMasCorta){
        i++;
    }

    if( i== cadenaMasCorta){
        if(largoStr1 == cadenaMasCorta){
            return -1;
        }
        else if(largoStr2 == cadenaMasCorta){
            return 1;
        }

    }
    else if(str1[i] < str2[i]){
        return -1;
    }
    else{
        return 1;
    }
}


void ejercicio_2(void){
    printf("a)\n");
    char cadena1[20]="musicaaa";
    printf("largo de la cadena: %d\n", string_len(cadena1));

    printf("b)\n");
    char cadena2[10]="ojana";
    string_reverse(cadena1);
    string_reverse(cadena2);

    printf("%s %s\n", cadena1, cadena2 );
    string_reverse(cadena1);

    printf("c)\n");
    string_concat(cadena1,cadena2,4);
    printf("%s\n", cadena1);

    printf("d)\n");

    char cadena3[10]= "abd";
    char cadena4[10]= "abcd";
    printf("%d\n",string_compare(cadena3,cadena4));
}

//3)-------------------------------
typedef struct{
    int* direccion;
    int capacida;
}ArregloEnteros;

//a)
//crear_arreglo_enteros: int ->ArregloEnteros
ArregloEnteros* crear_arreglo_enteros(int capacidad){

    ArregloEnteros* arr;
    arr= (ArregloEnteros*)malloc(sizeof(ArregloEnteros));
    if(arr==NULL){
        return NULL;
    }
    arr->direccion=malloc(sizeof(int)*capacidad);

    if (arr->direccion == NULL)
    {   
        
        free(arr);

    }
    
    arr->capacida= capacidad;
    return arr;
}

//b)
//destruir_arreglo_enteros; ArregloEnteros* -> void
void destruir_arreglo_enteros(ArregloEnteros* arrPtr){
    free(arrPtr->direccion);
    free(arrPtr);
}

//c)

int leer_arreglo_enteros(ArregloEnteros* arrPtr, int pos){

    return *(arrPtr->direccion +  pos);
}

//d)
void escribir_arreglo_enteros(ArregloEnteros* arrPtr, int pos, int dato){

    *(arrPtr->direccion + pos)= dato;
}

//e)
int capacidad_arreglo_enteros(ArregloEnteros* arrPtr){

    return arrPtr->capacida;
}

//f)

void imprimir_arreglo_enteros(ArregloEnteros* arrPtr){
    for(int i= 0; i < arrPtr->capacida ; i++){
        printf("%d, ", leer_arreglo_enteros(arrPtr, i));
    }
    printf("\n");
}


//4)

// ajustar_arreglo_enteros(): ArregloEnteros*, int  -> void
//ajusta el tamanño del arreglo. SI la nueva capacidad es menor, el contenido debe ser truncado
void ajustar_arreglo_enteros(ArregloEnteros* arrPtr, int capacidad){

    int tamanoArreglo= capacidad_arreglo_enteros(arrPtr);

    ArregloEnteros* nuevoArreglo= crear_arreglo_enteros(capacidad);

    for(int i = 0; i < capacidad; i++){
        escribir_arreglo_enteros(nuevoArreglo,i,leer_arreglo_enteros(arrPtr,i));
    }

    free(arrPtr->direccion);
    arrPtr->direccion= nuevoArreglo->direccion;
    arrPtr->capacida= capacidad;
    free(nuevoArreglo);
    

}
//insertar_arreglos_enteros(): ArregloEnteros*, int, int ->void
//insreta el dato en la posicion dada, moviendo odos los elementos desdee esa posicion un lugar a la derecha
//(se incrementa el tamaño del arreglo)
void insertar_arreglos_enteros(ArregloEnteros* arrPtr,int pos, int dato){

    int nuevaCapacidad= capacidad_arreglo_enteros(arrPtr)+1;
    ajustar_arreglo_enteros(arrPtr, nuevaCapacidad );
    for(int i = nuevaCapacidad-1; pos < i; i--){

        escribir_arreglo_enteros(arrPtr, i, leer_arreglo_enteros(arrPtr,i-1));
    }
    escribir_arreglo_enteros(arrPtr, pos, dato);
}

//c

//arreglo_enteros_eliminar(): arrPtr, pos -> ArregloEnteros*
//elimina el dato en la posicion dada, moviendo todos los elementos posterioes un lugar a la izquerda( se reduce el tamaño del arreglo)
void arreglo_enteros_eliminar(ArregloEnteros* arrPtr, int pos){

    int nuevaCapacidad=capacidad_arreglo_enteros(arrPtr)-1;
    for(int i=pos; i < nuevaCapacidad; i++){
        escribir_arreglo_enteros(arrPtr,i,leer_arreglo_enteros(arrPtr,i+1));
    }
    ajustar_arreglo_enteros(arrPtr,nuevaCapacidad);
}

void ejercicio_3(void){
    ArregloEnteros* arr= crear_arreglo_enteros(3);
    escribir_arreglo_enteros(arr,0,0);
    escribir_arreglo_enteros(arr,1,1);
    escribir_arreglo_enteros(arr,2,2);

    imprimir_arreglo_enteros(arr);
    ajustar_arreglo_enteros(arr,4);
    imprimir_arreglo_enteros(arr);
    insertar_arreglos_enteros(arr,3,11);
    imprimir_arreglo_enteros(arr);
    arreglo_enteros_eliminar(arr,0);
    imprimir_arreglo_enteros(arr);
    destruir_arreglo_enteros(arr);
}


int main(){
    //ejercicio_1();
    //ejercicio_2();
    ejercicio_3();

     
    
}