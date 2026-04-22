#include <stdio.h>

void sum(float* a, float* b, int len);
int main(void){
    float a[]= {1.0,2.0,3.5};
    float b[]= {1.0,2.0,3.5};
    int len= 3;
    sum(a,b,len);
    printf("a[0]= %f, a[1]=%f, a[2]=%f\n",a[0],a[1],a[2]);
    return 0;
}