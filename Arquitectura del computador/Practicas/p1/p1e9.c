#include <stdio.h>

int main(void) {
    // A = 200, B = 300, C = 500, D = 400
    int A = 0b00000000000000000000000011001000; // 200
    int B = 0b00000000000000000000000100101100; // 300
    int C = 0b00000000000000000000000111110100; // 500
    int D = 0b00000000000000000000000110010000; // 400

    int S_int = A * B * C * D; // posible overflow
    long int S_long = (long int)A * B * C * D; // cálculo correcto (64 bits)

    printf("Resultado con int: %d\n", S_int);
    printf("Resultado con long int: %ld\n", S_long);

    return 0;
}