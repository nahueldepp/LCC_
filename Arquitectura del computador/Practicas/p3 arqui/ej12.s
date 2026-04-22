.data
list: .long 50, 20, 30, 40, 10, 60, 70, 80, 90, 100
length: .byte 10
str_promedio:   .asciz "El valor promedio= %d\n"
str_minimo:     .asciz "Valor minimo= %d\n"
.text
.global main
main: 
    # prologo
    pushq %rbp
    movq %rsp, %rbp
    xor %rcx, %rcx
    movb length, %cl
    lea list, %rdi
    xor %rax, %rax
suma_lista:
    movl (%rdi), %edx
    addq %rdx, %rax
    addq $4, %rdi
    loop suma_lista
    
    # obtenemos el promedio
    movq $0, %rdx
    movb length, %bl
    div %bl # se divide el valor rn rax usando el valor de rbx (Division entera) el resultado se almacena en rax
imprime_promedio: 
    movq $str_promedio, %rdi # primer argumento de printf
    movq %rax, %rsi # segundo argumento de printf
    call printf

    # Buscamos el minimo
    xor %rax, %rax
    movb length, %cl
    lea list, %rax
    movl (%eax), %esi # muevo un long a rsi, donde se guardara el minimo

minimo: 
    addl $4, %eax
    cmpl (%eax), %esi
    js seguir  # si rsi<(%rdi) => (%rdi)-%rsi<0 => SF= 1 luego rsi es menor, sino SF=0, (%rdi)>=%rsi 
    movl (%eax), %esi
seguir:
    loop minimo 

imprimir_minimo: 
    movq $str_minimo, %rdi
    call printf 


    # epilogo
    movq %rbp, %rsp
    popq %rbp
    ret


