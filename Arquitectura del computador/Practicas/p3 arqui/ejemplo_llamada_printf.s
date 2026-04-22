.data
str: .asciz "%d\n"
a: .long 45

.text
.global main
main:
    pushq %rbp          # Alineamos la pila a 16 bytes
    leaq str, %rdi      # Le pasamos la direc. de la cadena de formato
    movl a, %esi        # Le pasamos el segundo argumento
    movb $0, %al        # Cantidad de argumentos de punto flotante
    call printf         # Llamamos a la función printf
    popq %rbp           # Desapilamos para restaurar el valor de rsp
    xorl %eax, %eax     # Retornamos cero
    ret