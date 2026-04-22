
.text
.global fact1
.type fact1, @function

# prologo
    
fact1:
    cmpq $1, %rdi
    jbe c_1
    pushq %rdi # guardo el x    
    decq %rdi # rdi= x-1
    call fact1
    popq %rdi
    mul %rdi # se guarda el resultado en rax
    ret

c_1:
    movq $1, %rax
    ret


.global fact2
.type fact2, @function
fact2:

    movl $1,%eax
recurse:
    cmp $1,%edi
    jz fin
    mul %edi
    decl %edi
    jmp recurse

fin:
    ret 

