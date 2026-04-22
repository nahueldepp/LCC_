#include <stdio.h>
int main (){
char a =127;
printf (" %hhd %hhu\n",a,a);
a =++ a;
printf (" %hhd %hhu\n",a,a);
unsigned char b =128;
printf (" %hhd %hhu\n",b,b);
b =++ b;

printf (" %d %u\n",b,b);
char a2 =127;
printf (" %d %u\n",a2,a2);
a2 =++ a2;
printf (" %d %u\n",a2,a2);
unsigned char b2 =128;
printf (" %d %u\n",b2,b2);
b2 =++ b2;
printf (" %d %u\n",b2,b2);

printf("ejer 11 b)\n");

unsigned char A= 0xc4;
unsigned char B= 0x4e;
unsigned char C=A+B;

printf("A= %x,%d B= %x,%d unsigned C= %hhu,signed C= %hhd, %u\n",A,A,B,B,C,C,C);
return 0;
}