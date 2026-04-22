#include <stdio.h>



//---prototipos---//
void ejercicio_9_d(void);
void aumentar_puteros(int* x, int* y,int z);
void ejercicio_9_e(void);
//void ejercicio_9_f(void);
//int *direccion_local(int a);
void ejercicio_9_g(void);
//---------------//

int main(){

    ejercicio_9_d();
    ejercicio_9_e();
    //ejercicio_9_f(); genera error ya que supuestamente direccion_local devuelve una direccion a un entero, pero despues de haber usado la variable local
    //a en la funcion, lo que guarda esta se elimina y no podemos tomarla como puntero a entero
    ejercicio_9_g();

    return 0;

}


void ejercicio_9_d(void){

    int *punt, i;
    int x[5] = {1,2,3,4,5};
    punt= &x[0] + 3; //guardo la direccion del 4 elemento del array, (4 hasta este punto)
    *(punt-2) = 9; //me muevo dos direcciones hacia atras, es decir apunto a la direccion del segundo elemento del array
                    //y lo desreferencio, guardando en la direccion apuntado un 9( 2->9)
    punt--; //se mueve la direccion apuntada a una anterior, ahora se guarda la direccion del tercer elemento(3 hasta ahora)
    *(punt) = 7; //se desreferencia la posición apuntada, y se guarda en esa direccion el valor 7(3->7)
    punt[1] = 11;//se mueve un lugar a partir de la posicion guardada,es decir se mueve a la pos del 4 elemento
    // y se guarda en esa direccion el valor 11 (4->11)
    punt =x; //se vuelve a guardar en el puntero la primera posicion del array
    //x={1,9,7,11,5}
    for(i = 0; i < 5; i++){
        printf("%d\n",x[i]);
    }
}

void aumentar_punteros(int* x, int* y,int z){
    *x = *x + 2;
    *y= *y + 5;
    z= z + 4;
}

void ejercicio_9_e(void){
    int x ,y ,z;
    x=3;
    y = 10;
    z = 15;
    aumentar_punteros(&x, &y, z);
    printf("x = %d, y= %d, z= %d\n",x,y,z);

}

/* int *direccion_local(int a){
    return &a;

} */

/* void ejercicio_9_f(void){
    int *ptr = NULL;
    int x = 2;
    ptr  = direccion_local(x);
    printf("%d\n ",*ptr);
} */

void ejercicio_9_g(void){
    char textoA[30] = "Agarrate Catalina";
    char textoB[30]= "El Cuarteto de Nos";
    char *p= textoA;
    char *q= textoB;
    printf("textoA: %s\n textoB: %s\n",textoA, textoB);
    while(*p++=*q++)
    ;
    printf("while(*p++=*q++)");
    printf("textoA: %s\n textoB: %s\n",textoA, textoB);
}