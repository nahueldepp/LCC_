.data
b:  .long 1
a:  .long 0x7fffffff
str_main:   .asciz "0x%x 0x%x\n"
str_foo1:   .asciz "Ejecutando foo1...\n"
str_foo2:   .asciz "Ejecutando foo2...\n"
str_gen:    .asciz "0x%x\n"

.text
foo1:
    # prologo
    pushq %rbp
    movq %rsp, %rbp
    movq $str_foo1, %rdi
    call printf
    movq $0, %rbx
    movl b, %ebx
    sall $31, %ebx
    movl a, %eax
    addl %ebx, %eax
    movl %eax, a
    movq $str_gen, %rdi
    movl %eax, %esi
    call printf
    movl a, %eax
    # epilogo
    movq %rbp, %rsp
    popq %rbp
    ret

foo2:
    # prologo
    pushq %rbp
    movq %rsp, %rbp

    movq $str_foo2, %rdi
    call printf
    movl a, %eax
    movl b, %ebx
    addl %ebx, %eax
    movl %eax, a
    movq $0, %rsi
    movl %eax, %esi
    movq $str_gen, %rdi
    call printf
    movl a, %eax
    # epilogo
    movq %rbp, %rsp
    popq %rbp
    ret
.global main
main:
    # prologo
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp # guardo dos lugares en la pila
    movl $0, %eax
    call foo2
    movl %eax, -8(%rbp) # ret foo2
    movl $0, %eax
    call foo1
    movl %eax, -16(%rbp) # ret foo1
    movq $str_main, %rdi
    movl -16(%rbp), %esi
    movl -8(%rbp), %edx
    call printf
    # epilogo
    movq %rbp, %rsp
    popq %rbp
    ret


