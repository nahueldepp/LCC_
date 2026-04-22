#include <stdio.h>


int is_one(long n, int b){
    long p=0x1;
    return (n>>b)&1;
}
void ejer_15(void){
    long n= 0b0011110111;
    int b= 3;
    printf("%ld en formato hexadecimal: %lx",n,n);
    printf("Para %ld el %d-esimo bit es %d\n",n,b,is_one(n,b));
    
}

/**
 * Toma un entero de 64 bits y lo imprime en binario
 */
void printbin(long n){

    for(int i=63; i>=0; i--){
        printf("%ld",(n>>i)&1);
    }
    puts("");
}
void ejer_16(void){
    long n= -16;
    printf("El numero %ld en binario es: ",n);
    printbin(n);
}

void cambio_XOR(long* a, long* b,long* c){
    *a=*a^*b;
    *b= *a^*b;//b=a
    *a=*a^*b;//a= a^b^a=b

    *c= *c^*a;
    *a=*c^*a;
    *c=*c^*a;//c=b

}
void ejer_17(void){
    long a,b,c;
    a=15;
    b=23;
    c=90;
    printf("Antes del cambio: %ld,%ld,%ld\n",a,b,c);
    cambio_XOR(&a,&b,&c);
    printf("Dsp del cambio: %ld,%ld,%ld\n",a,b,c);
}
int main(void){

    ejer_15();
    ejer_16();
    ejer_17();
    return 0;
}