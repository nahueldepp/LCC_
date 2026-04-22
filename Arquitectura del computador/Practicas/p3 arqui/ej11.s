.data
ar: .byte 1,2,3,4 #bytes
len:.quad 4
.text
.global main

main: 
    # Prologo
    pushq %rbp # guardo el puntero de  a la base de la pila en la pila
    movq %rsp, %rbp # muevo la base de la pila a su antiguo tope, para haccer una "nueva pila"

    movq len, %rcx # rcx= 4
    xor %rax, %rax
    lea ar, %rdi # rdi= &ar
apilar: 
    movzbq (%rdi), %rax # convierto el dato de ar[i] a un quad, ya que se apila por quad
    pushq %rax
    incq %rdi # rdi= rdi + 1
    loop apilar
    # receteamos rdi y rcx para desapilar
    leaq ar, %rdi
    xorq %rax, %rax
    movq len, %rcx
desapilar: 
    popq %rax
    movb %al,(%rdi) 
    incq %rdi   
    loop desapilar
    # epilogo
    movq %rbp, %rsp
    popq %rbp
    ret