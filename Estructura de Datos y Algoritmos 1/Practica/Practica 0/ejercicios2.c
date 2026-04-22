#include<stdio.h>
#include<math.h>


//--Estructuras/Tipo de datos--//

typedef void (* VisitanteFunc )(int *) ;

//----------------------------//

//---Prototipos---//
int fun0(int );
int apply(int(*fun)(int) , int x);
void apply_in(int(*fun)(int),int* a);
void recorre(VisitanteFunc fun,int arr[],int size);
void fun1(int *x);

//----------------//



int main(){
    //8a
    int (*pfun)(int)=&fun0;
    int val;
    val=apply(pfun,2);
    printf("valor=%d\n",val);
    //b
    int a=2;
    int *pa=&a;

    apply_in(pfun,pa);
    printf("El valor despues de aplicar apply_in es: %d\n",a);

    //c

    int arrInt[]={0,1,2,3};
    int sizeArr=sizeof(arrInt)/sizeof(arrInt[0]);

    VisitanteFunc ptrf1=&fun1;
    recorre( ptrf1,arrInt,sizeArr);

    



}

//ejercicip 8

//a)
//fun0:int->int
//toma un entero y lo evalua en el polinomio x^2+1
int fun0(int x){

    return pow(x,2)+1;
}

//aplly: int (*)(int)->int
//toma un puntero a funcion y un entero y aplica la funcion al valor
int apply(int(*fun)(int) , int x){
    fun(x);
}

//b)

// apply_in():int(*)(int), int* ->void
//Dado un puntero-a-función y un puntero a int, 
//reemplaza el entero apuntado por el valor de ejecutar la funcion apuntada sobre el valor apuntado
void apply_in(int(*fun)(int),int* a){
    
    *a=fun(*a);
}


//c)

void fun1(int *x){
    *x=pow(*x,2)+*x;
}
//recorre(): VisitanteFunc, int[], int -> void
//toma un puntero-a-función, un array de enteros y su tamaño, y aplica la funcion apuntada a cada valor de array (lo modifica)
void recorre(VisitanteFunc fun,int arr[],int size){

    for(int i=0;i<size;i++){
        fun(i+arr);
        printf("arr[i]=%d\n",arr[i]);
    }
}

