#define YES 1
#define NO 0
#line  3000 "Ejercicio1.c"

//d
#if defined(TRUE)
#undef TRUE
#define TRUE 1
#endif
//e
/* #ifdef TRUE
#undef TRUE
#define TRUE 1
#endif */
//f

#if (TRUE!=0)
#define FALSE 0
#else
#define FALSE 1
#endif

#define SQUARE_VOLUMEN(lado) (lado*lado*lado)

#include <stdio.h>

//Ejercicio 2
#define PI 3.14159
#define VOLUMEN_ESFERA(r) ((4/3)*PI*(r*r*r))
int lado=2;

//Ejercicio 4

#define MINIMUN2(a,b) ((a<b)?(a):(b))

//Ejercicio 5

#define MINIMUN3(a,b,c) (MINIMUN2(a,MINIMUN2(b,c)))


//7
#define PRINTARRAY(arr,nde) \
for(int i=0;i<=nde;i++)\
{printf("%d\n",arr[i]);\
}




//--------//
int volumen_esferas(void);
int minimo_2(void);
int minimo_3(void);
//--------//
int main(){
    printf("El volumen del cuadrado es %d \n",SQUARE_VOLUMEN(2));
    printf("%d",FALSE);
    printf("%d\n",TRUE);
    printf("Ejercicio 2 \n");
    volumen_esferas();

    printf("Ejercicio 3 \n");
    //minimo_2();
    //minimo_3();

    int arr[]={0,1,2,3,4,5,6};
    int size_array=sizeof(arr)/sizeof(arr[0]);

    PRINTARRAY(arr,size_array );
}

//volumen_esferas:void->void
//El programa imprime en pantalla el volumen de esferas de radios del 1 al 10

int volumen_esferas(void){

    for(int i=1;i<=10;i++){
        printf("La esfera de radio %d, tiene un volumen de %0.2f\n",i,VOLUMEN_ESFERA(i));
    }
    return 0;
}

int minimo_2(void){

    printf("Escriba dos valores númericos: \n");
    float a,b;
    scanf("%f %f",&a,&b);

    printf("El valor mas pequeños es: %0.2f \n",MINIMUN2(a,b));
}

    
    

int minimo_3(void){
    printf("Escriba tres valores númericos: \n");
    float a,b,c;
    scanf("%f %f %f",&a,&b,&c);

    printf("El valor mas pequeños es: %0.2f \n",MINIMUN3(a,b,c));


}