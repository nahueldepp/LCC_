.data
cant_arg_ins: .asciz "La cantidad de argumentos es insuficiente\n"
cant_suf: .asciz "Cantidad de argumentos: %d, suma de los argumentos: %d\n"
.text
.global main

main:
    # prologo 
    pushq %rbp
    movq %rsp, %rbp
    cmp $2, %rdi
    jb arg_in
    
    subq $16, %rsp # guartdo espacio para los primeros 6
    movq %rdi, -8(%rbp)
    movq %rsi, %r14
  
    movq %rdi, %r12 # cantidad de argumentos
    movq $0, %r13 # registro donde se almacenara la suma

suma:
    decq %r12 
    movq (%r14,%r12,8), %rdi
    call atoi
    addq %rax, %r13
    cmp $1, %r12
    jae suma
    jb arg_suf
    
arg_in:
    movq $cant_arg_ins, %rdi
    movq %r13, %rsi
    call printf
    jmp fin
arg_suf:
    movq $cant_suf, %rdi
    movq -8(%rbp), %rsi
    movq %r13, %rdx
    call printf
    
fin:
    # epilogo
    movq %rbp, %rsp
    popq %rbp
    ret