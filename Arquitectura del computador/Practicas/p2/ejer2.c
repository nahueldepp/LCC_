#include <stdio.h>

/**
 * intercambia los 16 primeros bist con los 16ultimos
 */
unsigned int intercambiar(unsigned int n){

    return ((n<<16)&0xffff0000)|((n>>16)&0x0000ffff);
}
int main(void){

    float a=6.225;
    float* p= &a;
    int b= *(int*)p;
    unsigned int A=0xc4b76037;
    unsigned int B=0x3b489fc1;
    unsigned int C= A+B;
    unsigned x= 15;
    x^=x;
    printf("x=%d\n",x);
    printf("A=%u, B=%u, C= %u\n",A,B,C);
    printf("%#x\n",b);
    printf("Signo:%#x\n",(b>>31)&1);
    printf("Exponente:%#x\n",(b>>23)&0xff);
    printf("Matisa: %#x\n",b&0x7fffff);

    unsigned n=2565036;
    printf("n=%#x, intercambio= %#x\n",n,intercambiar(n));
    return 0;
}