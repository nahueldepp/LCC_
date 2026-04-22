.data 
str1: .asciz "La suma es %f y el promedio es %f\n"

.text
.global funcion

funcion:
    pushq   %rbp
    movq    %rsp, %rbp
    subq $16, %rsp
    movq %rsi, -8(%rbp)
    xorq  %rcx,%rcx
    cvtsi2ss   %rcx, %xmm0
    cvtsi2ss   %rcx, %xmm1
    cvtsi2ss   %rcx, %xmm2
for:
    movss   (%rdi, %rcx,4), %xmm2
    addss   %xmm2, %xmm0
    incq    %rcx
    cmpq     %rcx, %rsi
    ja for

    cvtsi2ss    %rsi, %xmm1
    movss   %xmm0, %xmm2
    divss   %xmm1, %xmm2 # promedio en xmm2
    movss   %xmm2, %xmm1 # promedio en xmm1 para print f
    # printf espera double, hay que promover xmm0 y xmm1
    cvtss2sd    %xmm0, %xmm0
    cvtss2sd    %xmm1, %xmm1
    movq    $2, %rax
    leaq    str1, %rdi
    call printf

    sarq    -8(%rbp)
    cmpq    $0,-8(%rbp)
    je par
    impar:
        movq    %rbp, %rsp
        popq    %rbp
        movq $1, %rax
        ret
    par:
        movq    %rbp, %rsp
        popq    %rbp
        movq    $0, %rax
        ret