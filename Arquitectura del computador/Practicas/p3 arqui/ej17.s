.data
format: .asciz " %ld\n"
r_rsp:  .asciz "valor del registro rsp 0x%lx\n"
d_formato:  .asciz "Direccion de la cadena formato: 0x%016x\n"
i: .quad 0xDEADBEEF
.text
.global main
main:
imprimir_formato:
    movq $format, %rdi # El primer argumento es el formato
    movq $1234, %rsi # El valor a imprimir
    xorq %rax, %rax # Cantidad de valores de punto flotante
    call printf

imprimir_valor_rsp:
    movq $r_rsp, %rdi
    movq %rsp, %rsi
    xorq %rax, %rax
    call printf
imprimir_direccion_formato:
    movq $d_formato, %rdi
    movq $format, %rsi
    xorq %rax, %rax
    call printf

    ret
