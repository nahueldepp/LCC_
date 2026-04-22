.data

b:  .float 2.3
str1:   .asciz "El valor escalado es %f\n"

.text
.global main
main:
    pushq   %rbp
    movq    %rsp, %rbp
    decq    %rdi
    movq    (%rsi,%rdi,8) , %rdi # puntero al string s[1]
    xorq    %rax, %rax
    call    atoi
    movss   b, %xmm0    #   float b
    movq    %rax, %rdi # x
    movq    $1, %rax
    call    scale
    movq    %rbp, %rsp
    popq    %rbp
    ret
scale:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp

    movq    $8, %rbx
    xorps   %xmm0, %xmm0
    cvtsi2ss    %rbx, %xmm1 # k
    cvtsi2ss    %rdi, %xmm2 # x
    mulss       %xmm2, %xmm0 # x*b
    addss       %xmm1, %xmm0 # k+ x*b
    movaps      %xmm0, (%rsp)
    call imprime
    movaps      (%rsp), %xmm0
    movq    %rbp, %rsp
    popq %rbp
    cvtss2si    %xmm0, %eax
    ret

imprime: 
    pushq %rbp
    movq    %rsp, %rbp
    subq    $32, %rsp # mantenemos la pila a mod 16 bytes
    leaq        str1, %rdi 
    movq        $1, %rax
    cvtss2sd    %xmm0, %xmm0
    call printf
    xorq    %rax,%rax
    movq    %rbp, %rsp
    popq    %rbp
    ret