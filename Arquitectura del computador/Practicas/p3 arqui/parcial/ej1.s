.data
str1: .asciz "Estoy en foo!\n"
str2: .asciz "La suma es %d \n"

.text

foo:
    pushq   %rbp
    leaq    str1, %rdi
    xorl    %eax, %eax
    call printf
    popq    %rbp
    ret
suma:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $32, %rsp
    movl    %edi, -4(%rbp)
    movl    %esi, -8(%rbp)
    movl    %edx, -12(%rbp)
    movl    %ecx, -16(%rbp)
    movl    %r8d, -20(%rbp)
    movl    %r9d, -24(%rbp)
    call foo
    movq    %rbp, %rsp
    popq    %rbp
    ret

.global main
main:
pushq %rbp
movq  %rsp, %rbp
    pushq   $8
    pushq   $7
    movl    $6, %r9d
    movl    $5, %r8d
    movl    $4, %ecx
    movl    $3, %edx
    movl    $2, %esi
    movl    $1, %edi
    call suma
    movl    %eax, %esi
    leaq    str2, %rdi
    xorl    %eax, %eax
    call printf
    movl $0, %eax
    movq %rbp, %rsp
    popq %rbp
    ret
