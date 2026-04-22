.data
fmt: .string " %d"
entero: .long -100
funcs:  .quad f1
        .quad f2
        .quad f3
.text
f1: movl $0, %esi; movq $fmt, %rdi; call printf; jmp fin
f2: movl $1, %esi; movq $fmt, %rdi; call printf; jmp fin
f3: movl $2, %esi; movq $fmt, %rdi; call printf; jmp fin
.global main
main:
    pushq %rbp
    movq %rsp, %rbp
    # Leemos el entero.
    movq $entero, %rsi # scanf usa %rsi para saber donde almacenar el entero ingresado
    movq $fmt, %rdi
    xorq %rax, %rax
    call scanf
    xorq %rax, %rax
    
    movl entero, %eax # indice de funcs (0,1,2)
    jmp *funcs(,%rax,8)

fin:
    movq %rbp, %rsp
    popq %rbp
    ret