.text
.global calculo

# rdi(cahr), rsi(char),rdx(char),rcx(int),r8(char),xmm0(float),xmm1(double),r9(int),16(rbp),24(rbp)
calculo:
    # prologo
    pushq %rbp # guardamos la base de la pila
    movq %rsp, %rbp # movemos la base de la pila

    xorq %rax, %rax
    #   convertimos a,c a int (32bits)
    movzbl %dil, %edi # a
    movzbl %dl, %edx # c
    addl %edx, %eax # 0+c
    addl %edi, %eax # c+a
    addl %ecx, %eax # c+a+d

    movq $0, %rbx # se guardara la suma de i+h
    addl 16(%rbp), %ebx # 0 +j
    addl 24(%rbp), %ebx # j+i

    mull %ebx # rbx*rax

    #   epilogo
    movq %rbp, %rsp
    popq %rbp
    ret
