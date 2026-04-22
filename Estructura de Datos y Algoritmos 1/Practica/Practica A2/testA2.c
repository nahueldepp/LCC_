#include "A2.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_arr(int* arr, int largo) {
    for (int i = 0; i < largo; i++) {
        printf("%d ",*(arr + i));
    }
    printf("\n");
}

int main(){

    srand(time(NULL));
    const int t= 16;
    int arr[t];
    for(int i= 0; i < t; i++){
        arr[i]= rand() % t;
    }
    print_arr(arr, 16);
    int tam= sizeof(arr)/sizeof(arr[0])-1;
    printf("q_sort \n");
    merge_sort_int (arr, t-1);
    print_arr(arr, t);

    return 0;
}